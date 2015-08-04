//! LaplacianSmoother definition.
/*!
\file       LaplacianSmoother.cpp
\author     Tody

date        2014/07/06
*/

#include "LaplacianSmoother.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MDataHandle.h>

#include <Eigen/Dense>
#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
#include <Eigen/Sparse>
#include <Eigen/SparseLU>

#include "MeshLaplacianData.h"
#include "MayaEigen.h"
#include "TimeCounter.h"

MTypeId LaplacianSmoother::id ( 0x09101 );
MObject LaplacianSmoother::aLambda;
MObject LaplacianSmoother::aTimingBuild;
MObject LaplacianSmoother::aTimingSolve;

//! Macro for an input attribute.
#define MAKE_INPUT(attr) \
    CHECK_MSTATUS(attr.setKeyable(true)); \
    CHECK_MSTATUS(attr.setStorable(true)); \
    CHECK_MSTATUS(attr.setReadable(true)); \
    CHECK_MSTATUS(attr.setWritable(true));

//! Macro for an output attribute.
#define MAKE_OUTPUT(attr) \
    CHECK_MSTATUS(attr.setKeyable(false)); \
    CHECK_MSTATUS(attr.setStorable(true)); \
    CHECK_MSTATUS(attr.setReadable(true)); \
    CHECK_MSTATUS(attr.setWritable(true));


///! Create a new LaplacianSmoother instance.
void* LaplacianSmoother::creator()
{
    LaplacianSmoother* res = new LaplacianSmoother();
    return res;
}

//! Initializes the node attributes.
MStatus LaplacianSmoother::initialize()
{
    MFnNumericAttribute nAttr;

    aLambda = nAttr.create ( "lambda", "lm", MFnNumericData::kFloat );
    MAKE_INPUT ( nAttr );
    nAttr.setMin ( 0.00001 );
    nAttr.setMax ( 100.00 );

    aTimingBuild = nAttr.create ( "timingbuild", "tb", MFnNumericData::kFloat );
    MAKE_OUTPUT ( nAttr );

    aTimingSolve = nAttr.create ( "timingsolve", "ts", MFnNumericData::kFloat );
    MAKE_OUTPUT ( nAttr );

    CHECK_MSTATUS ( addAttribute ( aLambda ) );
    CHECK_MSTATUS ( addAttribute ( aTimingBuild ) );
    CHECK_MSTATUS ( addAttribute ( aTimingSolve ) );

    // deform operator will be affected by aLambda.
    CHECK_MSTATUS ( attributeAffects ( aLambda, outputGeom ) );

    // timing attributes will be affected by aLambda.
    CHECK_MSTATUS ( attributeAffects ( aLambda, aTimingBuild ) );
    CHECK_MSTATUS ( attributeAffects ( aLambda, aTimingSolve ) );

    return MStatus::kSuccess;
}

//! Return if matrix M should be updated or not.
/*!
    Simple check with the size of matrix M and the number of vertices.
*/
bool LaplacianSmoother::needUpdateM ( MObject& mesh )
{
    if ( _M.rows() == 0 || _M.cols() == 0 ) return true;

    MFnMesh meshFn ( mesh );
    if ( meshFn.numVertices() != _M.rows() ) return true;

    return false;
}

//! Compute matrix M as Lt L.
void LaplacianSmoother::computeM ( MObject& mesh )
{
    MeshLaplacianData laplacian ( mesh );
    _L = laplacian.GetLaplacianMatrix ( 1 );
    _M = _L.transpose() * _L;
}

//! Solve Laplacian smoothing.
/*!
    S = (I + \lambda M)^{-1} P

    Solve the linear equation with Eigen::SimplicialCholesky solver.
*/
const Eigen::MatrixXd LaplacianSmoother::solve ( MDataBlock& block, const Eigen::MatrixXd& P )
{
    float& lambda = block.inputValue ( aLambda ).asFloat();

    Eigen::SparseMatrix<double> I = Eigen::MatrixXd::Identity ( _M.rows(), _M.cols() ).sparseView();

    Eigen::SparseMatrix<double> A = I + lambda * _M;

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver;
    solver.compute ( A );

    if ( solver.info() != Eigen::Success )
    {
        cout << "solver: fail" << endl;
        return P;
    }

    Eigen::MatrixXd P_new = solver.solve ( P );

    return P_new;
}

//! Get target mesh object.
MObject LaplacianSmoother::getMeshObject ( const MPlug& plug, MDataBlock& block )
{
    // get the input corresponding to this output
    unsigned int index = plug.logicalIndex();
    MObject thisNode = this->thisMObject();
    MPlug inPlug ( thisNode, input );
    inPlug.selectAncestorLogicalIndex ( index, input );
    MDataHandle hInput = block.inputValue ( inPlug );

    // get the input geometry and input groupId
    MDataHandle hGeom = hInput.child ( inputGeom );
    MDataHandle hGroup = hInput.child ( groupId );
    unsigned int groupId = hGroup.asLong();
    MDataHandle hOutput = block.outputValue ( plug );
    hOutput.copy ( hGeom );
    return hOutput.asMesh();
}

//! Compute function to deform.
MStatus LaplacianSmoother::compute ( const MPlug& plug, MDataBlock& block )
{
    MStatus status = MStatus::kUnknownParameter;
    if ( plug.attribute() == outputGeom )
    {
        TimeCounter tcSolve ( "Solve" );

        MObject& mesh = getMeshObject ( plug, block );

        Eigen::MatrixXd P = MayaEigen::getPositionMatrix ( mesh );

        if ( needUpdateM ( mesh ) )
        {
            TimeCounter tcBuild ( "Build" );
            computeM ( mesh );

            block.outputValue ( aTimingBuild ).setFloat ( tcBuild.getElapsedTime() );
        }

        Eigen::MatrixXd P_new = solve ( block, P );

        MayaEigen::setPositions ( mesh, P_new );

        block.outputValue ( aTimingSolve ).setFloat ( tcSolve.getElapsedTime() );

        status = MStatus::kSuccess;
    }
    return status;
}

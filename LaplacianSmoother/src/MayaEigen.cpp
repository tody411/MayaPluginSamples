//! LaplacianSmoother definition.
/*!
  \file     MayaEigen.cpp
  \author       Tody
  MayaEigen definition.
  date      2015/03/17
*/

#include "MayaEigen.h"

#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MFloatVectorArray.h>

//! Returns the position matrix P of the target mesh.
const Eigen::MatrixXd MayaEigen::getPositionMatrix ( MObject& mesh )
{
    MFnMesh meshFn ( mesh );

    MPointArray vertexArray;
    meshFn.getPoints ( vertexArray );

    Eigen::MatrixXd P ( vertexArray.length(), 3 );

    for ( int i = 0; i < vertexArray.length(); i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            P ( i, j ) = vertexArray[i][j];
        }
    }

    return P;
}

//! Returns the normal matrix N of the target mesh.
const Eigen::MatrixXd MayaEigen::getNormalMatrix ( MObject& mesh )
{
    MFnMesh meshFn ( mesh );

    MFloatVectorArray normalArray;
    meshFn.getVertexNormals ( true, normalArray );

    Eigen::MatrixXd N ( normalArray.length(), 3 );

    for ( int i = 0; i < normalArray.length(); i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            N ( i, j ) = normalArray[i][j];
        }
    }

    return N;
}

//! Set the position matrix P for the target mesh.
void  MayaEigen::setPositions ( MObject& mesh, const Eigen::MatrixXd& P )
{
    MFnMesh meshFn ( mesh );

    if ( meshFn.numVertices() != P.rows() ) return;

    MPointArray vertexArray ( P.rows() );

    for ( int i = 0; i < P.rows(); i++ )
    {
        vertexArray[i] = MPoint ( P ( i, 0 ), P ( i, 1 ), P ( i, 2 ) );
    }

    meshFn.setPoints ( vertexArray );
}

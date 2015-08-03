/*!
  \file     LaplacianSmoother.h
  \author   Tody
  LaplacianSmoother definition.
  \date     2015/03/17
*/

#ifndef	LAPLACIANSMOOTHER_H
#define	LAPLACIANSMOOTHER_H

#include <maya/MPxDeformerNode.h>
#include <Eigen/Sparse>

//! LaplacianSmoother implementation.
/*!
	argmin_S |P - S|^2 + \lambda | L S |^2

	M = Lt L
	S = (I + \lambda M)^{-1} P

	MEL:	deformer -type LaplacianSmoother;
	Python: cmds.deformer( type="LaplacianSmoother" );
*/
class LaplacianSmoother : public MPxDeformerNode 
{ 
public:
	//! Constructor.
	LaplacianSmoother(){}

	//! Destructor.
	virtual ~LaplacianSmoother(){}

	//! Compute function to deform.
	/*!
		If you want to access mesh structure from the deformer,
		you need to implement compute function replacing with deform function.
	*/
	MStatus compute(const MPlug& plug, MDataBlock& dataBlock);


	//! Create a new LaplacianSmoother instance.
	static	void*    creator();

	//! Initializes the node attributes.
	static  MStatus initialize();

	//! type ID of the node. 
	static  MTypeId id;

	//! Returns the type name of this node. 
	static	MString getMayaName(){ return MString("LaplacianSmoother");}

private:
	//! Get target mesh object.
	MObject getMeshObject(const MPlug& plug, MDataBlock& block);

	//! Return if matrix M should be updated or not.
	bool needUpdateM(MObject& mesh);

	//! Compute matrix M as Lt L.
	void computeM(MObject& mesh);
	
	//! Solve Laplacian smoothing.
	const Eigen::MatrixXd solve(MDataBlock& block, const Eigen::MatrixXd& P);


private:
	//! M = Lt L
	Eigen::SparseMatrix<double>		_M;

	//! Sparse laplacian matrix.
	Eigen::SparseMatrix<double>		_L;

private:
	// inputs.
	//! Smoothing parameter lambda.
	static MObject aLambda;
	
	// outputs.
	//! Timing info for building matrix M.
	static MObject aTimingBuild;


	//! Timing info for solving laplacian smoothing.
	static MObject aTimingSolve;


};
#endif


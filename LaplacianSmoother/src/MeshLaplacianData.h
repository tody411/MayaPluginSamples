/*!
	\file		MeshMeshLaplacianData.h
	\author		Tody
	MeshMeshLaplacianData class definition.		
	\date		2015/03/17
*/

#ifndef	MESHLAPLACIANDATA_H
#define	MESHLAPLACIANDATA_H

#include "ILaplacianData.h"

#include <maya/MFnMesh.h>
#include <maya/MItMeshVertex.h>

//! Laplacian data.
class MeshLaplacianData : public ILaplacianData
{
public :
	/*!
	\param		geometryPath	target geometry dag path
	*/
	MeshLaplacianData(const MDagPath& geometryPath)
		: ILaplacianData( geometryPath ) {}

	/*!
	\param		geometryObject	target geometry object
	*/
	MeshLaplacianData(const MObject& geometryObject)
		: ILaplacianData( geometryObject) {}

	//! Destructor.
	virtual ~MeshLaplacianData(){}
	
	//!	Get Laplacian data.
	/*!
	\param	numFunctions	the number of functions (e.g. 3 for point xyz.)
	\return LaplacianMatrix	output Laplacian matrix data. Eigen::SparseMatrix<double> type.
	*/
	const	Eigen::SparseMatrix<double> GetLaplacianMatrix(int numFunctions = 3);

private:
	//! Vertex iterator for the target geometry.
	MItMeshVertex vertIter();

	//!	Get Laplacian data.
	/*!
	\param  meshFn			target mesh function
	\param	numFunctions	the number of functions (e.g. 3 for point xyz.)
	\return LaplacianMatrix	output Laplacian matrix data. Eigen::SparseMatrix<double> type.
	*/
	const	Eigen::SparseMatrix<double> getLaplacianMatrix(MFnMesh& meshFn, int numFunctions = 3);
};

#endif

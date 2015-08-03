#include "MeshLaplacianData.h"

#include <maya/MIntArray.h>
	

//!	Get Laplacian data.
const	Eigen::SparseMatrix<double>	MeshLaplacianData::GetLaplacianMatrix(int numFunctions)
{
	if ( _geometryPath.hasFn(MFn::kMesh) )
	{
		MFnMesh meshFn( _geometryPath );
		return getLaplacianMatrix(meshFn, numFunctions);
	}

	if ( _geometryObject.hasFn(MFn::kMesh))
	{
		MFnMesh meshFn( _geometryObject );
		return getLaplacianMatrix(meshFn, numFunctions);
	}

	Eigen::SparseMatrix<double>	zeroMat;
	return zeroMat;
}

//! Vertex iterator for the target geometry.
MItMeshVertex MeshLaplacianData::vertIter()
{
	if ( _geometryPath.hasFn(MFn::kMesh) )
	{
		return MItMeshVertex(_geometryPath);
	}

	if ( _geometryObject.hasFn(MFn::kMesh) )
	{
		return MItMeshVertex(_geometryObject);
	}

	return MItMeshVertex( _geometryObject);
}

//!	Get Laplacian data.
const	Eigen::SparseMatrix<double> MeshLaplacianData::getLaplacianMatrix(MFnMesh& meshFn, int numFunctions)
{
	int numVertices = meshFn.numVertices();

	int numRows = numFunctions * numVertices;
	int numCols = numRows;

	Eigen::SparseMatrix<double>	LaplacianMatrix(numRows, numCols);
	LaplacianMatrix.reserve(Eigen::VectorXi::Constant(numCols,8));

	MItMeshVertex vertIt = vertIter();
	MIntArray	cvIDs;

	int iterVerts = 0;

	while ( !vertIt.isDone() )
	{
		int vID = vertIt.index();
		vertIt.getConnectedVertices( cvIDs );

		if ( cvIDs.length() > 0)
		{
			for(int i = 0; i < numFunctions; ++i)
			{
				LaplacianMatrix.insert(numFunctions*vID+i,numFunctions*vID+i) = (float) cvIDs.length();
			}

			for (int vi = 0; vi < cvIDs.length(); ++vi)
			{
				int cvID = cvIDs[vi];
				for(int i = 0; i < numFunctions; ++i)
				{
					LaplacianMatrix.insert(numFunctions*vID+i, numFunctions*cvID+i) = -1.0f;
				}
			}
		}

		vertIt.next();
		iterVerts++;
	}

	LaplacianMatrix.makeCompressed();
	return LaplacianMatrix;
}
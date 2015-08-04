//! Interface class for Lapacian data.
/*!
\file       ILaplacianData.h
\author     Tody
\date       2015/03/17
*/

#ifndef BASELAPLACIANDATA_H
#define BASELAPLACIANDATA_H

#include <Eigen/Sparse>

#include <maya/MTypes.h>
#include <maya/MDagPath.h>

//! Interface class for Laplacian data.
class ILaplacianData
{
public :
    /*!
    \param      geometryPath    target geometry dag path
    */
    ILaplacianData ( const MDagPath& geometryPath )
        : _geometryPath ( geometryPath )
    {}

    /*!
    \param      geometryObject  target geometry object
    */
    ILaplacianData ( const MObject& geometryObject )
        : _geometryObject ( geometryObject )
    {}

    //! Destructor.
    virtual ~ILaplacianData() {}

    //! Get Laplacian data.
    /*!
    \param  numFunctions    the number of functions (e.g. 3 for point xyz.)
    \return LaplacianMatrix output Laplacian matrix data. Eigen::SparseMatrix<double> type.
    */
    virtual const   Eigen::SparseMatrix<double> GetLaplacianMatrix ( int numFunctions = 3 ) = 0;

protected:
    //! Target geometry objet.
    MObject             _geometryObject;

    //! Target geometry dag path.
    MDagPath            _geometryPath;
};

#endif

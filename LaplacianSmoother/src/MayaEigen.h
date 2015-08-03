
/*!
  \file     MayaEigen.h
  \author   Tody
  MayaEigen definition.
  \date     2015/03/17
*/

#ifndef	MAYAEIGEN_H
#define	MAYAEIGEN_H

#include <maya/MObject.h>
#include <Eigen/Sparse>

//! MayaEigen implementation.
class MayaEigen
{
private :
  //! Constructor.
  MayaEigen(){}

  //! Destructor.
  virtual ~MayaEigen(){}

public:

  //! Returns the position matrix P of the target mesh.
  static const Eigen::MatrixXd getPositionMatrix(MObject& mesh);

  //! Returns the normal matrix N of the target mesh.
  static const Eigen::MatrixXd getNormalMatrix(MObject& mesh);

  //! Set the position matrix P for the target mesh.
  static void setPositions(MObject& mesh, const Eigen::MatrixXd& P);
  

};

#endif


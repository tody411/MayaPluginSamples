//! NoiseDeformer definition.
/*!
    \file     NoiseDeformer.h
    \author   Tody
    \date     2015/03/17
*/
#ifndef NOISEDEFORMER_H
#define NOISEDEFORMER_H

#include <maya/MPxDeformerNode.h>

//! NoiseDeformer implementation.
/*!
    MEL:    deformer -type NoiseDeformer;
    Python: cmds.deformer( type="NoiseDeformer" );
*/
class NoiseDeformer : public MPxDeformerNode
{
public:
    //! Constructor.
    NoiseDeformer() {}

    //! Destructor.
    virtual ~NoiseDeformer() {}

    //! Deform function.
    MStatus  deform ( MDataBlock& block, MItGeometry& iter,
                      const MMatrix& mat, unsigned int multiIndex );

    //! Create a new NoiseDeformer instance.
    static  void*    creator();

    //! Initializes the node attributes.
    static  MStatus initialize();

    //! type ID of the node.
    static  MTypeId id;

    //! Returns the type name of this node.
    static  MString getMayaName() { return MString ( "NoiseDeformer" );}

private:
    // inputs.
    //! Noise paramter sigma.
    static MObject aSigma;

};

#endif

/*!
	\file     NoiseDeformer.cpp
	\author   Tody
	NoiseDeformer definition.
	\date     2015/03/17
*/
#include "NoiseDeformer.h"

#include <maya/MFnNumericAttribute.h> 
#include <maya/MItGeometry.h>
#include <maya/MPoint.h>

#include <random>

MTypeId NoiseDeformer::id(0x09100);
MObject NoiseDeformer::aSigma;

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

//! Create a new NoiseDeformer instance.
void* NoiseDeformer::creator() 
{
	NoiseDeformer * res = new NoiseDeformer();
	return res; 
}

//! Initializes the node attributes.
MStatus NoiseDeformer::initialize() 
{
	MFnNumericAttribute nAttr;

	aSigma = nAttr.create("sigma", "sg", MFnNumericData::kFloat, 1.0);
	MAKE_INPUT(nAttr);
	nAttr.setMin(0.0);
	nAttr.setMax(10.0);

	CHECK_MSTATUS(addAttribute(aSigma));

	// deform operator will be affected by aSigma.
	CHECK_MSTATUS(attributeAffects(aSigma, outputGeom));

	return MStatus::kSuccess;
}

//! Deform function.
MStatus NoiseDeformer::deform( MDataBlock& block, MItGeometry& iter,
							   const MMatrix&, unsigned int )
{
    MStatus status = MS::kSuccess;
    
    float env = block.inputValue(envelope).asFloat();
	double sigma = block.inputValue( aSigma ).asFloat();
	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> randPosition(-0.5 * sigma, 0.5 * sigma);

    // set new positions through each point in MItGeometry.
    for ( ; !iter.isDone(); iter.next()) 
	{
        MPoint p = iter.position();

		MVector d( randPosition(mt), randPosition(mt), randPosition(mt));

		p += env * d;

        iter.setPosition(p);
    }
    return status;
}


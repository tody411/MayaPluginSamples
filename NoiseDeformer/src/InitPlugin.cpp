//! Plugin functions for NoiseDeformer.
/*!
    \file     InitPlugin.cpp
    \author   Tody

    \date     2015/03/17
*/
#include <maya/MFnPlugin.h>
#include "NoiseDeformer.h"

//! Initialize plugin for NoiseDeformer.
MStatus initializePlugin ( MObject obj )
{
    MStatus status;
    MFnPlugin plugin ( obj, "Tody", "1.0", "Any" );
    status = plugin.registerNode ( NoiseDeformer::getMayaName(), NoiseDeformer::id, NoiseDeformer::creator,
                                   NoiseDeformer::initialize,  MPxNode::kDeformerNode );

    if ( !status )
    {
        status.perror ( "initialized plug-in" );
        status.perror ( status.errorString( ) );
    }

    return status;
}

//! Uninitialize plugin for NoiseDeformer.
MStatus uninitializePlugin ( MObject obj )
{
    MStatus status;
    MFnPlugin plugin ( obj );

    status = plugin.deregisterNode ( NoiseDeformer::id );

    if ( !status )
    {
        status.perror ( "uninitialized plug-in" );
        status.perror ( status.errorString( ) );
    }
    return status;
}
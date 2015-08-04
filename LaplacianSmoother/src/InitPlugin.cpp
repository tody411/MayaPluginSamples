//! Plugin functions for LaplacianSmoother.
/*!
    \file     InitPlugin.cpp
    \author   Tody
    \date     2015/03/17
*/
#include <maya/MFnPlugin.h>
#include "LaplacianSmoother.h"

//! Initialize plugin for LaplacianSmoother.
MStatus initializePlugin ( MObject obj )
{
    MStatus status;
    MFnPlugin plugin ( obj, "Tody", "1.0", "Any" );
    status = plugin.registerNode ( LaplacianSmoother::getMayaName(), LaplacianSmoother::id, LaplacianSmoother::creator,
                                   LaplacianSmoother::initialize,  MPxNode::kDeformerNode );

    if ( !status )
    {
        status.perror ( "initialized plug-in" );
        status.perror ( status.errorString( ) );
    }

    return status;
}

//! Uninitialize plugin for LaplacianSmoother.
MStatus uninitializePlugin ( MObject obj )
{
    MStatus status;
    MFnPlugin plugin ( obj );

    status = plugin.deregisterNode ( LaplacianSmoother::id );

    if ( !status )
    {
        status.perror ( "uninitialized plug-in" );
        status.perror ( status.errorString( ) );
    }
    return status;
}
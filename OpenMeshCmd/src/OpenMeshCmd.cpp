//! Simple OpenMesh command plug-in.
/*!
    \file     OpenMeshCmd.cpp
    \author   Tody
    \date     2015/08/05

    Usage:
    MEL:    OpenMeshCmd ;
    Python: cmds.OpenMeshCmd();
*/

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
typedef OpenMesh::PolyMesh_ArrayKernelT<>  MeshType;

#include <maya/MIOStream.h>
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MFnDagNode.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MItMeshVertex.h>
#include <maya/MItMeshPolygon.h>

#include <random>

//! This function will automatically create NoiseCmd class and register the plugin.
DeclareSimpleCommand ( OpenMeshCmd, "SimplePlugin", "1.0" );

//! Get selected dag list.
/*!
    \param dagList selected dag list.
    \param filter  target API types. kMesh | kLight | ...
*/
MStatus getSelectedDagList ( MDagPathArray& dagList, MFn::Type filter = MFn::kInvalid )
{
    MDagPath node;
    MObject component;
    MSelectionList list;
    MFnDagNode nodeFn;
    MGlobal::getActiveSelectionList ( list );
    for ( MItSelectionList listIter ( list, filter ); !listIter.isDone(); listIter.next() )
    {
        listIter.getDagPath ( node, component );
        nodeFn.setObject ( node );
        dagList.append ( node );
        cout << nodeFn.name().asChar() << " is selected" << endl;
    }

    return MStatus::kSuccess;
}

//! Get seleted mesh list.
/*!
    \param meshList selected mesh list.
*/
MStatus getSelectedMeshList ( MDagPathArray& meshList )
{
    return getSelectedDagList ( meshList, MFn::kMesh );
}

//! Compute noise for target mesh with parameter sigma.
/*!
    \param mesh     target mesh.
    \param sigma    noise parameter.
    \param space    target space. kObject | kWorld | kTransform | ...

    Random position will be compute with std::uniform_real_distribution method.
*/
MStatus openMeshInfo ( const MDagPath& mesh, MSpace::Space space = MSpace::kObject )
{
    MFnMesh meshFn ( mesh );
    cout << "=============================" << endl;
    cout << "MayaMesh data" << endl;
    cout << "=============================" << endl;
    cout << "numVertices: " << meshFn.numVertices() << endl;
    cout << "numEdges: " << meshFn.numEdges() << endl;
    cout << "numFaces: " << meshFn.numPolygons() << endl;
    cout <<  endl;

    int numVertices =  meshFn.numVertices();

    // create vertex data.
    MeshType openMesh;
    std::vector<MeshType::VertexHandle> vHandles ( numVertices );

    MPointArray points;
    meshFn.getPoints ( points, space );

    for ( int vi = 0; vi < numVertices; vi++ )
    {
        MPoint p = points[vi];
        vHandles[vi] = openMesh.add_vertex ( MeshType::Point ( p.x, p.y,  p.z ) );
    }

    // create face data.
    MIntArray triangleCounts;
    MIntArray triangleVertices;
    meshFn.getTriangles ( triangleCounts, triangleVertices );

    int numTriangles = triangleVertices.length() / 3;

    for ( int fi = 0; fi < numTriangles; fi++ )
    {
        std::vector<MeshType::VertexHandle>  face_vhandles;
        for ( int fvi = 0; fvi < 3; fvi++ )
        {
            face_vhandles.push_back ( vHandles[triangleVertices[3 * fi + fvi]] );
        }
        openMesh.add_face ( face_vhandles );
    }

    // compute vertex normals.
    openMesh.request_vertex_normals();
    openMesh.update_normals();



    cout << "=============================" << endl;
    cout << "OpenMesh data" << endl;
    cout << "=============================" << endl;
    cout << "numVertices: " << openMesh.n_vertices() << endl;
    cout << "numEdges: " << openMesh.n_edges() << endl;
    cout << "numFaces: " << openMesh.n_faces() << endl;
    cout << "numHalfEdges: " << openMesh.n_halfedges() << endl;

    cout << "hasVertexNormals: " << openMesh.has_vertex_normals() << endl;
    cout << "hasFaceNormals: " << openMesh.has_face_normals() << endl;

    return MStatus::kSuccess;
}

//! Simple command to get noisy mesh.
MStatus OpenMeshCmd::doIt ( const MArgList& args )
{
    cout << "OpenMeshCmd " << endl;

    MDagPathArray meshList;
    getSelectedMeshList ( meshList );

    for ( int i = 0; i < meshList.length(); i++ )
    {
        MDagPath mesh ( meshList[i] );
        openMeshInfo ( mesh );
    }

    return MS::kSuccess;
}


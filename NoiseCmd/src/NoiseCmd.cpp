//! Simple noise command plug-in definition.
/*!
	\file     NoiseCmd.cpp
	\author   Tody
	\date     2015/03/17

	Usage:
	MEL:    NoiseCmd <sigma>;
    Python: cmds.NoiseCmd( <sigma> );

    <sigma>: noise parameter.
*/

#include <maya/MIOStream.h>
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MItMeshVertex.h>

#include <random>

//! This function will automatically create NoiseCmd class and register the plugin.
DeclareSimpleCommand( NoiseCmd, "SimplePlugin", "1.0");

//! Get selected dag list.
/*!
	\param dagList selected dag list.
	\param filter  target API types. kMesh | kLight | ...
*/
MStatus getSelectedDagList(MDagPathArray& dagList, MFn::Type filter = MFn::kInvalid)
{
	MDagPath node;
	MObject component;
	MSelectionList list;
	MFnDagNode nodeFn;
	MGlobal::getActiveSelectionList( list );
	for ( MItSelectionList listIter( list, filter ); !listIter.isDone(); listIter.next() )
	{
		listIter.getDagPath( node, component );
		nodeFn.setObject( node );
		dagList.append( node );
		cout << nodeFn.name().asChar() << " is selected" << endl;
	}

	return MStatus::kSuccess;
}

//! Get seleted mesh list.
/*!
	\param meshList selected mesh list.
*/
MStatus getSelectedMeshList(MDagPathArray& meshList)
{
	return getSelectedDagList( meshList, MFn::kMesh );
}

//! Compute noise for target mesh with parameter sigma.
/*!
	\param mesh		target mesh.
	\param sigma	noise parameter.
	\param space	target space. kObject | kWorld | kTransform | ...

	Random position will be compute with std::uniform_real_distribution method.
*/
MStatus computeNoise(const MDagPath& mesh, double sigma,  MSpace::Space space=MSpace::kObject)
{
	std::random_device rd;
	std::mt19937 mt(rd());

	MItMeshVertex vertIt( mesh );

	std::uniform_real_distribution<double> randPosition(-0.5 * sigma, 0.5 * sigma);

	for ( ; !vertIt.isDone(); vertIt.next())
	{
		MVector d( randPosition(mt), randPosition(mt), randPosition(mt));
		vertIt.translateBy(d, space);
	}

	return MStatus::kSuccess;
}

//! Simple command to get noisy mesh.
MStatus NoiseCmd::doIt( const MArgList& args )
{
	double sigma = args.asDouble( 0 );
	cout<<"NoiseCmd " << sigma << endl;

	MDagPathArray meshList;
	getSelectedMeshList(meshList);

	for (int i = 0; i < meshList.length(); i++)
	{
		MDagPath mesh(meshList[i]);
		computeNoise( mesh, sigma );
	}

	return MS::kSuccess;
}


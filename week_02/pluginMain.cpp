#include "DojoStretchyIK.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus stat;

    MFnPlugin plugin( obj, "Dmitry Shurov", "1.0", "any");

    stat = plugin.registerNode(
            "dojoStretchyIK",
            DojoStretchyIK::typeID,
            DojoStretchyIK::creator,
            DojoStretchyIK::initialize,
            MPxNode::kDependNode
            );

    if ( stat != MStatus::kSuccess )
    {
        stat.perror( "Failed to register Rigging Dojo Maya API 101 dojoStretchyIK" );
    }

    return stat;
}

MStatus uninitializePlugin( MObject obj )
{
    MFnPlugin plugin;
    plugin.deregisterNode(DojoStretchyIK::typeID);

    return MStatus::kSuccess;
}


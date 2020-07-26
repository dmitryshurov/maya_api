#include "basicNode.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus stat;

    MFnPlugin plugin( obj, "Dmitry Shurov", "0.1", "any");

    stat = plugin.registerNode(
            "basicNode",
            basicNode::typeID,
            basicNode::creator,
            basicNode::initialize,
            MPxNode::kDependNode
            );

    if ( stat != MStatus::kSuccess )
    {
        stat.perror( "Failed to register Rigging Dojo Maya API 101 basicNode" );
    }

    return stat;
}

MStatus uninitializePlugin( MObject obj )
{
    MFnPlugin plugin;
    plugin.deregisterNode(basicNode::typeID);

    return MStatus::kSuccess;
}
#include "BasicNode.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus stat;

    MFnPlugin plugin( obj, "Dmitry Shurov", "0.1", "any");

    stat = plugin.registerNode(
            "BasicNode",
            BasicNode::typeID,
            BasicNode::creator,
            BasicNode::initialize,
            MPxNode::kDependNode
            );

    if ( stat != MStatus::kSuccess )
    {
        stat.perror( "Failed to register Rigging Dojo Maya API 101 BasicNode" );
    }

    return stat;
}

MStatus uninitializePlugin( MObject obj )
{
    MFnPlugin plugin;
    plugin.deregisterNode(BasicNode::typeID);

    return MStatus::kSuccess;
}


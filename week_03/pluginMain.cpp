#include "DojoAimConstraint.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus stat;

    MFnPlugin plugin( obj, "Dmitry Shurov", "1.0", "any");

    stat = plugin.registerNode(
            "dojoAimConstraint",
            DojoAimConstraint::typeID,
            DojoAimConstraint::creator,
            DojoAimConstraint::initialize,
            MPxNode::kDependNode
            );

    if ( stat != MStatus::kSuccess )
    {
        stat.perror( "Failed to register Rigging Dojo Maya API 101 dojoAimConstraint" );
    }

    return stat;
}

MStatus uninitializePlugin( MObject obj )
{
    MFnPlugin plugin;
    plugin.deregisterNode(DojoAimConstraint::typeID);

    return MStatus::kSuccess;
}


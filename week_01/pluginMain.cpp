#include "DojoLengthToCurveU.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus stat;

    MFnPlugin plugin( obj, "Dmitry Shurov", "1.0", "any");

    stat = plugin.registerNode(
            "dojoLengthToCurveU",
            DojoLengthToCurveU::typeID,
            DojoLengthToCurveU::creator,
            DojoLengthToCurveU::initialize,
            MPxNode::kDependNode
            );

    if ( stat != MStatus::kSuccess )
    {
        stat.perror( "Failed to register Rigging Dojo Maya API 101 dojoLengthToCurveU" );
    }

    return stat;
}

MStatus uninitializePlugin( MObject obj )
{
    MFnPlugin plugin;
    plugin.deregisterNode(DojoLengthToCurveU::typeID);

    return MStatus::kSuccess;
}


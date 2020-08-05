#ifndef RIGGING_DOJO_MAYA_API_101_BASICNODE_H
#define RIGGING_DOJO_MAYA_API_101_BASICNODE_H

#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class DojoLengthToCurveU : public MPxNode
{
public:
    // Static variables
    static MTypeId typeID;
    static MObject inputLength;
    static MObject inputCurve;
    static MObject outputU;

    // Static methods
    static void* creator();
    static MStatus initialize();

    // Methods
    virtual MStatus compute( const MPlug& plug, MDataBlock& data );
};

#endif //RIGGING_DOJO_MAYA_API_101_BASICNODE_H

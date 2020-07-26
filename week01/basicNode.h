#ifndef RIGGING_DOJO_MAYA_API_101_BASICNODE_H
#define RIGGING_DOJO_MAYA_API_101_BASICNODE_H

#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class basicNode : public MPxNode
{
public:
    // Static variables
    static MTypeId typeID;
    static MObject inputVal;
    static MObject inputCurve;
    static MObject outputVal;

    // Methods
    virtual MStatus compute( const MPlug& plug, MDataBlock& data );
    static void* creator();
    static MStatus initialize();
};


#endif //RIGGING_DOJO_MAYA_API_101_BASICNODE_H

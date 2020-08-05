#ifndef RIGGING_DOJO_MAYA_API_101_STRETCHY_IK_H
#define RIGGING_DOJO_MAYA_API_101_STRETCHY_IK_H

#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class DojoStretchyIK : public MPxNode
{
public:
    // Node type ID
    static MTypeId typeID;

    // Node inputs
    static MObject startMatrix;
    static MObject endMatrix;
    static MObject poleVectorMatrix;

    // Node outputs
    static MObject upScale;
    static MObject downScale;

    // Node editable attributes
    static MObject upInitLength;
    static MObject downInitLength;
    static MObject globalScale;
    static MObject poleVectorLock;
    static MObject stretch;
    static MObject slide;

    // Static methods
    static void* creator();
    static MStatus initialize();

    // Methods
    virtual MStatus compute( const MPlug& plug, MDataBlock& data );
};

#endif //RIGGING_DOJO_MAYA_API_101_STRETCHY_IK_H

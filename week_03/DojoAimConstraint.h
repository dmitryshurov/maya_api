#ifndef RIGGING_DOJO_MAYA_API_101_AIM_CONSTRAINT_H
#define RIGGING_DOJO_MAYA_API_101_AIM_CONSTRAINT_H

#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class DojoAimConstraint : public MPxNode
{
public:
    // Node type ID
    static MTypeId typeID;

    // Node inputs
    static MObject translateX;
    static MObject translateY;
    static MObject translateZ;
    static MObject translate;
    static MObject upX;
    static MObject upY;
    static MObject upZ;
    static MObject upVec;
    static MObject aimMatrix;
    static MObject upMatrix;
    static MObject parentInvMatrix;
    static MObject upType;


    // Node outputs
    static MObject rotateX;
    static MObject rotateY;
    static MObject rotateZ;
    static MObject rotate;

    // Node editable attributes


    // Static methods
    static void* creator();
    static MStatus initialize();

    // Methods
    virtual MStatus compute( const MPlug& plug, MDataBlock& data );
};

#endif //RIGGING_DOJO_MAYA_API_101_AIM_CONSTRAINT_H

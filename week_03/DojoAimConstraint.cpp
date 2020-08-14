#include "DojoAimConstraint.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MVector.h>
#include <maya/MGlobal.h>
#include <maya/MEulerRotation.h>

#define MAYA_PARM(name)  // A dummy to organize parameters in the code
#define AFFECTS(name)    // A dummy to organize parameter affects in the code

MTypeId DojoAimConstraint::typeID(0x5D2C3);

MObject DojoAimConstraint::translateX;
MObject DojoAimConstraint::translateY;
MObject DojoAimConstraint::translateZ;
MObject DojoAimConstraint::translate;
MObject DojoAimConstraint::aimMatrix;
MObject DojoAimConstraint::upMatrix;

MObject DojoAimConstraint::rotateX;
MObject DojoAimConstraint::rotateY;
MObject DojoAimConstraint::rotateZ;
MObject DojoAimConstraint::rotate;

void* DojoAimConstraint::creator() {
    return new DojoAimConstraint();
}

MStatus DojoAimConstraint::initialize()
{
    MFnNumericAttribute numFn;
    MFnMatrixAttribute matFn;
    MFnCompoundAttribute compFn;
    MFnUnitAttribute unitFn;

    MAYA_PARM(translateX) {
        translateX = numFn.create("translateX", "tx", MFnNumericData::kDouble);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(translateX);
    }
    MAYA_PARM(translateY) {
        translateY = numFn.create("translateY", "ty", MFnNumericData::kDouble);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(translateY);
    }
    MAYA_PARM(translateZ) {
        translateZ = numFn.create("translateZ", "tz", MFnNumericData::kDouble);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(translateZ);
    }
    MAYA_PARM(translate) {
        translate = compFn.create("translate", "t");
        compFn.addChild(translateX);
        compFn.addChild(translateY);
        compFn.addChild(translateZ);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(translate);
    }
    MAYA_PARM(aimMatrix) {
        aimMatrix = matFn.create("aimMatrix", "aim");
        matFn.setKeyable(true);
        matFn.setStorable(true);
        matFn.setWritable(true);
        addAttribute(aimMatrix);
    }
    MAYA_PARM(upMatrix) {
        upMatrix = matFn.create("upMatrix", "up");
        matFn.setKeyable(true);
        matFn.setStorable(true);
        matFn.setWritable(true);
        addAttribute(upMatrix);
    }

    MAYA_PARM(rotateX) {
        rotateX = unitFn.create("rotateX", "rx", MFnUnitAttribute::kAngle);
        unitFn.setKeyable(false);
        unitFn.setWritable(false);
        unitFn.setStorable(false);
        addAttribute(rotateX);
    }
    MAYA_PARM(rotateY) {
        rotateY = unitFn.create("rotateY", "ry", MFnUnitAttribute::kAngle);
        unitFn.setKeyable(false);
        unitFn.setWritable(false);
        unitFn.setStorable(false);
        addAttribute(rotateY);
    }
    MAYA_PARM(rotateZ) {
        rotateZ = unitFn.create("rotateZ", "rz", MFnUnitAttribute::kAngle);
        unitFn.setKeyable(false);
        unitFn.setWritable(false);
        unitFn.setStorable(false);
        addAttribute(rotateZ);
    }
    MAYA_PARM(rotate) {
        rotate = compFn.create("rotate", "rot");
        compFn.addChild(rotateX);
        compFn.addChild(rotateY);
        compFn.addChild(rotateZ);
        unitFn.setKeyable(false);
        unitFn.setWritable(false);
        unitFn.setStorable(false);
        addAttribute(rotate);
    }

    AFFECTS(affects_up) {
        attributeAffects(translate, rotate);
        attributeAffects(aimMatrix, rotate);
        attributeAffects(upMatrix, rotate);
    }

    return MStatus();
}

MStatus DojoAimConstraint::compute(const MPlug &plug, MDataBlock &data)
{
    if (plug == rotate || plug == rotateX || plug == rotateY || plug == rotateZ)
    {
        MMatrix aimMatV = data.inputValue(aimMatrix).asMatrix();
        MMatrix upMatV = data.inputValue(upMatrix).asMatrix();
        MVector translateV = data.inputValue(translate).asVector();

        MVector aimV = MTransformationMatrix(aimMatV).getTranslation(MSpace::kWorld);
        MVector upV = MTransformationMatrix(upMatV).getTranslation(MSpace::kWorld);

        MVector xAxis = (aimV - translateV).normal();
        MVector yAxis = (upV - translateV).normal();
        MVector zAxis = xAxis ^ yAxis;
        yAxis = zAxis ^ xAxis;

        double outArr[4][4] = {
                {xAxis[0], xAxis[1], xAxis[2], 0},
                {yAxis[0], yAxis[1], yAxis[2], 0},
                {zAxis[0], zAxis[1], zAxis[2], 0},
                {0, 0, 0, 0}
        };

        MMatrix outMat(outArr);
        MTransformationMatrix outXformMatrix(outMat);
        MEulerRotation outRot = outXformMatrix.eulerRotation();

        data.outputValue(rotate).set(outRot.asVector());
        data.outputValue(rotate).setClean();
    }

    return MStatus();
}

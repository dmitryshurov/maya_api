#include "DojoAimConstraint.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MVector.h>
#include <maya/MGlobal.h>
#include <maya/MEulerRotation.h>

#define MAYA_PARM(name)  // A dummy to organize parameters in the code
#define AFFECTS(name)    // A dummy to organize parameter affects in the code

#define MCheckError(STATUS, MESSAGE)                          \
if (STATUS != MStatus::kSuccess) {                            \
MGlobal::displayError(MESSAGE);                               \
return status;                                                \
}

#define MVEC_FROM_MMAT(NAME) MVector(NAME[3][0], NAME[3][1], NAME[3][2])

enum UpTypes {
    MATRIX,
    VECTOR
};

MTypeId DojoAimConstraint::typeID(0x5D2C3);

MObject DojoAimConstraint::translateX;
MObject DojoAimConstraint::translateY;
MObject DojoAimConstraint::translateZ;
MObject DojoAimConstraint::translate;
MObject DojoAimConstraint::upX;
MObject DojoAimConstraint::upY;
MObject DojoAimConstraint::upZ;
MObject DojoAimConstraint::upVec;
MObject DojoAimConstraint::aimMatrix;
MObject DojoAimConstraint::upMatrix;
MObject DojoAimConstraint::parentInvMatrix;
MObject DojoAimConstraint::upType;

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
    MFnEnumAttribute enumFn;

    MAYA_PARM(upType) {
        upType = enumFn.create("upType", "uptp", UpTypes::MATRIX);
        enumFn.addField("Matrix", UpTypes::MATRIX);
        enumFn.addField("Vector", UpTypes::VECTOR);
        enumFn.setKeyable(true);
        enumFn.setWritable(true);
        enumFn.setStorable(true);
        addAttribute(upType);
    }

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

    MAYA_PARM(upX) {
        upX = numFn.create("upX", "upx", MFnNumericData::kDouble);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setDefault(0.0);
        addAttribute(upX);
    }
    MAYA_PARM(upY) {
        upY = numFn.create("upY", "upy", MFnNumericData::kDouble);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setDefault(1.0);
        addAttribute(upY);
    }
    MAYA_PARM(upZ) {
        upZ = numFn.create("upZ", "upz", MFnNumericData::kDouble);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setDefault(0.0);
        addAttribute(upZ);
    }
    MAYA_PARM(upVec) {
        upVec = compFn.create("upVec", "upv");
        compFn.addChild(upX);
        compFn.addChild(upY);
        compFn.addChild(upZ);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(upVec);
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
        matFn.setKeyable(false);
        matFn.setStorable(false);
        matFn.setWritable(true);
        addAttribute(upMatrix);
    }

    MAYA_PARM(parentInvMatrix) {
        parentInvMatrix = matFn.create("parentInvMatrix", "piv");
        matFn.setKeyable(true);
        matFn.setStorable(true);
        matFn.setWritable(true);
        addAttribute(parentInvMatrix);
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
        attributeAffects(upVec, rotate);
        attributeAffects(aimMatrix, rotate);
        attributeAffects(upMatrix, rotate);
        attributeAffects(parentInvMatrix, rotate);
        attributeAffects(upType, rotate);
    }

    return MStatus();
}

MStatus DojoAimConstraint::compute(const MPlug &plug, MDataBlock &data)
{
    if (plug == rotate || plug == rotateX || plug == rotateY || plug == rotateZ)
    {
        MStatus status;

        MVector upV;

        MMatrix aimMatV = data.inputValue(aimMatrix).asMatrix();
        int upTypeV = data.inputValue(upType).asInt();

        bool globalUp;

        MDataHandle upMatrixVH = data.inputValue(upMatrix, &status);

        if (upTypeV == UpTypes::MATRIX)
        {
            MMatrix upMatV = upMatrixVH.asMatrix();
            upV = MVEC_FROM_MMAT(upMatV);
            globalUp = false;
        }
        else if (upTypeV == UpTypes::VECTOR) {
            upV = data.inputValue(upVec).asVector();
            globalUp = true;
        }
        else {
            MGlobal::displayError("Incorrect upType value");
            return MStatus::kFailure;
        }

        MDataHandle parentInvMatVH = data.inputValue(parentInvMatrix, &status);
        MCheckError(status, "Input parentInvMat not connected");
        MMatrix parentInvMatV = parentInvMatVH.asMatrix();

        MVector translateV = data.inputValue(translate).asVector();

        MVector aimV = MVEC_FROM_MMAT(aimMatV);
        MVector parentInvV = MVEC_FROM_MMAT(parentInvMatV.inverse());

        translateV += parentInvV; // Compensate for the parent translation

        MVector xAxis = (aimV - translateV).normal();
        MVector yAxis = globalUp ? upV.normal() : (upV - translateV).normal();
        MVector zAxis = (xAxis ^ yAxis).normal();
        yAxis = (zAxis ^ xAxis).normal();

        double outArr[4][4] = {
                {xAxis[0], xAxis[1], xAxis[2], 0},
                {yAxis[0], yAxis[1], yAxis[2], 0},
                {zAxis[0], zAxis[1], zAxis[2], 0},
                {translateV[0], translateV[1], translateV[2], 1}
        };

        MMatrix outMat(outArr);

        outMat = outMat * parentInvMatV;

        MTransformationMatrix outXformMatrix(outMat);
        MEulerRotation outRot = outXformMatrix.eulerRotation();

        data.outputValue(rotate).set(outRot.asVector());
        data.outputValue(rotate).setClean();
    }

    return MStatus();
}

#include "DojoStretchyIK.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MGlobal.h>

#define MAYA_PARM(name)  // A dummy to organize parameters in the code
#define AFFECTS(name)    // A dummy to organize parameter affects in the code

MTypeId DojoStretchyIK::typeID(0x5D2C2 );

MObject DojoStretchyIK::startMatrix;
MObject DojoStretchyIK::endMatrix;
MObject DojoStretchyIK::poleVectorMatrix;

MObject DojoStretchyIK::upScale;
MObject DojoStretchyIK::downScale;

MObject DojoStretchyIK::upInitLength;
MObject DojoStretchyIK::downInitLength;
MObject DojoStretchyIK::globalScale;
MObject DojoStretchyIK::poleVectorLock;
MObject DojoStretchyIK::stretch;
MObject DojoStretchyIK::slide;

void* DojoStretchyIK::creator() {
    return new DojoStretchyIK();
}

MStatus DojoStretchyIK::initialize()
{
    MFnNumericAttribute numFn;
    MFnMatrixAttribute matFn;

    MAYA_PARM(startMatrix) {
        startMatrix = matFn.create("Start_Matrix", "stm");
        matFn.setKeyable(true);
        matFn.setStorable(true);
        addAttribute(startMatrix);
    }
    MAYA_PARM(endMatrix) {
        endMatrix = matFn.create("End_Matrix", "enm");
        matFn.setKeyable(true);
        matFn.setStorable(true);
        addAttribute(endMatrix);
    }
    MAYA_PARM(poleVectorMatrix) {
        poleVectorMatrix = matFn.create("Pole_Vector_Matrix", "plvm");
        matFn.setKeyable(true);
        matFn.setStorable(true);
        addAttribute(poleVectorMatrix);
    }

    MAYA_PARM(upScale) {
        upScale = numFn.create("Up_Scale", "ups", MFnNumericData::kDouble, 1.0);
        numFn.setKeyable(false);
        numFn.setWritable(false);
        numFn.setStorable(false);
        addAttribute(upScale);
    }
    MAYA_PARM(downScale) {
        downScale = numFn.create("Down_Scale", "dns", MFnNumericData::kDouble, 1.0);
        numFn.setKeyable(false);
        numFn.setWritable(false);
        numFn.setStorable(false);
        addAttribute(downScale);
    }

    MAYA_PARM(upInitLength) {
        upInitLength = numFn.create("Up_Init_Length", "upis", MFnNumericData::kDouble, 0);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.001);
        addAttribute(upInitLength);
    }
    MAYA_PARM(downInitLength) {
        downInitLength = numFn.create("Down_Init_Length", "dnis", MFnNumericData::kDouble, 0);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.001);
        addAttribute(downInitLength);
    }
    MAYA_PARM(globalScale) {
        globalScale = numFn.create("Global_Scale", "gls", MFnNumericData::kDouble, 1.0);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.001);
        addAttribute(globalScale);
    }
    MAYA_PARM(poleVectorLock) {
        poleVectorLock = numFn.create("Pole_Vector_Lock", "pvl", MFnNumericData::kDouble, 0.0);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.0);
        numFn.setMax(1.0);
        addAttribute(poleVectorLock);
    }
    MAYA_PARM(stretch) {
        stretch = numFn.create("Stretch", "str", MFnNumericData::kDouble, 0.0);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.0);
        numFn.setMax(1.0);
        addAttribute(stretch);
    }
    MAYA_PARM(slide) {
        slide = numFn.create("Slide", "sld", MFnNumericData::kDouble, 0.5);
        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.0);
        numFn.setMax(1.0);
        addAttribute(slide);
    }

    AFFECTS(affects_up) {
        attributeAffects(startMatrix, upScale);
        attributeAffects(endMatrix, upScale);
        attributeAffects(poleVectorMatrix, upScale);

        attributeAffects(upInitLength, upScale);
        attributeAffects(downInitLength, upScale);
        attributeAffects(globalScale, upScale);
        attributeAffects(poleVectorLock, upScale);
        attributeAffects(stretch, upScale);
        attributeAffects(slide, upScale);
    }
    AFFECTS(affects_down) {
        attributeAffects(startMatrix, downScale);
        attributeAffects(endMatrix, downScale);
        attributeAffects(poleVectorMatrix, downScale);

        attributeAffects(upInitLength, downScale);
        attributeAffects(downInitLength, downScale);
        attributeAffects(globalScale, downScale);
        attributeAffects(poleVectorLock, downScale);
        attributeAffects(stretch, downScale);
        attributeAffects(slide, downScale);
    }

    return MStatus();
}

MStatus DojoStretchyIK::compute(const MPlug &plug, MDataBlock &data)
{
    if (plug == upScale || plug == downScale)
    {
        MMatrix startMatrixV = data.inputValue(startMatrix).asMatrix();
        MMatrix endMatrixV = data.inputValue(endMatrix).asMatrix();
        MMatrix poleVectorMatrixV = data.inputValue(poleVectorMatrix).asMatrix();

        double upInitLengthV = data.inputValue(upInitLength).asDouble();
        double downInitLengthV = data.inputValue(downInitLength).asDouble();
        double globalScaleV = data.inputValue(globalScale).asDouble();
        double poleVectorLockV = data.inputValue(poleVectorLock).asDouble();
        double stretchV = data.inputValue(stretch).asDouble();
        double slideV = data.inputValue(slide).asDouble();

        // Sum of bone init lengths
        double chainInitLength = upInitLengthV + downInitLengthV;

        MVector startVec(startMatrixV[3][0], startMatrixV[3][1], startMatrixV[3][2]);
        MVector endVec(endMatrixV[3][0], endMatrixV[3][1], endMatrixV[3][2]);
        MVector poleVec(poleVectorMatrixV[3][0], poleVectorMatrixV[3][1], poleVectorMatrixV[3][2]);

        MVector startToEndVec = endVec - startVec;
        MVector startToPoleVec = poleVec - startVec;
        MVector poleToEndVec = endVec - poleVec;

        double startToEndLength = startToEndVec.length();
        double startToPoleLength = startToPoleVec.length();
        double poleToEndLength = poleToEndVec.length();

        double upScaleV = upInitLengthV;
        double downScaleV = downInitLengthV;


        // Apply slide
        if (slideV < 0.5)
        {
            upScaleV *= slideV / 0.5;
            downScaleV = chainInitLength - upScaleV;
        }

        if (slideV > 0.5)
        {
            downScaleV *= (1 - slideV) / 0.5;
            upScaleV = chainInitLength - downScaleV;
        }
        //


        // Apply stretch
        if (chainInitLength < startToEndLength)
        {
            double scale = startToEndLength / chainInitLength;

            // The simplest scaling
            upScaleV *= 1.0 + (scale - 1.0) * stretchV;
            downScaleV *= 1.0 + (scale - 1.0) * stretchV;
        }
        //


        // Apply polar vector lock
        if (poleVectorLockV > 0)
        {
            upScaleV += poleVectorLockV * (startToPoleLength - upScaleV);
            downScaleV += poleVectorLockV * (poleToEndLength - downScaleV);
        }
        //

        // Set output values
        data.outputValue(upScale).set(upScaleV);
        data.outputValue(upScale).setClean();

        data.outputValue(downScale).set(downScaleV);
        data.outputValue(downScale).setClean();
    }

    return MStatus();
}

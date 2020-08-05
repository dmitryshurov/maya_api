#include "DojoStretchyIK.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MGlobal.h>

#define MAYA_PARM(name)  // A dummy to organize parameters in the code

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
        upScale = numFn.create("Up_Scale", "ups", MFnNumericData::kDouble);

        numFn.setKeyable(false);
        numFn.setWritable(false);
        numFn.setStorable(false);
        addAttribute(upScale);
    }
    MAYA_PARM(downScale) {
        downScale = numFn.create("Down_Scale", "dns", MFnNumericData::kDouble);

        numFn.setKeyable(false);
        numFn.setWritable(false);
        numFn.setStorable(false);
        addAttribute(downScale);
    }

    MAYA_PARM(upInitLength) {
        upInitLength = numFn.create("Up_Init_Length", "upis", MFnNumericData::kDouble);

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(upInitLength);
    }
    MAYA_PARM(downInitLength) {
        downInitLength = numFn.create("Down_Init_Length", "dnis", MFnNumericData::kDouble);

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(downInitLength);
    }
    MAYA_PARM(globalScale) {
        globalScale = numFn.create("Global_Scale", "gls", MFnNumericData::kDouble);

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(globalScale);
    }
    MAYA_PARM(poleVectorLock) {
        poleVectorLock = numFn.create("Pole_Vector_Lock", "pvl", MFnNumericData::kDouble);

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(poleVectorLock);
    }
    MAYA_PARM(stretch) {
        stretch = numFn.create("Stretch", "str", MFnNumericData::kDouble);

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(stretch);
    }
    MAYA_PARM(slide) {
        slide = numFn.create("Slide", "sld", MFnNumericData::kDouble);

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        addAttribute(slide);
    }

    attributeAffects(slide, upScale);
    attributeAffects(slide, downScale);

    return MStatus();
}

MStatus DojoStretchyIK::compute(const MPlug &plug, MDataBlock &data)
{
//    if (plug == outputU)
//    {
//        double inLen = data.inputValue(inputLength).asDouble();
//        MFnNurbsCurve nurbsCrv(data.inputValue(inputCurve).asNurbsCurve());
//        double outVal = nurbsCrv.findParamFromLength(inLen);
//
//        data.outputValue(outputU).set(outVal);
//        data.outputValue(outputU).setClean();
//    }

    return MStatus();
}

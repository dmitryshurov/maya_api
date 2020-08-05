#include "DojoLengthToCurveU.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MFnNurbsCurve.h>

#define MAYA_PARM  // A dummy to organize parameters in the code

MTypeId DojoLengthToCurveU::typeID(0x5D2C1 );

MObject DojoLengthToCurveU::inputLength;    // double. Means input curve length
MObject DojoLengthToCurveU::inputCurve;  // curve. Means input curve length
MObject DojoLengthToCurveU::outputU;   // double. Means output curve UV

void* DojoLengthToCurveU::creator() {
    return new DojoLengthToCurveU();
}

MStatus DojoLengthToCurveU::initialize() {
    MStatus status;
    MFnNumericAttribute numFn;
    MFnTypedAttribute typedFn;

    MAYA_PARM {
        inputLength = numFn.create("Length", "len", MFnNumericData::kDouble, 0.0, &status);

        if (status != MStatus::kSuccess) {
            status.perror("Failed to create Length parameter");
            return status;
        }

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.0);  // We probably can't have a negative value for this parm, right?
        addAttribute(inputLength);
    }

    MAYA_PARM {
        inputCurve = typedFn.create("Curve", "crv", MFnData::kNurbsCurve);

        if (status != MStatus::kSuccess) {
            status.perror("Failed to create Curve parameter");
            return status;
        }

        typedFn.setKeyable(true);
        typedFn.setWritable(true);
        typedFn.setStorable(true);
        addAttribute(inputCurve);
    }

    MAYA_PARM {
        outputU = numFn.create("U_Value", "uval", MFnNumericData::kDouble, 0.0, &status);

        if (status != MStatus::kSuccess) {
            status.perror("Failed to create U_Value parameter");
            return status;
        }

        numFn.setKeyable(false);
        numFn.setWritable(false);
        numFn.setStorable(false);
        addAttribute(outputU);
    }

    attributeAffects(inputLength, outputU);
    attributeAffects(inputCurve, outputU);

    return MStatus();
}

MStatus DojoLengthToCurveU::compute(const MPlug &plug, MDataBlock &data)
{
    if (plug == outputU)
    {
        double inLen = data.inputValue(inputLength).asDouble();
        MFnNurbsCurve nurbsCrv(data.inputValue(inputCurve).asNurbsCurve());
        double outVal = nurbsCrv.findParamFromLength(inLen);

        data.outputValue(outputU).set(outVal);
        data.outputValue(outputU).setClean();
    }

    return MStatus();
}

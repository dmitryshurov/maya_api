#include "BasicNode.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>

#define MAYA_PARM if (true)  // A weird wrapper to organize parms in the code, should think about a better way to do that

MTypeId BasicNode::typeID( 0x5D2C1 );

MObject BasicNode::inputVal;    // double. Means input curve length
MObject BasicNode::inputCurve;  // curve. Means input curve length
MObject BasicNode::outputVal;   // double. Means output curve UV

void* BasicNode::creator() {
    return new BasicNode();
}

MStatus BasicNode::initialize() {
    MStatus status;
    MFnNumericAttribute numFn;

    MAYA_PARM {
        inputVal = numFn.create("inputValue", "iv", MFnNumericData::kDouble, 0.0, &status);

        if (status != MStatus::kSuccess) {
            status.perror("Failed to create inputValue parameter");
            return status;
        }

        numFn.setKeyable(true);
        numFn.setWritable(true);
        numFn.setStorable(true);
        numFn.setMin(0.0);  // We probably can't have a negative value for this parm, right?
        addAttribute(inputVal);
    }

    MAYA_PARM {
        outputVal = numFn.create("outputValue", "ov", MFnNumericData::kDouble, 0.0, &status);

        if (status != MStatus::kSuccess) {
            status.perror("Failed to create outputValue parameter");
            return status;
        }

        numFn.setKeyable(false);
        numFn.setWritable(false);
        numFn.setStorable(false);
        addAttribute(outputVal);
    }

    attributeAffects(inputVal, outputVal);

    return MStatus();
}

MStatus BasicNode::compute(const MPlug &plug, MDataBlock &data) {

    if (plug == outputVal)
    {
        double inp = data.inputValue(inputVal).asDouble();

        MGlobal::displayInfo(MString("Input is: ") + inp);
    }

    return MStatus();
}

//
//  IIRCombFilter.cpp
//  PROJECT1
//
//  Created by Som on 24/01/16.
//
//

#include <iostream>
#include <cmath>

#include "IIRCombFilter.h"

IIRCombFilter::IIRCombFilter() {
    this->reset();
}

IIRCombFilter::~IIRCombFilter() {
    this->reset();
}

void IIRCombFilter::processFilter(float **inputAudioData, float **outputAudioData, CAudioFileIf::FileSpec_t spec) {
    
}

void IIRCombFilter::setDelayLineInSecs(float paramVal) {
    delayLineInSecs = paramVal;
}

void IIRCombFilter::setWeight(float paramVal) {
	if (fabs(paramVal) > 1)
	{
		std::cout << "Incorrect parameter value for filter weight. Should be <= 1";
		exit(0);
	}
    weight = paramVal;
}

//
//  IIRCombFilter.cpp
//  PROJECT1
//
//  Created by Som on 24/01/16.
//
//

#include <stdio.h>

#include "IIRCombFilter.h"

IIRCombFilter::IIRCombFilter() {
    this->reset();
}

IIRCombFilter::~IIRCombFilter() {
    this->reset();
}

void IIRCombFilter::processFilter(float **inputAudioData, float **ouputAudioData, int numChannels) {
    
}

void IIRCombFilter::setDelayLineInSecs(float paramVal) {
    delayLineInSecs = paramVal;
}

void IIRCombFilter::setWeight(float paramVal) {
    weight = paramVal;
}

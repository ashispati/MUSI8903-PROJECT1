//
//  FIRCombFilter.cpp
//  PROJECT1
//
//  Created by Som on 24/01/16.
//
//

#include <stdio.h>

#include "FIRCombFilter.h"

FIRCombFilter::FIRCombFilter() {
    this->reset();
}

FIRCombFilter::~FIRCombFilter() {
    this->reset();
}

void FIRCombFilter::processFilter(float **inputAudioData, float **ouputAudioData, int numChannels) {
    
}

void FIRCombFilter::setDelayLineInSecs(float paramVal) {
    delayLineInSecs = paramVal;
}

void FIRCombFilter::setWeight(float paramVal) {
    weight = paramVal;
}


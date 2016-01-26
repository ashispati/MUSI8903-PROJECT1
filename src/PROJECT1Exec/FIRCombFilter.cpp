//
//  FIRCombFilter.cpp
//  PROJECT1
//
//  Created by Som on 24/01/16.
//
//

#include <iostream>
#include <cmath>

#include "FIRCombFilter.h"

FIRCombFilter::FIRCombFilter() {
    this->reset();
}

FIRCombFilter::~FIRCombFilter() {
    this->reset();
}

void FIRCombFilter::processFilter(float **inputAudioData, float **outputAudioData, CAudioFileIf::FileSpec_t spec, long long iInFileLength) {
    
    //Initialize delay line
    long int delayLength = getDelayLineInSamples(spec.fSampleRateInHz);
    float *delayLine = new float(delayLength);
    
    //Implement filter
    for (int channelId = 0; channelId < spec.iNumChannels; channelId++) {
        for (int k = 0; k < delayLength; k++) {
            delayLine[k] = 0.0F;
        }
        for (int dataId = 0; dataId < iInFileLength; dataId++) {
            outputAudioData[channelId][dataId] = inputAudioData[channelId][dataId] + gain*delayLine[delayLength-1];
            
            for (int i = delayLength-1; i > 0 ; i--) {
                delayLine[i] = delayLine[i-1];
            }
            
            delayLine[0] = inputAudioData[channelId][dataId];
            
        }
    }
    
    free(delayLine);
}

void FIRCombFilter::setDelayLineInSecs(float paramVal) {
    delayLineInSecs = paramVal;
}

void FIRCombFilter::setGain(float paramVal) {
    gain = paramVal;
}


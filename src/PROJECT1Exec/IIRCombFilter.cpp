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
    //Initialize delay line
    long int delayLength = getDelayLineInSamples(spec.fSampleRateInHz);
    int delayLine[delayLength];
    
    //Implement filter
    int audioLength = (sizeof(inputAudioData)/sizeof(float))/spec.iNumChannels;
    for (int channelId = 0; channelId < spec.iNumChannels; channelId++) {
        for (int k = 0; k < delayLength; k++) {
            delayLine[k] = 0;
        }
        for (int dataId = 0; dataId < audioLength; dataId++) {
            outputAudioData[channelId][dataId] = inputAudioData[channelId][dataId] + weight*delayLine[delayLength-1];
            for (int i = 0; i < delayLength-1; i++) {
                delayLine[i+1] = delayLine[i];
            }
            delayLine[0] = outputAudioData[channelId][dataId];
        }
    }
}

void IIRCombFilter::setDelayLineInSecs(float paramVal) {
    delayLineInSecs = paramVal;
}

void IIRCombFilter::setWeight(float paramVal) {
	if (fabs(paramVal) > 1)
	{
		std::cout << "Incorrect parameter value for filter weight. Magnitude should be <= 1";
		exit(0);
	}
    weight = paramVal;
}

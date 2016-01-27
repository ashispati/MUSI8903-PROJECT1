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

FIRCombFilter::FIRCombFilter() {}

FIRCombFilter::~FIRCombFilter() {}

Error_t FIRCombFilter::process(float **inputBuffer, float **outputBuffer, int numSamples) {
    //Implement filter
    for (int channelId = 0; channelId < filterNumChannels; channelId++) {
        for (int dataId = 0; dataId < numSamples; dataId++) {
            outputBuffer[channelId][dataId] = inputBuffer[channelId][dataId] + gain*delayBuffer[channelId][delayLineInSamples-1];
			//std::cout << outputBuffer[channelId][dataId] << "\t" << inputBuffer[channelId][dataId] << "\t" << delayBuffer[channelId][delayLineInSamples - 1]<<std::endl;
            for (int i = delayLineInSamples-1; i > 0 ; i--) {
                delayBuffer[channelId][i] = delayBuffer[channelId][i-1];
            }
            
            delayBuffer[channelId][0] = inputBuffer[channelId][dataId];
            
        }
    }
    
    return kNoError;
}


Error_t FIRCombFilter::setDelayLineInSamples(long int paramVal)
{
    delayLineInSamples = paramVal;
	return kNoError;
}

Error_t FIRCombFilter::setGain(float paramVal)
{
    gain = paramVal;
	return kNoError;
}


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

IIRCombFilter::IIRCombFilter() {}

IIRCombFilter::~IIRCombFilter() {}

Error_t IIRCombFilter::process(float **inputBuffer, float **outputBuffer, int numSamples) {
    //Implement filter
    for (int channelId = 0; channelId < filterNumChannels; channelId++) {
        for (int dataId = 0; dataId < numSamples; dataId++) {
            outputBuffer[channelId][dataId] = inputBuffer[channelId][dataId] + gain*delayBuffer[channelId][delayLineInSamples-1];
            
            for (int i = delayLineInSamples-1; i > 0 ; i--) {
                delayBuffer[channelId][i] = delayBuffer[channelId][i-1];
            }
            
            delayBuffer[channelId][0] = outputBuffer[channelId][dataId];
            
        }
    }
    
    return kNoError;
}

void IIRCombFilter::setDelayLineInSamples(long int paramVal)
{
    delayLineInSamples = paramVal;
}

void IIRCombFilter::setGain(float paramVal) {
    if (fabs(paramVal) > 1)
    {
        std::cout << "Incorrect parameter value for filter gain. Magnitude should be <= 1" << std::endl;
        exit(0);
    }
    gain = paramVal;
}



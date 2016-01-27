
// standard headers
#include <iostream>
#include <cmath>

// project headers
#include "ErrorDef.h"
#include "MyProject.h"
#include "FIRCombFilter.h"
#include "IIRCombFilter.h"

static const char*  kCMyProjectBuildDate             = __DATE__;


CMyProject::CMyProject () {}


CMyProject::~CMyProject () {
    this->reset();
}

const int  CMyProject::getVersion (const Version_t eVersionIdx)
{
    int iVersion = 0;

    switch (eVersionIdx)
    {
    case kMajor:
        iVersion    = MyProject_VERSION_MAJOR;
        break;
    case kMinor:
        iVersion    = MyProject_VERSION_MINOR; 
        break;
    case kPatch:
        iVersion    = MyProject_VERSION_PATCH; 
        break;
    case kNumVersionInts:
        iVersion    = -1;
        break;
    }

    return iVersion;
}
const char*  CMyProject::getBuildDate ()
{
    return kCMyProjectBuildDate;
}

Error_t CMyProject::create(CMyProject*& pCMyProject, int type, float delayTimeInSecs, float gain, long int sampleRate, int numChannels)
{
	if (type == 0)
		pCMyProject = new FIRCombFilter();
	else if (type == 1)
		pCMyProject = new IIRCombFilter();
	else
		return kFunctionIllegalCallError;

	if (delayTimeInSecs < 0)
		return kFunctionInvalidArgsError;
    
    if (!pCMyProject)
        return kUnknownError;

    return pCMyProject->init(delayTimeInSecs, gain, sampleRate, numChannels);
    
	//return kNoError;
}

Error_t CMyProject::destroy (CMyProject*& pCMyProject)
{
    if (!pCMyProject)
        return kUnknownError;
    
    delete pCMyProject;
    pCMyProject = 0;

    return kNoError;

}

Error_t CMyProject::init(float delayTimeInSecs, float gainValue, long int sampleRate, int numChannels)
{
    //gain = gainValue;
	Error_t check;
	check = this->setGain(gainValue);
	if (check != kNoError)
		return check;
    filterSampleRate = sampleRate;
	check = this->setDelayLineInSamples(getDelayLineInSamples(sampleRate, delayTimeInSecs));
	if (check != kNoError)
		return check;
    filterNumChannels = numChannels;
    //delayLineInSamples = getDelayLineInSamples(sampleRate, delayTimeInSecs);
    
    //std::cout << delayLineInSamples << std::endl;
    
    delayBuffer = new float*[filterNumChannels];
    
    for(int i = 0; i < filterNumChannels; i++)
    {
        delayBuffer[i] = new float[delayLineInSamples];
    }
    
    for(int i = 0; i < filterNumChannels; i++) {
        for (int k = 0; k < delayLineInSamples; k++) {
            delayBuffer[i][k] = 0.0F;
        }
    }

    return kNoError;
}

Error_t CMyProject::reset () {
    
    //std::cout << delayBuffer[0][0] << std::endl;
    //std::cout << filterNumChannels << std::endl;
    for (int i = 0; i < filterNumChannels; i++)
    {
        delete[] delayBuffer[i];
    }
    delete[] delayBuffer;
    delayLineInSamples = 0;
	gain = 0.0;
    filterNumChannels = 0;
    filterSampleRate = 0;
    return kNoError;
}

long int CMyProject::getDelayLineInSamples()
{
	return delayLineInSamples;
}

float CMyProject::getGain()
{
	return gain;
}

//WHY ARE WE USING SET FUNCTIONS HERE WHEN THEY ARE VIRTUAL FUNCTIONS AND WE'RE EVENTUALLY OVERRIDING THEM IN ALL THE SUBCLASSES?
//
//										ATTENTION!!!!!
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Error_t CMyProject::setDelayLineInSamples(long int paramVal)
{
	delayLineInSamples = paramVal;
	return kNoError;
}

Error_t CMyProject::setGain(float paramVal)
{
	gain = paramVal;
	return kNoError;
}

long int CMyProject::getDelayLineInSamples(long int fs, float delayLineInSecs)
{
	return roundf(fs*delayLineInSecs);
}
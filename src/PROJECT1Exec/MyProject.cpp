
// standard headers

// project headers
#include "ErrorDef.h"

#include "MyProject.h"
#include "FIRCombFilter.h"
#include "IIRCombFilter.h"

static const char*  kCMyProjectBuildDate             = __DATE__;


CMyProject::CMyProject ()
{
    // this never hurts
    this->reset ();
}


CMyProject::~CMyProject ()
{
    this->reset ();
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

Error_t CMyProject::create(CMyProject*& pCMyProject, int type)
{
	if (type == 0)
		pCMyProject = new FIRCombFilter();
	else
		pCMyProject = new IIRCombFilter();

	if (!pCMyProject)
		return kUnknownError;


	return kNoError;
}

Error_t CMyProject::destroy (CMyProject*& pCMyProject)
{
    if (!pCMyProject)
        return kUnknownError;
    
    pCMyProject->reset ();
    
    delete pCMyProject;
    pCMyProject = 0;

    return kNoError;

}

Error_t CMyProject::init()
{
    // allocate memory

    // initialize variables and buffers

    return kNoError;
}

Error_t CMyProject::reset ()
{
    // reset buffers and variables to default values
	delayLineInSecs = 0.0;
	weight = 0.0;
    return kNoError;
}

float CMyProject::getDelayLineInSecs()
{
	return delayLineInSecs;
}

float CMyProject::getWeight()
{
	return weight;
}

void CMyProject::setDelayLineInSecs(float paramVal)
{
	delayLineInSecs = paramVal;
}

void CMyProject::setWeight(float paramVal)
{
	weight = paramVal;
}

long int CMyProject::getDelayLineInSamples(long int fs)
{
	return fs / delayLineInSecs;
}
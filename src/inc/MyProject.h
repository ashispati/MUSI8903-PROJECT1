#if !defined(__MyProject_hdr__)
#define __MyProject_hdr__

#include "ErrorDef.h"
#include "AudioFileIf.h"

#define MyProject_VERSION_MAJOR 1
#define MyProject_VERSION_MINOR 0
#define MyProject_VERSION_PATCH 0

class CMyProject
{
public:
    /*! version number */
    enum Version_t
    {
        kMajor,                         //!< major version number
        kMinor,                         //!< minor version number
        kPatch,                         //!< patch version number

        kNumVersionInts
    };

    static const int  getVersion (const Version_t eVersionIdx);
    static const char* getBuildDate ();

	static Error_t create(CMyProject*& pCKortIf, int type, float delayTimeInSecs, float gain, long int sampleRate, int numChannels);
	static Error_t destroy (CMyProject*& pCKortIf);
    
    Error_t init (float delayTimeInSecs, float gain, long int sampleRate, int numChannels);
    Error_t reset ();
    
    //get functions
	long int getDelayLineInSamples();
	float getGain();
	
	//filtering function
    //virtual void processFilter(float **inputAudioData, float **outputAudioData, CAudioFileIf::FileSpec_t spec, long long iInFileLength) = 0;
    virtual Error_t process (float **inputBuffer, float **outputBuffer, int numSamples) = 0;

protected:
    CMyProject ();
    virtual ~CMyProject ();
    
    long int delayLineInSamples;
    float gain;
    float** delayBuffer;
    long int filterSampleRate;
    int filterNumChannels;
    
	long int getDelayLineInSamples(long int fs, float delayLineInSecs);
    virtual Error_t setDelayLineInSamples(long int paramVal);
    virtual Error_t setGain(float paramVal);
    
};

#endif // #if !defined(__MyProject_hdr__)
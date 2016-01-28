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

	/*
		Create function creates an instance of the correct filter type
		as specified in the arguments.
	*/
	static Error_t create(CMyProject*& pCKortIf, int type, float delayTimeInSecs, float gain, long int sampleRate, int numChannels);

	/*
		Delete function calls the destructor.
	*/
	static Error_t destroy (CMyProject*& pCKortIf);
    
	/*
		Init() function assigns the data members accordingly. It is called
		from the create() method as well to initialize.
	*/
    Error_t init (float delayTimeInSecs, float gain, long int sampleRate, int numChannels);

	/*
		Clears all memory buffers and sets the data members to 0.
	*/
    Error_t reset ();
    
    //getter functions
	long int getDelayLineInSamples();
	float getGain();
	
	//virtual filtering function. Implemented in the inheriting subclasses.
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
    virtual Error_t setDelayLineInSamples(long int paramVal) = 0;
    virtual Error_t setGain(float paramVal) = 0;
    
};

#endif // #if !defined(__MyProject_hdr__)
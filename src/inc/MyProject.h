#if !defined(__MyProject_hdr__)
#define __MyProject_hdr__

#include "ErrorDef.h"

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

	static Error_t create(CMyProject*& pCKortIf, int type);
	static Error_t destroy (CMyProject*& pCKortIf);
    
    Error_t init (/*enter parameters here*/);
    Error_t reset ();

	float getDelayLineInSecs();
	float getWeight();
	//Set functions
	void setDelayLineInSecs(float paramVal);
	void setWeight(float paramVal);
	//filtering function
	virtual void processFilter(float **audioData, int numChannels) = 0;
    
    //virtual Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) = 0;

protected:
    CMyProject ();
    virtual ~CMyProject ();

private:
	float delayLineInSecs;
	float weight;
    
};

#endif // #if !defined(__MyProject_hdr__)




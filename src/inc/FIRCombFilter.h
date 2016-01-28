//
//  FIRCombFilter.h
//  PROJECT1
//
//  Created by Som on 24/01/16.
//
//

#ifndef FIRCombFilter_h
#define FIRCombFilter_h

#include "MyProject.h"

class FIRCombFilter : public CMyProject
{
public:
    FIRCombFilter();
    
    ~FIRCombFilter();
    
	/* The main filtering function. The FIR filter is implemented.
	inputs:
		inputBuffer: The buffer containing input data.
		outputBuffer: The buffer to which to write the filtered signal.
		numSamples: The number of samples.
	outputs:
		error codes
	*/
	Error_t process (float **inputBuffer, float **outputBuffer, int numSamples) override;
    
    Error_t setDelayLineInSamples(long int paramVal) override;
    Error_t setGain(float paramVal) override;
    
private:
    
};

#endif /* FIRCombFilter_h */

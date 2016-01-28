//
//  IIRCombFilter.h
//  PROJECT1
//
//  Created by Som on 24/01/16.
//
//

#ifndef IIRCombFilter_h
#define IIRCombFilter_h

#include "MyProject.h"

class IIRCombFilter : public CMyProject
{
public:
    IIRCombFilter();
    
    ~IIRCombFilter();
    
	/* The main filtering function. The IIR filter is implemented.
	inputs:
		inputBuffer: The buffer containing input data.
		outputBuffer: The buffer to which to write the filtered signal.
		numSamples: The number of samples.
	outputs:
		error codes
	*/    Error_t process (float **inputBuffer, float **outputBuffer, int numSamples) override;

	/*
		Setter functions for the filter parameters
	*/
    Error_t setDelayLineInSamples(long int paramVal) override;
    Error_t setGain(float paramVal) override;
    
private:

};


#endif /* IIRCombFilter_h */

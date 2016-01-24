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
    
    void processFilter(float **inputAudioData, float **outputAudioData, int numChannels) override;
    
    void setDelayLineInSecs(float paramVal) override;
    void setWeight(float paramVal) override;
    
private:
    
};


#endif /* IIRCombFilter_h */

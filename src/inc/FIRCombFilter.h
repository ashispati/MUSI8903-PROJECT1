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
    
    void processFilter(float **inputAudioData, float **outputAudioData, CAudioFileIf::FileSpec_t spec, long long iInFileLength) override;
    
    void setDelayLineInSecs(float paramVal) override;
    void setGain(float paramVal) override;
    
private:
    
};

#endif /* FIRCombFilter_h */

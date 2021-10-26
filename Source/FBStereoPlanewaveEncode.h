/*
  ==============================================================================

    FBStereoPlanewaveEncode.h
    Notes:
    1. 

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class FBStereoPlanewaveEncode
{
public:
    
    FBStereoPlanewaveEncode();
    ~FBStereoPlanewaveEncode();
    
    void stereoEncoding(const float* stereoLeftInput,
                        const float* stereoRightInput,
                        float leftPosition,
                        float rightPosition,
                        float elevationLevel,
                        float* ACN0Output,
                        float* ACN1Output,
                        float* ACN2Output,
                        float* ACN3Output,
                        int inputBufferSize);
    
private:
    
};

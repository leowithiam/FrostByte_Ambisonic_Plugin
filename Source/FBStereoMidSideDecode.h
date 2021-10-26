/*
  ==============================================================================

    FBStereoMidSideDecode.h
    Notes:
    1. 

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class FBStereoMidSideDecode
{
public:
    
    FBStereoMidSideDecode();
    ~FBStereoMidSideDecode();
    
    void stereoMidSideDecoding(const float* ACN0Input,
                               const float* ACN1Input,
                               const float* ACN2Input,
                               const float* ACN3Input,
                               float* midSignal,
                               float* leftOutput,
                               float* rightOutput,
                               int inputBufferSize);
    
private:
    
};

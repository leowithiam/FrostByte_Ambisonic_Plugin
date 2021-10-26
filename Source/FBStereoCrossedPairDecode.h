/*
  ==============================================================================

    FBStereoCrossedPairDecode.h
    Notes:
    1. 

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class FBStereoCrossedPairDecode
{
public:
    
    FBStereoCrossedPairDecode();
    ~FBStereoCrossedPairDecode();
    
    void stereoCrossedPairDecoding(const float* ACN0Input,
                                   const float* ACN1Input,
                                   const float* ACN2Input,
                                   const float* ACN3Input,
                                   float* leftOutput,
                                   float* rightOutput,
                                   int inputBufferSize);
    
private:
    
};

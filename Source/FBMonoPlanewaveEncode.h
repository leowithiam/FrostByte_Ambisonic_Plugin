/*
  ==============================================================================

    FBMonoPlanewaveEncode.h
    Notes:
    1. monoInput in monoEncoding method is made const because .getReadPointer() method returns a const value

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class FBMonoPlanewaveEncode
{
public:
    
    FBMonoPlanewaveEncode();
    ~FBMonoPlanewaveEncode();
    
    void monoEncoding(const float* monoInput,
                      float azimuthLevel,
                      float elevationLevel,
                      float* ACN0Output,
                      float* ACN1Output,
                      float* ACN2Output,
                      float* ACN3Output,
                      int inputBufferSize);
    
private:
    
};

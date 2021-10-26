/*
  ==============================================================================

    FBStereoMidSideDecode.cpp
    Notes:
    1. 

  ==============================================================================
*/

#include "FBStereoMidSideDecode.h"

FBStereoMidSideDecode::FBStereoMidSideDecode()
{
    
}

FBStereoMidSideDecode::~FBStereoMidSideDecode()
{
    
}

void FBStereoMidSideDecode::stereoMidSideDecoding(const float* ACN0Input,
                                                  const float* ACN1Input,
                                                  const float* ACN2Input,
                                                  const float* ACN3Input,
                                                  float* midSignal,
                                                  float* leftOutput,
                                                  float* rightOutput,
                                                  int inputBufferSize)
{
    // Blumlein Mid-Side decode matrix
    for (int sample = 0; sample < inputBufferSize; sample++)
    {
        midSignal[sample] = (ACN0Input[sample] * sqrt(2)) + ACN3Input[sample];
        leftOutput[sample] = (midSignal[sample] + ACN1Input[sample]) * 0.5;
        rightOutput[sample] = (midSignal[sample] - ACN1Input[sample]) * 0.5;
    }
}

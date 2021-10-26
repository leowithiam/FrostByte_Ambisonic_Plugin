/*
  ==============================================================================

    FBStereoCrossedPairDecode.cpp
    Notes:
    1. 

  ==============================================================================
*/

#include "FBStereoCrossedPairDecode.h"

FBStereoCrossedPairDecode::FBStereoCrossedPairDecode()
{
    
}

FBStereoCrossedPairDecode::~FBStereoCrossedPairDecode()
{
    
}

void FBStereoCrossedPairDecode::stereoCrossedPairDecoding(const float* ACN0Input,
                                                          const float* ACN1Input,
                                                          const float* ACN2Input,
                                                          const float* ACN3Input,
                                                          float* leftOutput,
                                                          float* rightOutput,
                                                          int inputBufferSize)
{
    // Blumlein Crossed Pair decode matrix
    for (int sample = 0; sample < inputBufferSize; sample++)
    {
        leftOutput[sample] = (ACN3Input[sample] + ACN1Input[sample])/(sqrt(2));
        rightOutput[sample] = (ACN3Input[sample] - ACN1Input[sample])/(sqrt(2));
    }
}

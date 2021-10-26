/*
  ==============================================================================

    FBMonoPlanewaveEncode.cpp
    Notes:
    1. 

  ==============================================================================
*/

#include "FBMonoPlanewaveEncode.h"

FBMonoPlanewaveEncode::FBMonoPlanewaveEncode()
{
    
}

FBMonoPlanewaveEncode::~FBMonoPlanewaveEncode()
{
    
}

void FBMonoPlanewaveEncode::monoEncoding(const float* monoInput,
                                         float azimuthLevel,
                                         float elevationLevel,
                                         float* ACN0Output,
                                         float* ACN1Output,
                                         float* ACN2Output,
                                         float* ACN3Output,
                                         int inputBufferSize)
{
    // Mono planewave calculations
    // Azimuth
    azimuthLevel = (azimuthLevel * ((M_PI) / 180.0f)) * -1;
    
    // Elevation
    elevationLevel *= (M_PI / 180.0f);
    
    // Mono planewave matrix
    for (int sample = 0; sample < inputBufferSize; sample++)
    {
        ACN0Output[sample] = monoInput[sample] * (1/sqrt(2));
        ACN1Output[sample] = monoInput[sample] * (sin(azimuthLevel) * cos(elevationLevel));
        ACN2Output[sample] = monoInput[sample] * (sin(elevationLevel));
        ACN3Output[sample] = monoInput[sample] * (cos(azimuthLevel) * cos(elevationLevel));
    }
}

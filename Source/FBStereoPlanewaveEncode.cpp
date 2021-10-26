/*
  ==============================================================================

    FBStereoPlanewaveEncode.cpp
    Notes:
    1. 

  ==============================================================================
*/

#include "FBStereoPlanewaveEncode.h"

FBStereoPlanewaveEncode::FBStereoPlanewaveEncode()
{
    
}

FBStereoPlanewaveEncode::~FBStereoPlanewaveEncode()
{
    
}

void FBStereoPlanewaveEncode::stereoEncoding(const float* stereoLeftInput,
                                             const float* stereoRightInput,
                                             float leftPosition,
                                             float rightPosition,
                                             float elevationLevel,
                                             float* ACN0Output,
                                             float* ACN1Output,
                                             float* ACN2Output,
                                             float* ACN3Output,
                                             int inputBufferSize)
{
    // Stereo planewave calculations
    // Stereo width
    leftPosition = (leftPosition * ((M_PI) / 180.0f));
    rightPosition = (rightPosition * ((M_PI) / 180.0f)) * -1;
    
    // Elevation
    elevationLevel *= (M_PI / 180.0f);
    

    // Stereo planewave encode matrix
    for (int sample = 0; sample < inputBufferSize; sample++)
    {
        ACN0Output[sample] = (stereoLeftInput[sample] * (1/sqrt(2))) + (stereoRightInput[sample] * (1/sqrt(2)));
        
        ACN1Output[sample] = (stereoLeftInput[sample] * (sin(leftPosition) * cos(elevationLevel))) + (stereoRightInput[sample] * (sin(rightPosition) * cos(elevationLevel)));
        
        ACN2Output[sample] = (stereoLeftInput[sample] * (sin(elevationLevel))) + (stereoRightInput[sample] * (sin(elevationLevel)));
        
        ACN3Output[sample] = (stereoLeftInput[sample] * (cos(leftPosition) * cos(elevationLevel))) + (stereoRightInput[sample] * (cos(rightPosition) * cos(elevationLevel)));
    }
     
}

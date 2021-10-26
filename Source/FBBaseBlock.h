/*
  ==============================================================================

    FBBaseBlock.h
    Notes:
    1. 

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "FBSettings.h"

class FBBaseBlock : public juce::Component
{
public:
    
    FBBaseBlock(FrostByteAudioProcessor* inputProcessor);
    ~FBBaseBlock();
    
    void paint(juce::Graphics& g) override;
    
protected:
    
    FrostByteAudioProcessor* mProcessor;
    
};

/*
  ==============================================================================

    FBTitleBlock.h
    Notes:
    1.

  ==============================================================================
*/

#pragma once

#include "FBBaseBlock.h"

class FBTitleBlock : public FBBaseBlock
{
public:
    
    FBTitleBlock(FrostByteAudioProcessor* inputProcessor);
    ~FBTitleBlock();
    
    void paint(juce::Graphics& g) override;
    
private:
    
    
    // FrostByte_Title_Text Image object declaration
    juce::Image mFBTitle_Text;
    
};

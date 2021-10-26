/*
  ==============================================================================

    FBBaseBlock.cpp
    Notes:
    1.

  ==============================================================================
*/

#include "FBBaseBlock.h"

FBBaseBlock::FBBaseBlock(FrostByteAudioProcessor* inputProcessor) : mProcessor(inputProcessor)
{
    
}

FBBaseBlock::~FBBaseBlock()
{
    
}

void FBBaseBlock::paint(juce::Graphics& g)
{
    /*
    // Editor formatting
    g.setColour(juce::Colours::lightgrey);
    g.fillAll();
    
    // Border formatting
    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());
     */
}

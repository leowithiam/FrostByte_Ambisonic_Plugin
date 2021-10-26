/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
    Notes:
    1.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FBMainBlock.h"
#include "FBLookAndFeel.h"

//==============================================================================
/**
*/
class FrostByteAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FrostByteAudioProcessorEditor (FrostByteAudioProcessor&);
    ~FrostByteAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    // FrostByte_Background Image object declaration
    juce::Image mBackgroundImage;
    
    // Block smart pointer object declaration
    std::unique_ptr<FBMainBlock> mMainBlock;
    
    // FBLookAndFeel smart pointer object declaration
    std::unique_ptr<FBLookAndFeel> mLookAndFeel;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FrostByteAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrostByteAudioProcessorEditor)
};

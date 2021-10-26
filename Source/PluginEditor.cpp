/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
    Notes:
    1.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FrostByteAudioProcessorEditor::FrostByteAudioProcessorEditor (FrostByteAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Formatting size of editor to equal size of FBMainBlock smart pointer object
    setSize (MAIN_BlOCK_WIDTH,
             MAIN_BLOCK_HEIGHT);
    
    // FBMainBlock smart pointer object instantiation
    mMainBlock = std::make_unique<FBMainBlock>(&audioProcessor);
    
    // FBMainBlock smart pointer object initialisation
    addAndMakeVisible(mMainBlock.get());
    
    // FBLookAndFeel smart pointer object instantiation
    mLookAndFeel = std::make_unique<FBLookAndFeel>();
    
    // FBLookAndFeel smart pointer object initialisation
    juce::LookAndFeel::setDefaultLookAndFeel(mLookAndFeel.get());
    
    // FrostByte_Background Image object instantiation
    mBackgroundImage = juce::ImageCache::getFromMemory(BinaryData::FrostByte_Background_png,
                                                       BinaryData::FrostByte_Background_pngSize);
}

FrostByteAudioProcessorEditor::~FrostByteAudioProcessorEditor()
{
}

//==============================================================================
void FrostByteAudioProcessorEditor::paint (juce::Graphics& g)
{
    //  // FrostByte_Background Image object initialisation
    g.drawImage(mBackgroundImage, getLocalBounds().toFloat());
}

void FrostByteAudioProcessorEditor::resized()
{

}

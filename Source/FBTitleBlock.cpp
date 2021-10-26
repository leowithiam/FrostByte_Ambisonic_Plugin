/*
  ==============================================================================

    FBTitleBlock.cpp
    Notes:
    1.

  ==============================================================================
*/

#include "FBTitleBlock.h"

FBTitleBlock::FBTitleBlock(FrostByteAudioProcessor* inputProcessor) : FBBaseBlock(inputProcessor)
{
    // Formatting size and placement of FBTitleBlock object
    setSize(TITLE_BlOCK_WIDTH,
            TITLE_BLOCK_HEIGHT);
    
    // FrostByte_Title_Text Image object instantiation
    mFBTitle_Text = juce::ImageCache::getFromMemory(BinaryData::FrostByte_Title_Text_png,
                                                    BinaryData::FrostByte_Title_Text_pngSize);
    
}

FBTitleBlock::~FBTitleBlock()
{
    
}

void FBTitleBlock::paint(juce::Graphics& g)
{
    
    // FrostByte_Title_Text Image object initialisation
    /*
    g.drawImage(mFBTitle_Text,
                -55,
                0,
                400,
                getHeight(),
                0,
                0,
                6400,
                800);
     */
    
    
    // FrostByte_Title_Text Image object initialisation
    g.drawImage(mFBTitle_Text,
                98,
                0,
                400,
                getHeight(),
                0,
                0,
                6400,
                800);
     
    
    /*
    // Title text formatting
    FBBaseBlock::paint(g);
    g.setColour (juce::Colours::black);
    g.setFont (50.0f);
    g.drawText("FROSTBYTE", 0, 0, 400, getHeight(), juce::Justification::centred);
     */
     
     
}

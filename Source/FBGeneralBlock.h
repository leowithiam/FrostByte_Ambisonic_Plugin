/*
  ==============================================================================

    FBGeneralBlock.h
    Notes
    1.

  ==============================================================================
*/

#pragma once

#include "FBBaseBlock.h"

class FBGeneralBlock : public FBBaseBlock
{
public:
    
    FBGeneralBlock(FrostByteAudioProcessor* inputProcessor);
    ~FBGeneralBlock();
    
    void paint(juce::Graphics& g) override;
    
    // Listener method declarations
    void encodeTypeChanged();
    void decodeTypeChanged();
    
private:
    
    // Object declarations
    // ComboBox object declarations
    juce::ComboBox mEncodeMenu;
    juce::ComboBox mDecodeMenu;
    
    // Slider object declarations
    juce::Slider mAzimuthSlider;
    juce::Slider mElevationSlider;
    juce::Slider mStereoWidthSlider;
    
    // Slider Label object declarations
    juce::Label mAzimuthSliderLabel;
    juce::Label mElevationSliderLabel;
    juce::Label mStereoWidthSliderLabel;
    
    // Data member declarations
    float mAzimuthValue;
    float mElevationValue;
    float mStereoWidthValue;
    float mAzimuthPositionX;
    float mAzimuthPositionY;
    float mLeftPositionX;
    float mLeftPositionY;
    float mRightPositionX;
    float mRightPositionY;
    
};



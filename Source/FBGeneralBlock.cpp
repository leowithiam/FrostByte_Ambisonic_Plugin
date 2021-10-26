/*
  ==============================================================================

    FBGeneralBlock.cpp
    Notes:
    1. Calculations for planewave ellipses azimuth rotation:
    X_Position = Centre + cos(current_azimuth_slider_value * conversion_to_radians - 90_degrees_in_radians_to_rotate_x-axis) * radius_of_circle
    Y_Position = Centre + sin(current_azimuth_slider_value * conversion_to_radians - 90_degrees_in_radians_to_rotate_y-axis) * radius_of_circle

  ==============================================================================
*/

#include "FBGeneralBlock.h"

FBGeneralBlock::FBGeneralBlock(FrostByteAudioProcessor* inputProcessor) : FBBaseBlock(inputProcessor)
{
    // Formatting size and placement of FBGeneralBlock object
    setSize(GENERAL_BLOCK_WIDTH,
            GENERAL_BLOCK_HEIGHT);
    
    // AudioProcessor Parameter pointer object retrievals
    auto& parameters = inputProcessor->getParameters();
    juce::AudioParameterInt* encodeType = (juce::AudioParameterInt*)parameters.getUnchecked(3);
    juce::AudioParameterInt* decodeType = (juce::AudioParameterInt*)parameters.getUnchecked(4);
    
    // Encode ComboBox object initialisation
    mEncodeMenu.setBounds(50, 0, 225, 30);
    mEncodeMenu.addItem("Mono Planewave Encode", 1);
    mEncodeMenu.addItem("Stereo Planewave Encode", 2);
    mEncodeMenu.setSelectedId(*encodeType);
    
    // Linking encode ComboBox object to encode Parameter pointer object
    mEncodeMenu.onChange  = [this, encodeType]
    {
        encodeType->beginChangeGesture();
        encodeTypeChanged();
        *encodeType = mEncodeMenu.getSelectedId();
        encodeType->endChangeGesture();
    };
    
    // Setting encode ComboBox object to current encode Parameter pointer object value when UI is opened
    mEncodeMenu.setSelectedId(*encodeType);
    
    // Displaying encode ComboBox object onscreen
    //addAndMakeVisible(mEncodeMenu);
    
    // Decode Combox object initialisation
    //mDecodeMenu.setBounds(325, 0, 225, 30);
    mDecodeMenu.setBounds(190, 0, 220, 30);
    mDecodeMenu.addItem("Stereo Mid-Side Decode", 1);
    mDecodeMenu.addItem("Stereo Crossed Pair Decode", 2);
    mDecodeMenu.addItem("1st Order AmbiX", 3);
    mDecodeMenu.setSelectedId(*decodeType);
    
    // Linking decode ComboBox object to decode Parameter pointer object
    mDecodeMenu.onChange  = [this, decodeType]
    {
        decodeType->beginChangeGesture();
        //decodeTypeChanged();
        *decodeType = mDecodeMenu.getSelectedId();
        decodeType->endChangeGesture();
    };
    
    // Setting decode ComboBox object to current decode Parameter pointer object value when UI is opened
    mDecodeMenu.setSelectedId(*decodeType);
    
    // Displaying decode ComboBox object onscreen
    addAndMakeVisible(mDecodeMenu);
}

FBGeneralBlock::~FBGeneralBlock()
{
    
}

void FBGeneralBlock::paint(juce::Graphics& g)
{
    // Visual planewave spatial representation
    // Drawing ellipse for isotropic Ambisonics sphere
    g.setColour(FBColour_5);
    g.drawEllipse(150, 40, 300, 300, 2);
    g.fillEllipse(150, 40, 300, 300);
    
    // Formatting for drawing planewave ellipses
    float elevationValue = mElevationValue;
    g.setColour(FBColour_1);
    
    // if statement dependent on encode ComboBox object state
    // When encode ComboBox SelectedId == 1, mono planwave encode ellipse representation is executed
    if (mEncodeMenu.getSelectedId() == 1)
    {
        // Nested if statement dependent on elevation value retrieved from elevation Slider object
        if (elevationValue >= 0)
        {
            // if elevation is positive, ellipse is not filled
            float elevationNewValue = elevationValue * -1;
            float elevationModifier = ((elevationNewValue * (M_PI / 180)) * 86) + (270 / 2);
            
            mAzimuthPositionX = (150 + 300/2 + cos(mAzimuthValue * (M_PI /180) - M_PI/2) * elevationModifier);
            mAzimuthPositionY = (40 + 300/2 + sin(mAzimuthValue * (M_PI / 180) - M_PI/2) * elevationModifier);
            
            g.drawEllipse(mAzimuthPositionX - 30/2, mAzimuthPositionY - 30/2, 30, 30, 2);
            repaint();
        }
        
        else
        {
            // else elevation is negative, ellipse is filled
            float elevationModifier = ((elevationValue * (M_PI / 180)) * 86) + (270 / 2);
            
            mAzimuthPositionX = (150 + 300/2 + cos(mAzimuthValue * (M_PI /180) - M_PI/2) * elevationModifier);
            mAzimuthPositionY = (40 + 300/2 + sin(mAzimuthValue * (M_PI / 180) - M_PI/2) * elevationModifier);
            
            g.setColour(FBColour_8);
            g.fillEllipse(mAzimuthPositionX - 30/2, mAzimuthPositionY - 30/2, 30, 30);
            g.setColour(FBColour_1);
            g.drawEllipse(mAzimuthPositionX - 30/2, mAzimuthPositionY - 30/2, 30, 30, 2);
            
            repaint();
        }
    }
    
    // When encode ComboBox SelectedId == 2, stereo planwave encode ellipse representation is executed
    else if (mEncodeMenu.getSelectedId() == 2)
    {
        // Nested if statement dependent on elevation value retrieved from elevation Slider object
        if (elevationValue >= 0)
        {
            // if elevation is positive, ellipses are not filled
            float elevationNewValue = elevationValue * -1;
            float elevationModifier = ((elevationNewValue * (M_PI / 180)) * 86) + (270 / 2);
            
            mLeftPositionX = (150 + 300/2 + cos((-mStereoWidthValue) * (M_PI /180) - M_PI/2) * elevationModifier);
            mLeftPositionY = (40 + 300/2 + sin((-mStereoWidthValue) * (M_PI / 180) - M_PI/2) * elevationModifier);
            
            g.setColour(FBColour_9);
            g.drawEllipse(mLeftPositionX - 30/2, mLeftPositionY - 30/2, 30, 30, 2);
            
            
            mRightPositionX = (150 + 300/2 + cos(mStereoWidthValue * (M_PI /180) - M_PI/2) * elevationModifier);
            mRightPositionY = (40 + 300/2 + sin(mStereoWidthValue * (M_PI / 180) - M_PI/2) *  elevationModifier);
            
            g.setColour(FBColour_11);
            g.drawEllipse(mRightPositionX - 30/2, mRightPositionY - 30/2, 30, 30, 2);
            
            repaint();
        }
        
        else
        {
            // else elevation is negative, ellipses are filled
            float elevationModifier = ((elevationValue * (M_PI / 180)) * 86) + (270 / 2);
            
            mLeftPositionX = (150 + 300/2 + cos((-mStereoWidthValue) * (M_PI /180) - M_PI/2) * elevationModifier);
            mLeftPositionY = (40 + 300/2 + sin((-mStereoWidthValue) * (M_PI / 180) - M_PI/2) * elevationModifier);
            
            g.setColour(FBColour_10);
            g.fillEllipse(mLeftPositionX - 30/2, mLeftPositionY - 30/2, 30, 30);
            g.setColour(FBColour_9);
            g.drawEllipse(mLeftPositionX - 30/2, mLeftPositionY - 30/2, 30, 30, 2);
            
            
            mRightPositionX = (150 + 300/2 + cos(mStereoWidthValue * (M_PI /180) - M_PI/2) * elevationModifier);
            mRightPositionY = (40 + 300/2 + sin(mStereoWidthValue * (M_PI / 180) - M_PI/2) *  elevationModifier);
            
            g.setColour(FBColour_12);
            g.fillEllipse(mRightPositionX - 30/2, mRightPositionY - 30/2, 30, 30);
            g.setColour(FBColour_11);
            g.drawEllipse(mRightPositionX - 30/2, mRightPositionY - 30/2, 30, 30, 2);
            
            repaint();
        }
        
    }
    
}

// method to execute when encode ComboBox object state is altered
void FBGeneralBlock::encodeTypeChanged()
{
    // AudioProcessor Parameter pointer object retrievals
    auto& parameters = mProcessor->getParameters();
    juce::AudioParameterFloat* azimuthParameter = (juce::AudioParameterFloat*)parameters.getUnchecked(0);
    juce::AudioParameterFloat* elevationParameter = (juce::AudioParameterFloat*)parameters.getUnchecked(1);
    juce::AudioParameterFloat* stereoWidthParameter = (juce::AudioParameterFloat*)parameters.getUnchecked(2);
    
    // When encode ComboBox object is changed to mono planewave encode
    if (mEncodeMenu.getSelectedId() == 1)
    {
        // Cleaning UI
        // Verifying whether stereo planewave encode paramters are displayed, and removed if so
        if (mStereoWidthSlider.isVisible() == true)
        {
            mStereoWidthSlider.setVisible(false);
            mStereoWidthSliderLabel.setVisible(false);
        }
        
        // Azimuth Slider Label object initialisation
        mAzimuthSliderLabel.setFont(FBFont_2);
        mAzimuthSliderLabel.setColour(0x1000281, FBColour_1);
        mAzimuthSliderLabel.setText("AZIMUTH", juce::dontSendNotification);
        mAzimuthSliderLabel.attachToComponent(&mAzimuthSlider, false);
        mAzimuthSliderLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(mAzimuthSliderLabel);
        
        // Azimuth Slider object initialisation
        mAzimuthSlider.setBounds(25, ((0.5 * getHeight()) - 50), 100, 100);
        mAzimuthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        mAzimuthSlider.setColour(0x1001400, FBColour_1);
        mAzimuthSlider.setColour(0x1001700, FBColour_2);
        mAzimuthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        mAzimuthSlider.setRange(azimuthParameter->range.start, azimuthParameter->range.end);
        mAzimuthSlider.setValue(*azimuthParameter);
        
        // Linking azimuth Slider object to azimuth Parameter pointer object
        mAzimuthSlider.onDragStart = [azimuthParameter]
        {
            azimuthParameter->beginChangeGesture();
        };
        mAzimuthSlider.onValueChange = [this, azimuthParameter]
        {
            *azimuthParameter = mAzimuthSlider.getValue();
            mAzimuthValue = mAzimuthSlider.getValue();
        };
        mAzimuthSlider.onDragEnd = [azimuthParameter]
        {
            azimuthParameter->endChangeGesture();
        };
        
        // Additional azimuth Slider object functionality
        mAzimuthSlider.setDoubleClickReturnValue(true, 0.0f);
        mAzimuthSlider.setNumDecimalPlacesToDisplay(2);
        
        // Displaying azimuth Slider object onscreen
        addAndMakeVisible(&mAzimuthSlider);
        
        // Elevation Slider Label object initialisation
        mElevationSliderLabel.setFont(FBFont_2);
        mElevationSliderLabel.setColour(0x1000281, FBColour_1);
        mElevationSliderLabel.setText("ELEVATION", juce::dontSendNotification);
        mElevationSliderLabel.attachToComponent(&mElevationSlider, false);
        mElevationSliderLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(mElevationSliderLabel);
        
        // Elevation Slider object initialisation
        mElevationSlider.setBounds(475, ((0.5 * getHeight()) - 50), 100, 100);
        mElevationSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        mElevationSlider.setColour(0x1001400, FBColour_1);
        mElevationSlider.setColour(0x1001700, FBColour_2);
        mElevationSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        mElevationSlider.setRange(elevationParameter->range.start, elevationParameter->range.end);
        mElevationSlider.setValue(*elevationParameter);
        
        // Linking elevation Slider object to elevation Parameter pointer object
        mElevationSlider.onDragStart = [elevationParameter]
        {
            elevationParameter->beginChangeGesture();
        };
        mElevationSlider.onValueChange = [this, elevationParameter]
        {
            *elevationParameter = mElevationSlider.getValue();
            mElevationValue = mElevationSlider.getValue();
        };
        mElevationSlider.onDragEnd = [elevationParameter]
        {
            elevationParameter->endChangeGesture();
        };
        
        // Additional elevation Slider object functionality
        mElevationSlider.setDoubleClickReturnValue(true, 0.0f);
        mElevationSlider.setNumDecimalPlacesToDisplay(2);
        
        // Displaying elevation Slider object onscreen
        addAndMakeVisible(&mElevationSlider);
    }
    
    // When encode ComboBox object is changed to stereo planewave encode
    else if (mEncodeMenu.getSelectedId() == 2)
    {
        // Cleaning UI
        // Verifying whether mono planewave encode paramters are displayed, and removed if so
        if (mAzimuthSlider.isVisible() == true)
        {
            mAzimuthSlider.setVisible(false);
            mAzimuthSliderLabel.setVisible(false);
        }
        
        // Stereo Width Slider Label object initialisation
        mStereoWidthSliderLabel.setFont(FBFont_2);
        mStereoWidthSliderLabel.setColour(0x1000281, FBColour_1);
        mStereoWidthSliderLabel.setText("WIDTH", juce::dontSendNotification);
        mStereoWidthSliderLabel.attachToComponent(&mStereoWidthSlider, false);
        mStereoWidthSliderLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(mStereoWidthSliderLabel);
        
        // Stereo Width Slider object initialisation
        mStereoWidthSlider.setBounds(25, ((0.5 * getHeight()) - 50), 100, 100);
        mStereoWidthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        mStereoWidthSlider.setColour(0x1001400, FBColour_1);
        mStereoWidthSlider.setColour(0x1001700, FBColour_2);
        mStereoWidthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        mStereoWidthSlider.setRange(stereoWidthParameter->range.start, stereoWidthParameter->range.end);
        mStereoWidthSlider.setValue(*stereoWidthParameter);
        
        // Linking stereo width Slider object to stereo width Parameter pointer object
        mStereoWidthSlider.onDragStart = [stereoWidthParameter]
        {
            stereoWidthParameter->beginChangeGesture();
        };
        mStereoWidthSlider.onValueChange = [this, stereoWidthParameter]
        {
            *stereoWidthParameter = mStereoWidthSlider.getValue();
            mStereoWidthValue = mStereoWidthSlider.getValue();
        };
        mStereoWidthSlider.onDragEnd = [stereoWidthParameter]
        {
            stereoWidthParameter->endChangeGesture();
        };
        
        // Additional stereo width Slider object functionality
        mStereoWidthSlider.setDoubleClickReturnValue(true, 0.0f);
        mStereoWidthSlider.setNumDecimalPlacesToDisplay(2);
        
        // Displaying stereo width Slider object onscreen
        addAndMakeVisible(&mStereoWidthSlider);
        
        // Elevation Slider Label object initialisation
        mElevationSliderLabel.setFont(FBFont_2);
        mElevationSliderLabel.setColour(0x1000281, FBColour_1);
        mElevationSliderLabel.setText("ELEVATION", juce::dontSendNotification);
        mElevationSliderLabel.attachToComponent(&mElevationSlider, false);
        mElevationSliderLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(mElevationSliderLabel);
        
        // Elevation Slider object initialisation
        mElevationSlider.setBounds(475, ((0.5 * getHeight()) - 50), 100, 100);
        mElevationSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        mElevationSlider.setColour(0x1001400, FBColour_1);
        mElevationSlider.setColour(0x1001700, FBColour_2);
        mElevationSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        mElevationSlider.setRange(elevationParameter->range.start, elevationParameter->range.end);
        mElevationSlider.setValue(*elevationParameter);
        
        // Linking elevation Slider object to elevation Parameter pointer object
        mElevationSlider.onDragStart = [elevationParameter]
        {
            elevationParameter->beginChangeGesture();
        };
        mElevationSlider.onValueChange = [this, elevationParameter]
        {
            *elevationParameter = mElevationSlider.getValue();
            mElevationValue = mElevationSlider.getValue();
        };
        mElevationSlider.onDragEnd = [elevationParameter]
        {
            elevationParameter->endChangeGesture();
        };
        
        // Additional elevation Slider object functionality
        mElevationSlider.setDoubleClickReturnValue(true, 0.0f);
        mElevationSlider.setNumDecimalPlacesToDisplay(2);
        
        // Displaying elevation Slider object onscreen
        addAndMakeVisible(&mElevationSlider);
    }
}

// Potential additional functionality dependent on decode ComboBox state
// method to execute when decode ComboBox object state is altered
void FBGeneralBlock::decodeTypeChanged()
{
    if (mDecodeMenu.getSelectedId() == 1)
    {
        
    }
    
    else if (mDecodeMenu.getSelectedId() == 2)
    {
        
    }
    
    else if (mDecodeMenu.getSelectedId() == 3)
    {
        
    }
    
}

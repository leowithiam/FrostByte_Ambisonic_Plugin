/*
  ==============================================================================

    FBLookAndFeel.h
    Notes:
    1.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "FBSettings.h"

class FBLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    FBLookAndFeel()
    {
        // FrostByte_Sliders_Temp Image object instantiation
        mFBSliderImage = juce::ImageCache::getFromMemory(BinaryData::FrostByte_Sliders_Temp_png,
                                                         BinaryData::FrostByte_Sliders_Temp_pngSize);
        
    }
    
    ~FBLookAndFeel()
    {
        
    }
    
    // ComboBox LookAndFeel customisation
    // Customising LookAndFeel font
    juce::Font getLabelFont(juce::Label& label) override
    {
        return FBFont_2;
    }
    
    // Reconstructing ComboBox object drop down menu interface
    void drawPopupMenuItem (juce::Graphics& g,
                            const juce::Rectangle<int>& area,
                            bool isSeparator,
                            bool isActive,
                            bool isHighlighted,
                            bool isTicked,
                            bool hasSubMenu,
                            const juce::String& text,
                            const juce::String& shortcutKeyText,
                            const juce::Drawable* icon,
                            const juce::Colour* textColour) override
    {
        juce::Rectangle<int> r (area);
        juce::Colour fillColour = isHighlighted ? FBColour_6 : FBColour_5;
        
        g.setColour(fillColour);
        g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() -1);
        
        juce::Colour myTextColour = isTicked ? FBColour_7 : FBColour_3;
        g.setColour(myTextColour);
        g.setFont(FBFont_2);
        
        r.setLeft(10);
        r.setY(1);
        g.drawFittedText(text, r, juce::Justification::left, 1);
        
    }
    
    //Reconstructing ComboBox object button interface
    void drawComboBox (juce::Graphics& g,
                       int width,
                       int height,
                       bool isButtonDown,
                       int buttonX,
                       int buttonY,
                       int buttonW,
                       int buttonH,
                       juce::ComboBox& box) override
    {
        const float cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds (0, 0, width, height);
        
        g.setColour(FBColour_4);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);
        
        juce::Rectangle<int> arrow (width - 30, 0, 20, height);
        
        juce::Path path;
        
        path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
        path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
        path.lineTo(arrow.toFloat().getRight() - 3.0, arrow.toFloat().getCentreY() - 2.0f);
        
               juce::Colour arrowColour = box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
        g.setColour(arrowColour);
        g.strokePath(path, juce::PathStrokeType(2.0f));
        
    }
    
    // Slider LookAndFeel customisation
    // Reconstructing Slider object rotary slider interface
    void drawRotarySlider (juce::Graphics& g, int x,int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider) override
    {
        const int numFrames = mFBSliderImage.getHeight() / mFBSliderImage.getWidth();
        
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));
        
        const float radius = juce::jmin(width * 0.5, height * 0.5);
        const float centreX = x + width * 0.5;
        const float centreY = y + height * 0.5;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        
        g.drawImage(mFBSliderImage,
                    rx,
                    ry,
                    2 * radius,
                    2 * radius,
                    0,
                    frameIndex * mFBSliderImage.getWidth(),
                    mFBSliderImage.getWidth(),
                    mFBSliderImage.getWidth());
        
    }
    
    
private:
    
    // FrostByte_Sliders_Temp Image object declaration
    juce::Image mFBSliderImage;
    
};

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.
    Notes:
    1. m prefix naming convention for declared class members, this allows me to differentiate between local variables/elements and prexisting class elements.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FBMonoPlanewaveEncode.h"
#include "FBStereoPlanewaveEncode.h"
#include "FBStereoMidSideDecode.h"
#include "FBStereoCrossedPairDecode.h"

//==============================================================================
/**
*/
class FrostByteAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FrostByteAudioProcessor();
    ~FrostByteAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    // Parameter pointer object declarations
    juce::AudioParameterFloat* mAzimuthParameter;
    juce::AudioParameterFloat* mElevationParameter;
    juce::AudioParameterFloat* mStereoWidthParameter;
    juce::AudioParameterInt* mEncodeType;
    juce::AudioParameterInt* mDecodeType;
    
    // DSP pointer object declarations
    std::unique_ptr<FBMonoPlanewaveEncode> mMonoPlanewaveEncode;
    std::unique_ptr<FBStereoPlanewaveEncode> mStereoPlanewaveEncode;
    std::unique_ptr<FBStereoMidSideDecode> mStereoMidSideDecode;
    std::unique_ptr<FBStereoCrossedPairDecode> mStereoCrossedPairDecode;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrostByteAudioProcessor)
};

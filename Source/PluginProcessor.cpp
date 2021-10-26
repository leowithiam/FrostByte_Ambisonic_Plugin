/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.
    Notes:
    1.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FrostByteAudioProcessor::FrostByteAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::ambisonic(1), true)
                     #endif
                       )
#endif
{
    // Parameter pointer object initialisations
    addParameter(mAzimuthParameter = new juce::AudioParameterFloat("Azimuth", "Azimuth", -180.0f, 180.0f, 0.0f));
    
    addParameter(mElevationParameter = new juce::AudioParameterFloat("Elevation", "Elevation", -180.0f, 180.0f, 0.0f));
    
    addParameter(mStereoWidthParameter = new juce::AudioParameterFloat("Stereo Width", "Stereo Width", 0.0f, 180.0f, 0.0f));
    
    addParameter(mEncodeType = new juce::AudioParameterInt("Encode Type", "Encode Type", 1, 2, 1));
    
    addParameter(mDecodeType = new juce::AudioParameterInt("Decode Type", "Decode Type", 1, 3, 1));
    
}

FrostByteAudioProcessor::~FrostByteAudioProcessor()
{
}

//==============================================================================
const juce::String FrostByteAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FrostByteAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FrostByteAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FrostByteAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FrostByteAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FrostByteAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FrostByteAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FrostByteAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FrostByteAudioProcessor::getProgramName (int index)
{
    return {};
}

void FrostByteAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FrostByteAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FrostByteAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FrostByteAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return false;
}
#endif

void FrostByteAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    // Inputs
    // Mono
    auto* monoInput = buffer.getReadPointer(0);
    
    
    // Stereo
    auto* stereoLeftInput = buffer.getReadPointer(0);
    auto* stereoRightInput = buffer.getReadPointer(1);
     
    
    // FOA AmbiX
    auto* ACN0Input = buffer.getReadPointer(0);
    auto* ACN1Input = buffer.getReadPointer(1);
    auto* ACN2Input = buffer.getReadPointer(2);
    auto* ACN3Input = buffer.getReadPointer(3);
    
    // Outputs
    // Stereo
    auto* leftOutput = buffer.getWritePointer(0);
    auto* rightOutput = buffer.getWritePointer(1);
    auto* midSignal = buffer.getWritePointer(2);
    
    // FOA AmbiX
    auto* ACN0Output = buffer.getWritePointer(0);
    auto* ACN1Output = buffer.getWritePointer(1);
    auto* ACN2Output = buffer.getWritePointer(2);
    auto* ACN3Output = buffer.getWritePointer(3);
    
    // DSP
    // Encoding
    mMonoPlanewaveEncode->monoEncoding(monoInput,
                                       mAzimuthParameter->get(),
                                       mElevationParameter->get(),
                                       ACN0Output,
                                       ACN1Output,
                                       ACN2Output,
                                       ACN3Output,
                                       buffer.getNumSamples());
    /*
    if (*mEncodeType == 1)
    {
        mMonoPlanewaveEncode->monoEncoding(monoInput,
                                           mAzimuthParameter->get(),
                                           mElevationParameter->get(),
                                           ACN0Output,
                                           ACN1Output,
                                           ACN2Output,
                                           ACN3Output,
                                           buffer.getNumSamples());
    }
    
    else if (*mEncodeType == 2)
    {
        mStereoPlanewaveEncode->stereoEncoding(stereoLeftInput,
                                               stereoRightInput,
                                               mStereoWidthParameter->get(),
                                               mStereoWidthParameter->get(),
                                               mElevationParameter->get(),
                                               ACN0Output,
                                               ACN1Output,
                                               ACN2Output,
                                               ACN3Output,
                                               buffer.getNumSamples());
    }
    */
    
    // Decoding
    if (*mDecodeType == 1)
    {
        mStereoMidSideDecode->stereoMidSideDecoding(ACN0Input,
                                                    ACN1Input,
                                                    ACN2Input,
                                                    ACN3Input,
                                                    midSignal,
                                                    leftOutput,
                                                    rightOutput,
                                                    buffer.getNumSamples());
    }
    
    else if (*mDecodeType == 2)
    {
        mStereoCrossedPairDecode->stereoCrossedPairDecoding(ACN0Input,
                                                            ACN1Input,
                                                            ACN2Input,
                                                            ACN3Input,
                                                            leftOutput,
                                                            rightOutput,
                                                            buffer.getNumSamples());
    }
    
    else if (*mDecodeType == 3)
    {
        
    }
    
}

//==============================================================================
bool FrostByteAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FrostByteAudioProcessor::createEditor()
{
    return new FrostByteAudioProcessorEditor (*this);
}

//==============================================================================
void FrostByteAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FrostByteAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FrostByteAudioProcessor();
}

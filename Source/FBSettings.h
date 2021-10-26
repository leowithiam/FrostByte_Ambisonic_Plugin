/*
  ==============================================================================

    FBSettings.h
    Notes:
    1.

  ==============================================================================
*/

#pragma once

// Pre-processor macro definitions
// Main block sizes
#define MAIN_BlOCK_WIDTH    600
#define MAIN_BLOCK_HEIGHT   400

// Title block sizes
#define TITLE_BlOCK_WIDTH   MAIN_BlOCK_WIDTH
#define TITLE_BLOCK_HEIGHT  50

// General block sizes
#define GENERAL_BLOCK_WIDTH     MAIN_BlOCK_WIDTH
#define GENERAL_BLOCK_HEIGHT    MAIN_BLOCK_HEIGHT - TITLE_BLOCK_HEIGHT

// Colour variables
const juce::Colour FBColour_1 = juce::Colour(juce::Colours::white);
const juce::Colour FBColour_2 = juce::Colour(juce::Colours::transparentBlack);
const juce::Colour FBColour_3 = juce::Colour(105, 105, 105);
const juce::Colour FBColour_4 = juce::Colour(juce::Colours::black).withAlpha(0.3f);
const juce::Colour FBColour_5 = juce::Colour(juce::Colours::black).withAlpha(0.4f);
const juce::Colour FBColour_6 = juce::Colour(105, 105, 105).withAlpha(0.1f);
const juce::Colour FBColour_7 = juce::Colour(125, 125, 125);
const juce::Colour FBColour_8 = juce::Colour(juce::Colours::white).withAlpha(0.4f);
const juce::Colour FBColour_9 = juce::Colour(juce::Colours::lightblue);
const juce::Colour FBColour_10 = juce::Colour(juce::Colours::lightblue.withAlpha(0.4f));
const juce::Colour FBColour_11 = juce::Colour(juce::Colours::red);
const juce::Colour FBColour_12 = juce::Colour(juce::Colours::red.withAlpha(0.4f));


// Font variables
const juce::Font FBFont_1("Helvetica Neue", 30.00f, juce::Font::bold);
const juce::Font FBFont_2("Helvetica Neue", 15.00f, juce::Font::bold);




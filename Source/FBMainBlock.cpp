/*
  ==============================================================================

    FBMainBlock.cpp
    Notes:
    1.

  ==============================================================================
*/

#include "FBMainBlock.h"

FBMainBlock::FBMainBlock(FrostByteAudioProcessor* inputProcessor) : FBBaseBlock(inputProcessor)
{
    // Formatting size of FBMainBlock object
    setSize(MAIN_BlOCK_WIDTH,
            MAIN_BLOCK_HEIGHT);
    
    // Instantiating FBTitleBlock smart pointer object
    mTitleBlock = std::make_unique<FBTitleBlock>(inputProcessor);
    mTitleBlock->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTitleBlock.get());
    
    // Instantiating FBGeneralBlock smart pointer object
    mGeneralBlock = std::make_unique<FBGeneralBlock>(inputProcessor);
    mGeneralBlock->setTopLeftPosition(0, TITLE_BLOCK_HEIGHT);
    addAndMakeVisible(mGeneralBlock.get());
}

FBMainBlock::~FBMainBlock()
{
    
}

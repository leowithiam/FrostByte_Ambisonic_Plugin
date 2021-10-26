/*
  ==============================================================================

    FBMainBlock.h
    Notes
    1.

  ==============================================================================
*/

#pragma once

#include "FBBaseBlock.h"
#include "FBTitleBlock.h"
#include "FBGeneralBlock.h"

class FBMainBlock : public FBBaseBlock
{
public:
    
    FBMainBlock(FrostByteAudioProcessor* inputProcessor);
    ~FBMainBlock();
    
private:
    
    // Block smart pointer object declarations
    std::unique_ptr<FBTitleBlock> mTitleBlock;
    std::unique_ptr<FBGeneralBlock> mGeneralBlock;
    
};

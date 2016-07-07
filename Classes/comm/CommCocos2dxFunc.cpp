#include "CommCocos2dxFunc.h"

namespace CommCocos2dxFunc
{
    void switchSceneMoveInLR(Scene* scene, bool next/*=true*/, float duration/*=0.5f*/)
    {
        if (next)
        {
            Director::getInstance()->replaceScene(TransitionMoveInR::create(duration, scene));
        }
        else
        {
            Director::getInstance()->replaceScene(TransitionMoveInL::create(duration, scene));
        }
    }

    void switchSceneSpliteRows(Node* from, Scene* scene, bool next/*=true*/, float duration/*=0.5f*/)
    {
        if (next)
        {
            Director::getInstance()->replaceScene(TransitionSplitRows::create(duration, scene));
        }
        else
        {
            Director::getInstance()->replaceScene(TransitionSplitRows::create(duration, scene));
        }
    }

    void switchSceneMoveInTB(Scene* scene, bool next/*=true*/, float duration/*=0.3f*/)
    {
        if (next)
        {
            Director::getInstance()->replaceScene(TransitionMoveInB::create(duration, scene));
        }
        else
        {
            Director::getInstance()->replaceScene(TransitionMoveInT::create(duration, scene));
        }
    }

    void switchSceneSpliteCols(Scene* scene, bool next/*=true*/, float duration/*=0.3f*/)
    {
        if (next)
        {
            Director::getInstance()->replaceScene(TransitionSplitCols::create(duration, scene));
        }
        else
        {
            Director::getInstance()->replaceScene(TransitionSplitCols::create(duration, scene));
        }
    }

}
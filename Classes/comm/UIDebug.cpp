#include "UIDebug.h"

namespace UIDebug
{

void drawNodeRect(Node* node, const Color4F& color/*=Color4F(1.0f, 0.0f, 0.0f, 1.0f)*/, int tag_id/*=99999*/)
{
    DrawNode* drawNode = NULL;
    if (tag_id > 0)
    {
        drawNode = dynamic_cast<DrawNode*>(node->getChildByTag(tag_id));
    }
    if (NULL==drawNode)
    {
        drawNode = DrawNode::create();
        node->addChild(drawNode);
        if (tag_id>0)
        {
            drawNode->setTag(tag_id);
        }
    }
    drawNode->setLocalZOrder(100000);
    Size sizeContent(node->getContentSize());
    drawNode->setContentSize(sizeContent);

    drawNode->drawSegment(Point(0, 0), Point(sizeContent.width, 0), 1, color);
    drawNode->drawSegment(Point(0, 0), Point(0, sizeContent.height), 1, color);
    drawNode->drawSegment(Point(0, sizeContent.height), Point(sizeContent.width, sizeContent.height), 1, color);
    drawNode->drawSegment(Point(sizeContent.width, 0), Point(sizeContent.width, sizeContent.height), 1, color);
}

void drawNodeRectAndAnchorPoint(Node* node, const Color4F& color/*=Color4F(0.0f, 1.0f, 0.0f, 1.0f)*/, int tag_id/*=99999*/)
{
    DrawNode* drawNode = NULL;
    if (tag_id > 0)
    {
        drawNode = dynamic_cast<DrawNode*>(node->getChildByTag(tag_id));
    }
    if (NULL==drawNode)
    {
        drawNode = DrawNode::create();
        node->addChild(drawNode);
        if (tag_id>0)
        {
            drawNode->setTag(tag_id);
        }
    }
    drawNode->setLocalZOrder(100000);
    Size sizeContent(node->getContentSize());
    drawNode->setContentSize(sizeContent);

    drawNode->drawSegment(node->getAnchorPointInPoints(), node->getAnchorPointInPoints(), 4.0f, color);
    drawNode->drawSegment(Point(0, 0), Point(sizeContent.width, 0), 1, color);
    drawNode->drawSegment(Point(0, 0), Point(0, sizeContent.height), 1, color);
    drawNode->drawSegment(Point(0, sizeContent.height), Point(sizeContent.width, sizeContent.height), 1, color);
    drawNode->drawSegment(Point(sizeContent.width, 0), Point(sizeContent.width, sizeContent.height), 1, color);
}
}
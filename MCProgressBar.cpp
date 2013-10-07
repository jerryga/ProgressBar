//
//  MCProgressBar.cpp
//  MagicCardGame
//
//  Created by Static Ga on 13-8-21.
//
//

#include "scene/CardScene/Helper/MCProgressBar.h"
#include <sstream>

#define pExpBarBG "HeCheng/RedExpProgressBg.png"
#define pExpRedBarBG "HeCheng/RedExpProgressBar.png"

#define kRedBarTag 7777
#define kLabelTag 7778

using namespace cocos2d;

MCProgressBar *MCProgressBar::createWithPer(float percent) {
    MCProgressBar *bar = new MCProgressBar();
    if (bar && bar->initWithPer(percent)) {
        bar->autorelease();
        return bar;
    }
    
    CC_SAFE_DELETE(bar);
    return NULL;
}

bool MCProgressBar::initWithPer(float percent) {
    if (!CCSprite::initWithFile(pExpBarBG)) {
        return false;
    }
    makeProgressBar(percent);
    
    CCLabelTTF *currentExpLabel = CCLabelTTF::create(" ", "FZCuYuan-M03S.ttf", 22);
    CCNode *pNode = this->getChildByTag(kRedBarTag);
    pNode->addChild(currentExpLabel);
    currentExpLabel->setPosition(ccp(pNode->getContentSize().width/2, pNode->getContentSize().height/2));
    currentExpLabel->setTag(kLabelTag);
    
    return true;
}

void MCProgressBar::makeProgressBar(float percent) {
    CCSize size = this->getContentSize();
    
    CCSprite *redBar = CCSprite::create(pExpRedBarBG);
    
    //第一个参数是时间，第二个参数是表示只旋转80%
    CCProgressTimer* pt = CCProgressTimer::create(redBar);
    pt->setType(kCCProgressTimerTypeBar);
    pt->setMidpoint(CCPointMake(0, 0));
    pt->setBarChangeRate(CCPointMake(1, 0));
    pt->setTag(kRedBarTag);
    addChild(pt);
    pt->setPosition(ccp(size.width/2, redBar->getContentSize().height/2));
    
    upDatePer(percent);
    
    
}

void MCProgressBar::setBarValue(int divisorValue, int dividendValue) {
    _divisorValue = divisorValue;
    _dividendValue = dividendValue;
    CCNode *pNode = this->getChildByTag(kRedBarTag);
    CCLabelTTF *label = dynamic_cast<CCLabelTTF *>(pNode->getChildByTag(kLabelTag));
    std::string str;
    
    std::stringstream ss_stream;
    ss_stream<<_divisorValue<<" / "<<_dividendValue;
    str = ss_stream.str();
    label->setString(str.c_str());
}

void MCProgressBar::upDatePer(float percent,bool showAniamte) {
    int times = percent/100;
    dis  = (int)percent % 100;
    CCProgressTimer *redBarProgress = dynamic_cast<CCProgressTimer *>(this->getChildByTag(kRedBarTag));
    
    CCLog("times %d dis %f",times,dis);
    if (showAniamte) {
        CCArray *progressArr = new CCArray();
        for (int i = 0; i < times; ++i) {
            CCProgressFromTo *progressFromTo = CCProgressFromTo::create(2, 0.0, 100.0);
            progressArr->addObject(progressFromTo);
        }
        
        CCProgressFromTo *progressFromTo = CCProgressFromTo::create(2, 0.0, dis);
        progressArr->addObject(progressFromTo);
        redBarProgress->runAction(CCSequence::create(progressArr));
        progressArr->release();
    }else {
        CCProgressTo* p1 = CCProgressTo::create(0, dis);
        redBarProgress->runAction(p1);
    }
}


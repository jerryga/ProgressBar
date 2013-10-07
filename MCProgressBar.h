//
//  MCProgressBar.h
//  MagicCardGame
//
//  Created by Static Ga on 13-8-21.
//
//

#ifndef __MagicCardGame__MCProgressBar__
#define __MagicCardGame__MCProgressBar__

#include <iostream>
#include "cocos2d.h"

class MCProgressBar :public cocos2d::CCSprite{
public:
    MCProgressBar() {
        dis = 0;
        _divisorValue = 0;
        _dividendValue = 0;
    }
    static MCProgressBar *createWithPer(float percent);
    bool initWithPer(float percent);
    void upDatePer(float percent,bool showAniamte = true);
    void makeProgressBar(float percent);
    void setBarValue(int divisorValue, int dividendValue);
private:
    float dis;
    int _divisorValue;
    int _dividendValue;
};

#endif /* defined(__MagicCardGame__MCProgressBar__) */


#include "KCCMenuItemMoreFrame.h"


bool KCCMenuItemMoreFrame::initWithNormalSprite(CCNode* normalSprite, CCNode* offSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItem::initWithTarget(target, selector); 
	setNormalImage(normalSprite);
	setSelectedImage(offSprite);
	setDisabledImage(disabledSprite);

	if(m_pNormalImage)
	{
		this->setContentSize(m_pNormalImage->getContentSize());
	}
	return true;
}


KCCMenuItemMoreFrame * KCCMenuItemMoreFrame::create(CCNode *normalSprite, CCNode *offSprite, CCNode *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
	KCCMenuItemMoreFrame *pRet = new KCCMenuItemMoreFrame();
	pRet->initWithNormalSprite(normalSprite, offSprite, disabledSprite, target, selector); 
	pRet->autorelease();
	return pRet;
}


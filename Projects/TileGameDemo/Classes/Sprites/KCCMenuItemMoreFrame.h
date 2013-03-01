#ifndef _KCCMENU_ITEM_
#define  _KCCMENU_ITEM_
#include "cocos2d.h"

using namespace cocos2d;



class KCCMenuItemMoreFrame : public CCMenuItemSprite
{

public:
	enum MenuItemStatus
	{
		Normal,
		Off,
		Disabled
	};
public:
	KCCMenuItemMoreFrame(){CCMenuItemSprite::CCMenuItemSprite();}
	~ KCCMenuItemMoreFrame(){}

public:
	void setTag(int tag)
	{
		this->mTag = tag;
	}

	int getTag()
	{
		return this->mTag;
	}

	MenuItemStatus getStatus()
	{
		return (MenuItemStatus)mStatus;
	}

	void setStatus(MenuItemStatus status)
	{
		this->mStatus = status;
		switch (status)
		{
		case KCCMenuItemMoreFrame::Normal:
			{
				this->m_pNormalImage->setVisible(true);
				this->m_pSelectedImage->setVisible(false);
				this->m_pDisabledImage->setVisible(false);
			}
			break;
		case KCCMenuItemMoreFrame::Off:
			{
				this->m_pNormalImage->setVisible(false);
				this->m_pSelectedImage->setVisible(true);
				this->m_pDisabledImage->setVisible(false);
			}
			break;
		case KCCMenuItemMoreFrame::Disabled:
			{
				this->m_pNormalImage->setVisible(false);
				this->m_pSelectedImage->setVisible(false);
				this->m_pDisabledImage->setVisible(true);
			}
			break;
		default:
			break;
		}
	}

	static KCCMenuItemMoreFrame * create(CCNode* normalSprite, CCNode* offSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

	bool initWithNormalSprite(CCNode* normalSprite, CCNode* offSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
private:
	int mTag;
	int mStatus;
};








#endif
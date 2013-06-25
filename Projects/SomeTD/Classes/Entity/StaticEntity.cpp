//
//  StaticEntity.cpp
//  Some
//
//  Created by kelyad on 02-17-2013.
//

#include "StaticEntity.h"
#include "../Managers/EnemyManager.h"
#include "../Managers/AllyManager.h"
#include "../Helper/CommonHelpers.h"
#include <math.h>
using namespace cocos2d;


namespace SomeTD
{

	bool StaticEntity::myInit(CCSpriteFrame* defaultFrame)
	{
		kkAssertMsg(defaultFrame != nullptr, "[StaticEntity:{myInit}]: defaultFrame is null!");
		mDefaultFrame = defaultFrame;
	}


	CCRect StaticEntity::getCollisionRect()
	{
		//auto colorRect = this->getColorRect();
		CCPoint pos = this->getPosition();
		auto size = this->getContentSize();

		/* calculate detail
		*	left_bottom_X = pos.x - size.width / 2
		*	left_bottom_Y = pos.y - size.height / 2
		*	left_bottom_ColorRect_X = colorRect.origin.x
		*	left_bottom_ColorRect_Y = size.height - colorRect.size.height - colorRect.origin.y
		*  final_X =  left_bottom_X + left_bottom_ColorRect_X
		*	final_Y =  left_bottom_Y + left_bottom_ColorRect_Y*/

		float x = pos.x - size.width / 2 + m_colorRect.getMinX();
		float y = pos.y + size.height / 2 - m_colorRect.getMaxY();

		//CCRect old(pos.x, pos.y, size.width, size.height);

		//CCLog("colorRect: {{%f, %f}, {%f, %f}}",colorRect.origin.x, colorRect.origin.y, colorRect.size.width, colorRect.size.height);
		//CCLog("collisionRect Old: {{%f, %f}, {%f, %f}}",old.origin.x, old.origin.y, old.size.width, old.size.height);
		//CCLog("collisionRect New: {{%f, %f}, {%f, %f}}",x, y, colorRect.size.width, colorRect.size.height);
		return CCRect(x, y, m_colorRect.size.width, m_colorRect.size.height);
	}

	
}

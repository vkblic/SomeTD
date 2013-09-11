//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "AllyManager.h"
#include "EntityManager.h"
#include "EnemyManager.h"
#include "../Helper/CommonHelpers.h"
#include "../Helper/SpriteHelpers.h"
#include "../Common/Common.h"
#include "../Utility/XmlReader.h"
#include "../MessagePump/MsgRoute.h"
using namespace cocos2d;


AllyManager::AllyManager()
{
	this->mAllyLayer = NULL;
	//this->mHpBatchNode = NULL;
	//this->mBatch = NULL;
	this->mIDSeed = 10001;
}
AllyManager::~AllyManager()
{
	for(auto it = this->mAllies.begin(); it != this->mAllies.end(); ++it)
	{
		it->second->release();
		//this->mBatch->removeChild(it->second, true);
		it->second->getParent()->removeChild(it->second, true);
		CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", it->second->retainCount());
	}
	this->mAllies.clear();

	for(auto it = this->mBatchNodes.begin(); it != this->mBatchNodes.end(); ++it)
	{
		it->second->release();
		it->second->getParent()->removeChild(it->second, true);
	}

	this->mAllyLayer->release();
	//this->mBatch->release();
	//this->mHpBatchNode->release();
}

AllyManager* AllyManager::mInstance = nullptr;
AllyManager* AllyManager::sharedAllyManager()
{
	if (AllyManager::mInstance == nullptr)
		AllyManager::mInstance = new AllyManager();
	return AllyManager::mInstance;
}

void AllyManager::setObjectLayer(CCNode* layer)
{
	this->mAllyLayer = layer;
}

void AllyManager::readAlliesInfo(const char* fileName)
{
	XmlReader::readActiveObjectInfoFromFile(this->mAllyInfo, fileName);
}






#pragma region Range checker

ENTITY_ID AllyManager::getObjInRange(const CCPoint& pos, int rangeRadius)
{

	for(auto it = this->mAllies.begin();it != this->mAllies.end(); ++it)
	{
		CCRect collisionRect = it->second->getCollisionRect();
		if (isRectAndCircleCollided(pos, rangeRadius, collisionRect))
		{
			CCPoint targetPos = it->second->getPosition();
			CCSize targetSize = it->second->getContentSize();
			//CCRect rect = it->second->getCollisionRect();
			//CCLog("New target in range.");
			//CCLog("target: {{%f, %f}, {%f, %f}}", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
			//CCLog("collisionRect Old: {{%f, %f}, {%f, %f}}",rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
			//CCLog("tower: pos(%f, %f)", pos.x, pos.y );
			return it->first;
		}
	}
	return -1;
}

bool AllyManager::isOjbectInRange(const CCPoint& pos, int rangeRadius,  ENTITY_ID id)
{
	auto it = this->mAllies.find(id);

	// enemy already dead
	if (it == this->mAllies.end())
		return false;
	CCRect collisionRect = it->second->getCollisionRect();
	if (isRectAndCircleCollided(pos, rangeRadius, collisionRect))
		return true;
	CCPoint targetPos = it->second->getPosition();
	CCSize targetSize = it->second->getContentSize();
	//CCLog("\ntarget out of range.");
	//CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
	//CCLog("tower: pos(%f, %f)", pos.x, pos.y );
	return false;
}

#pragma endregion


#pragma region enemy node

AllyUnit* AllyManager::addAlly(const char* enemyName, const CCPoint& pos, const CCPoint& towerPos)
{

	auto allyInfo = this->mAllyInfo.find(enemyName);
	ActiveObjModel* temp = &(*allyInfo).second;

	// dealing with batch node
	auto batch = this->getBatchNode(temp->textureSet);
	auto hpBatch = this->getBatchNode("hp.png");

	auto ally = AllyUnit::create(temp, hpBatch);
	//CCLog("EnemyManager::addEnemy: retainCount: %d", enemy->retainCount());
	auto entityID = EntityManager::sharedEntityManager()->generateID();
	// for debug		entityID += 10000;
	this->mAllies.insert(std::pair< ENTITY_ID, AllyUnit*>(entityID, ally));
	batch->addChild(ally);
	ally->setEntityID(entityID);
	ally->setPosition(pos);
	ally->setTowerPos(towerPos);
	EntityManager::sharedEntityManager()->addEntity(ally);
	ally->setFSM_Machine(FSM_Ally);
	return ally;
}




CCSpriteBatchNode* AllyManager::getBatchNode( const char* textureSetName )
{

	auto it = this->mBatchNodes.find(textureSetName);
	CCSpriteBatchNode* batch;
	if(it == this->mBatchNodes.end())
	{
		batch = CCSpriteBatchNode::create(textureSetName);
		this->mBatchNodes.insert(
			std::map<std::string, CCSpriteBatchNode*>::value_type(
			textureSetName, 
			batch
			)
			);
		this->mAllyLayer->addChild(batch);
	}
	else
	{
		batch = (*it).second;
	}
	return batch;
}



void AllyManager::removeAllyByID( ENTITY_ID id)
{
	auto it = this->mAllies.find(id);
	if(it == this->mAllies.end())
		kkAssertMsg(false, "[AllyManager::removeAllyByID], can't find ally in mAllies map!");

	this->mRemovedAllies.insert(std::map< ENTITY_ID, AllyUnit*>::value_type(id, it->second));

	this->mAllies.erase(it);

	EntityManager::sharedEntityManager()->removeEntity(id);
}

void AllyManager::eraseAllyByID( ENTITY_ID id)
{
	auto it = this->mRemovedAllies.find(id);
	if(it == this->mRemovedAllies.end())
		kkAssertMsg(false, "[AllyManager::eraseAllyByID], can't find ally in mUnusedAllies map!");

	this->mUnusedAllies.push_back(it->second);
	this->mRemovedAllies.erase(it);
}



void AllyManager::clearUnusedAllies()
{
	for(auto it = this->mUnusedAllies.begin(); it != this->mUnusedAllies.end(); ++it)
	{
		auto node = (*it);
		//node->release();
		//CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", node->retainCount());
		auto batch = (*this->mBatchNodes.find(node->getEntityInfo()->textureSet)).second;
		batch->removeChild(node, true);
	}
	this->mUnusedAllies.clear();
}

AllyUnit* AllyManager::getAvailableObject( ENTITY_ID id)
{
	auto it = this->mAllies.find(id);
	if (it == this->mAllies.end())
		return NULL;
	return it->second;
}

#pragma endregion


//fsm

void AllyManager::changeState( AllyUnit* entity, ActiveObj_States state )
{
	MsgRoute* msgRount = MsgRoute::sharedMsgRount();
	msgRount->sendMsg(MSG_RESERVED_Exit, entity->getEntityID(), entity->getEntityID());
	entity->setState(state);
	msgRount->sendMsg(MSG_RESERVED_Enter, entity->getEntityID(), entity->getEntityID());
}

void AllyManager::sendMsg( MsgName name, ENTITY_ID senderID, ENTITY_ID receiverID )
{
	MsgRoute::sharedMsgRount()->sendMsg(name, senderID, receiverID);
}

void AllyManager::sendCollisionRecMsg(ENTITY_ID senderID, ENTITY_ID receiverID, CCRect rect)
{
	CollisionRectMsg msg;
	msg.name = MSG_ReceivePosition;
	msg.receiver_id = receiverID;
	msg.sender_id = senderID;
	msg.rect = rect;
	msg.delivery_time = MsgRoute::sharedMsgRount()->getTick();
	MsgRoute::sharedMsgRount()->sendMsg(msg);
}

void AllyManager::sendDamageMsg(ENTITY_ID senderID, ENTITY_ID receiverID, int damage)
{
	MsgDamage msg;
	msg.name = MSG_Damage;
	msg.receiver_id = receiverID;
	msg.sender_id = senderID;
	msg.damage = damage;
	msg.delivery_time = MsgRoute::sharedMsgRount()->getTick();
	MsgRoute::sharedMsgRount()->sendMsg(msg);
}

void AllyManager::frameTrigger(float dt)
{
	for(auto iter = mAllies.begin(); iter != mAllies.end(); ++iter)
	{
		iter->second->frameListener(dt);
	}

	this->clearUnusedAllies();
}



void AllyManager::fsmTranslater(const MsgBase& msg, AllyUnit* ally)
{
	//MsgRoute* msgRoute = MsgRoute::sharedMsgRount();
	//AllyUnit* ally = this->getAvailableObject(msg.receiver_id);
	//if(ally == nullptr && (msg.receiver_id != msg.sender_id))
	//	msgRoute->sendDelayedMsg(MSG_TargetNotAvailable, 1, 0, msg.sender_id);
	switch (msg.name)
	{
	case MSG_RequestPosition:
		{
			this->sendCollisionRecMsg(msg.receiver_id, msg.sender_id, ally->getCollisionRect());
		}
		return;
	case MSG_AttackerNoAvailable:
		{
			ally->removeAttacker(msg.sender_id);
		}
		return;
		default:
			break;
	}


	switch (ally->getState())
	{
	case STATE_Idle:
		{
			if(msg.name == MSG_RESERVED_Enter)
			{
				ally->onEnterIdle();
			}
			else if(msg.name == MSG_RESERVED_Exit)
			{

			}
			else if(msg.name == MSG_FoundTarget)
			{
				this->changeState(ally, STATE_MovingToTarget);
			}
			else if( msg.name == MSG_Damage)
			{
				auto damageMsg = static_cast<const MsgDamage&>(msg);
				// calc hp
				ally->underAttack(damageMsg.damage, damageMsg.sender_id, damageMsg.senderCollisionRect);
				// deal with target
				if(ally->targetCheck(msg.sender_id))
					this->changeState(ally, STATE_MovingToTarget);
			}
			else
			{
				kkAssertMsgf(false, "[AllyManager::fsmTranslater], [STATE_Idle] can't handle message");
			}
		}
		break;
	case STATE_MovingToTarget:
		{
			if(msg.name == MSG_RESERVED_Enter)
			{
				ally->enterMoveToTarget();
			}
			else if(msg.name == MSG_ReceivePosition)
			{
				auto msgPos = static_cast<const CollisionRectMsg&>(msg);
				ally->setTargetCollisionRect(msgPos.rect);
			}
			else if(msg.name == MSG_InAttackPosition)
			{
				this->changeState(ally, STATE_Attacking);
			}

			else if(msg.name == MSG_TargetNotAvailable)
			{
				this->changeState(ally, STATE_Moving);
			}

			else if(msg.name == MSG_RESERVED_Exit)
			{
				ally->exitMoveToTarget();
			}
			else
			{
				kkAssertMsgf(false, "[AllyManager::fsmTranslater], [STATE_MovingToTarget] can't handle message");
			}
		}
		break;
	case STATE_Attacking:
		{
			if(msg.name == MSG_RESERVED_Enter)
			{
				ally->enterAttacking();
			}
			else if(msg.name == MSG_TargetNotAvailable)
			{
				// back to flag pos when k.o. a enemy.
				ally->removeTarget();
				this->changeState(ally, STATE_Moving);
			}

			else if(msg.name == MSG_ReceivePosition)
			{
				kkAssertMsg(ally->targetIs(msg.sender_id), "[AllyManager::fsmTranslater], STATE_Attacking-MSG_ReceivePosition, targetIs check faild");
				this->changeState(ally, STATE_MovingToTarget);
			}
			else if( msg.name == MSG_Damage)
			{
				auto damageMsg = static_cast<const MsgDamage&>(msg);
				// calc hp
				ally->underAttack(damageMsg.damage, damageMsg.sender_id, damageMsg.senderCollisionRect);

			}
			else if(msg.name == MSG_RESERVED_Exit)
			{
				ally->exitAttacing();
			}
			else
			{
				kkAssertMsgf(false, "[AllyManager::fsmTranslater], [STATE_Attacking] can't handle message");
			}
		}
		break;
	case STATE_Moving:
		{
			if(msg.name == MSG_RESERVED_Enter)
			{
				//ally->moveToMassPos();
				ally->moveBackToMassPos();
			}
			else if(msg.name == MSG_InPostion)
			{
				this->changeState(ally, STATE_Idle);
			}
			else if(msg.name == MSG_RESERVED_Exit)
			{
				// do nothing temporary
				ally->onExitMoving();
			}
			else
			{
				kkAssertMsgf(false, "[AllyManager::fsmTranslater], [STATE_Moving] can't handle message");
			}
		}
	default:
		break;
	}
}

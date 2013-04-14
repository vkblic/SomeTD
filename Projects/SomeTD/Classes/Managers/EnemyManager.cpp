//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "EnemyManager.h"
#include "EntityManager.h"
#include "../Helper/CommonHelpers.h"
#include "../Helper/SpriteHelpers.h"
#include "../Utility/XmlReader.h"
#include "../Common/Common.h"
#include "../MessagePump/MsgRoute.h"
using namespace cocos2d;

EnemyManager::EnemyManager()
{
	this->mEnemyLayer = NULL;
	//this->mHpBatchNode = NULL;
	//this->mBatch = NULL;
}
EnemyManager::~EnemyManager()
{
	for(auto it = this->mEnemies.begin(); it != this->mEnemies.end(); ++it)
	{
		it->second->release();
		//this->mBatch->removeChild(it->second, true);
		it->second->getParent()->removeChild(it->second, true);
		CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", it->second->retainCount());
	}
	this->mEnemies.clear();

	for(auto it = this->mBatchNodes.begin(); it != this->mBatchNodes.end(); ++it)
	{
		it->second->release();
		it->second->getParent()->removeChild(it->second, true);
	}

	this->mEnemyLayer->release();
	//this->mBatch->release();
	//this->mHpBatchNode->release();
}

EnemyManager* EnemyManager::mInstance = NULL;
EnemyManager* EnemyManager::sharedEnemyManager()
{
	if (EnemyManager::mInstance == NULL)
		EnemyManager::mInstance = new EnemyManager();
	return EnemyManager::mInstance;
}

void EnemyManager::setEnemyLayer(CCNode* layer)
{
	this->mEnemyLayer = layer;
}

void EnemyManager::readEnemyInfo(const char* fileName)
{
	XmlReader::readActiveObjectInfoFromFile(this->mEnemyInfo, fileName);
}






#pragma region Range checker

entity_id EnemyManager::getEnemyInRange(CCPoint pos, int rangeRadius)
{

	for(auto it = this->mEnemies.begin();it != this->mEnemies.end(); ++it)
	{
		CCRect rect = it->second->getCollisionRect();
		if (isRectAndCircleCollided(pos, rangeRadius, rect))
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
	return non_entity;
}

bool EnemyManager::isEnemyInRange(CCPoint pos, int rangeRadius,  entity_id enemyID)
{
	if (enemyID == -1)
		return false;
	auto it = this->mEnemies.find(enemyID);

	// enemy already dead
	if (it == this->mEnemies.end())
		return false;
	CCRect collisionRect = it->second->getCollisionRect();
	if (isRectAndCircleCollided(pos, rangeRadius, collisionRect))
		return true;
	//CCPoint targetPos = it->second->getPosition();
	//CCSize targetSize = it->second->getContentSize();
	//CCLog("\ntarget out of range.");
	//CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
	//CCLog("tower: pos(%f, %f)", pos.x, pos.y );
	return false;
}
bool EnemyManager::isEnemyInRangeAndInTowerRange(CCPoint pos, int rangeRadius, CCPoint towerPos, int towerRangeRadius, entity_id enemyID)
{

	if (enemyID == -1)
		return false;
	auto it = this->mEnemies.find(enemyID);

	// enemy already dead
	if (it == this->mEnemies.end())
		return false;
	CCRect collisionRect = it->second->getCollisionRect();
	auto isInRange = isRectAndCircleCollided(pos, rangeRadius, collisionRect);
	auto isInTowerRange = isRectAndCircleCollided(towerPos, towerRangeRadius, collisionRect);
	
	if (isInRange && isInTowerRange)
		return true;
	return false;

}




#pragma endregion


#pragma region enemy node

EnemyUnit* EnemyManager::addEnemy(const char* enemyName, CCPoint entry)
{

	auto enemyInfo = this->mEnemyInfo.find(enemyName);
	ActiveObjModel* temp = &(*enemyInfo).second;

	auto it = this->mBatchNodes.find(temp->textureSet);
	CCSpriteBatchNode* batch;
	if(it == this->mBatchNodes.end())
	{
		batch = CCSpriteBatchNode::create(temp->textureSet);
		this->mBatchNodes.insert(
			std::map<std::string, CCSpriteBatchNode*>::value_type(
			temp->textureSet, 
			batch
			)
			);
		this->mEnemyLayer->addChild(batch);
	}
	else
	{
		batch = (*it).second;
	}

	it = this->mBatchNodes.find("hp.png");
	CCSpriteBatchNode* hpBatch;
	if(it == this->mBatchNodes.end())
	{
		hpBatch = CCSpriteBatchNode::create("hp.png");
		this->mBatchNodes.insert(std::map<std::string, CCSpriteBatchNode*>::value_type(
			"hp.png", 
			hpBatch)
			);
		this->mEnemyLayer->addChild(hpBatch);
	}
	else
	{
		hpBatch = (*it).second;
	}


	auto enemy = EnemyUnit::create(temp, hpBatch);

	auto entityID = EntityManager::sharedEntityManager()->generateID();
	//CCLog("EnemyManager::addEnemy: retainCount: %d", enemy->retainCount());
	this->mEnemies.insert(std::pair< entity_id, EnemyUnit*>(entityID, enemy));
	batch->addChild(enemy);
	enemy->setEntityID(entityID);
	enemy->setFSM_Machine(FSM_Enemy);
	EntityManager::sharedEntityManager()->addEntity(enemy);
	return enemy;
}


void EnemyManager::addEnemyAndRush(const char* name, CCPoint entry, const std::vector<WayPointEx>* wayPoints)
{
	EnemyUnit* enemy =  this->addEnemy(name, entry);
	enemy->setPosition(entry);
	enemy->run(wayPoints);
}


void EnemyManager::removeEnemy( entity_id enemyID)
{
	auto it = this->mEnemies.find(enemyID);
	if(it == this->mEnemies.end())
		kkAssertMsg(false, "must find id in map! there must be some error some where!");

	this->mRemovedEnemies.insert(std::map< entity_id, EnemyUnit*>::value_type(enemyID, it->second));

	this->mEnemies.erase(it);
	EntityManager::sharedEntityManager()->removeEntity(enemyID);
}

void EnemyManager::eraseEnemy( entity_id enemyID)
{
	auto it = this->mRemovedEnemies.find(enemyID);
	if(it == this->mRemovedEnemies.end())
		kkAssertMsg(false, "must find id in map! there must be some error some where!");

	this->mUnusedEnemy.push_back(it->second);
	this->mRemovedEnemies.erase(it);
}



void EnemyManager::clearUnusedEnemise()
{
	for(auto it = this->mUnusedEnemy.begin(); it != this->mUnusedEnemy.end(); ++it)
	{
		auto node = (*it);
		//node->release();
		//CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", node->retainCount());
		auto batch = (*this->mBatchNodes.find(node->getEntityInfo()->textureSet)).second;
		batch->removeChild(node, true);
	}
	this->mUnusedEnemy.clear();
}

EnemyUnit* EnemyManager::getAvailableEnemy( entity_id enemyID)
{
	auto it = this->mEnemies.find(enemyID);
	if (it == this->mEnemies.end())
		return NULL;
	return it->second;
}

#pragma endregion



void EnemyManager::frameTrigger(float dt)
{
	for(auto iter = mEnemies.begin(); iter != mEnemies.end(); ++iter)
	{
		iter->second->frameListener(dt);
	}

	this->clearUnusedEnemise();
}



//fsm

void EnemyManager::changeState( EnemyUnit* entity, ActiveObj_States state )
{
	MsgRoute* msgRount = MsgRoute::sharedMsgRount();
	msgRount->sendMsg(MSG_RESERVED_Exit, entity->getEntityID(), entity->getEntityID());
	entity->setState(state);
	msgRount->sendMsg(MSG_RESERVED_Enter, entity->getEntityID(), entity->getEntityID());
}

void EnemyManager::sendMsg( MsgName name, entity_id senderID, entity_id receiverID )
{
	MsgRoute::sharedMsgRount()->sendMsg(name, senderID, receiverID);
}

void EnemyManager::sendDelayedMsg(MsgName name, int delay, entity_id senderID, entity_id receiverID )
{
	MsgRoute::sharedMsgRount()->sendDelayedMsg(name, delay, senderID, receiverID);
}

void EnemyManager::sendCollisionRecMsg(entity_id senderID, entity_id receiverID, CCRect rect)
{
	CollisionRectMsg msg;
	msg.name = MSG_ReceivePosition;
	msg.receiver_id = receiverID;
	msg.sender_id = senderID;
	msg.rect = rect;
	msg.delivery_time = MsgRoute::sharedMsgRount()->getTick();
	MsgRoute::sharedMsgRount()->sendMsg(msg);
}

void EnemyManager::sendDamageMsg(entity_id senderID, entity_id receiverID, int damage)
{
	MsgDamage msg;
	msg.name = MSG_Damage;
	msg.receiver_id = receiverID;
	msg.sender_id = senderID;
	msg.damage = damage;
	msg.delivery_time = MsgRoute::sharedMsgRount()->getTick();
	MsgRoute::sharedMsgRount()->sendMsg(msg);
}


void EnemyManager::fsmTranslater(const MsgObject& msg, EnemyUnit* enemy)
{
	//MsgRoute* msgRoute = MsgRoute::sharedMsgRount();
	//EnemyUnit* enemy = this->getAvailableEnemy(msg.receiver_id);
	//if(enemy == nullptr && (msg.receiver_id != msg.sender_id))
	//	msgRoute->sendDelayedMsg(MSG_TargetNotAvailable, 1, 0, msg.sender_id);

	// globle msg
	switch (msg.name)
	{
	case MSG_RequestPosition:
		{
			this->sendCollisionRecMsg(msg.receiver_id, msg.sender_id, enemy->getCollisionRect());
		}
		return;
	default:
		break;
	}


	switch (enemy->getState())
	{
	case STATE_Moving:
		{
			if ( msg.name == MSG_RESERVED_Enter )
			{
				enemy->enterMoving();
			}
			else if( msg.name == MSG_StopMoving)
			{
				// for now collision rect is not need.
				enemy->addAttacker(msg.sender_id, CCRect());
				this->changeState(enemy, STATE_Stoped);
				//CCLog("targeID:%d", enemy->getTarget());
			}
			else if( msg.name == MSG_ArriveEndPoint)
			{
				enemy->onArriveEndPoint();
			}
			else if ( msg.name == MSG_AttackerNoAvailable)
			{
				enemy->removeAttacker(msg.sender_id);
			}

			// cause of no remote attack add, temporary, in STATE_Moving must not deal with MSG_Damage
			//else if( msg.name == MSG_Damage)
			//{
			//	auto damageMsg = static_cast<const MsgDamage&>(msg);
			//	// calc hp
			//	enemy->underAttack(damageMsg.damage, damageMsg.sender_id, damageMsg.senderCollisionRect);
			//
			//}


			else if(msg.name == MSG_RESERVED_Exit)
			{
				enemy->exitMoving();
			}
			else
			{
				kkAssertMsgf(false, "[EnemyManager::fsmTranslater], [STATE_Moving] can't handle message: %s", EnumStr(msg.name));
			}
		}
		break;
	case STATE_Stoped:
		{
			if(msg.name == MSG_RESERVED_Enter)
			{

			}
			else if( msg.name == MSG_StopMoving)
			{
				// for now collision rect is not need.
				enemy->addAttacker(msg.sender_id, CCRect());
				//this->changeState(enemy, STATE_Stoped);
				//CCLog("targeID:%d", enemy->getTarget());
			}
			else if ( msg.name == MSG_InAttackPosition )
			{
				//kkAssertMsg(msg.sender_id == enemy->getTarget(), "[EnemyManager::fsmTranslater] [STATE_Stopped][MSG_InAttackPosition]: target not equal!");
				//CCLog("warning!: [EnemyManager::fsmTranslater] [STATE_Stopped][MSG_InAttackPosition]: target not equal!");
				enemy->setTarget(msg.sender_id);
				this->sendMsg(MSG_RequestPosition, enemy->getEntityID(), msg.sender_id);
				this->changeState(enemy, STATE_Attacking);
			}
			else if(msg.name == MSG_ReceivePosition)
			{
				auto msgPos = static_cast<const CollisionRectMsg&>(msg);
				enemy->setTargetCollisionRect(msgPos.rect);
			}
			else if ( msg.name == MSG_AttackerNoAvailable)
			{
				// check if attacker is target.
				if(enemy->isTargetNoAvailable(msg.sender_id))
				{
					enemy->removeAttacker(msg.sender_id);
					enemy->removeTarget();
					this->changeState(enemy, STATE_Moving);
				}
			}
			else if(msg.name == MSG_RESERVED_Exit)
			{

			}
			else
			{
				kkAssertMsgf(false, "[EnemyManager::fsmTranslater], [STATE_Stoped] can't handle message: %s", EnumStr(msg.name));
			}
		}
		break;
	case STATE_Attacking:
		{
			if(msg.name == MSG_RESERVED_Enter)
			{
				enemy->enterAttacking();
			}
			else if(msg.name == MSG_TargetNotAvailable)
			{
				this->changeState(enemy, STATE_Moving);
			}
			else if ( msg.name == MSG_AttackerNoAvailable)
			{
				enemy->removeAttacker(msg.sender_id);
			}
			else if( msg.name == MSG_Damage)
			{
				auto damageMsg = static_cast<const MsgDamage&>(msg);
				// calc hp
				enemy->underAttack(damageMsg.damage, damageMsg.sender_id, damageMsg.senderCollisionRect);

			}
			else if(msg.name == MSG_RESERVED_Exit )
			{
				enemy->exitAttacing();
			}
			else if( msg.name == MSG_StopMoving)
			{
				// for now collision rect is not need.
				enemy->addAttacker(msg.sender_id, CCRect());
			}
			else if( msg.name == MSG_InAttackPosition)
			{
				// temporary do nothing
			}
			else
			{
				kkAssertMsgf(false, "[EnemyManager::fsmTranslater], [STATE_Attacking] can't handle message: %s", EnumStr(msg.name));
			}
		}
		break;


	default:
		break;
	}
}

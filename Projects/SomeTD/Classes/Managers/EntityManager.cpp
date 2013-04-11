//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "EntityManager.h"
using namespace cocos2d;

EntityManager::EntityManager()
	: id_seed(0)
{

}
EntityManager::~EntityManager()
{

}

EntityManager* EntityManager::mInstance = nullptr;
EntityManager* EntityManager::sharedEntityManager()
{
	if (EntityManager::mInstance == nullptr)
		EntityManager::mInstance = new EntityManager();
	return EntityManager::mInstance;
}

void EntityManager::addEntity(Entity* entity)
{
	this->mEntityMap.insert(std::pair<entity_id, Entity*>(entity->getEntityID(), entity));
}

Entity* EntityManager::getEntity(entity_id entityID)
{
	auto iter = mEntityMap.find(entityID);
	if(iter != mEntityMap.end())
		return iter->second;
	return nullptr;
}

void EntityManager::removeEntity(entity_id entityID)
{
	auto iter = mEntityMap.find(entityID);
	if(iter == mEntityMap.end())
		kkAssertMsg(false, "must find id in map! there must be some error some where!");
	mEntityMap.erase(iter);
}
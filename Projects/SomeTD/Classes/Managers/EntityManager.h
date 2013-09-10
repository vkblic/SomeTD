
#ifndef _ENTITY_MANAGER_
#define _ENTITY_MANAGER_

#include "cocos2d.h"
#include "../Sprites/Entity.h"
using namespace cocos2d;

class EntityManager 
{

public:
	~EntityManager();
	static EntityManager* sharedEntityManager();
private:
	EntityManager();
	static EntityManager* mInstance;

public:

	/*
	 *add a enemy node to manager, manager have responsibility to 
	 *retain or release it 
	 *
	 *@param	plFrameName: enemy node pointer
	 *@return	a valid enemy node pointer	 */
	void addEntity(Entity* entity);

	

	void removeEntity( ENTITY_ID entityID);

	/*
	 *get the nearness enemy unit in range 
	 *
	 *@param	pos: the centre point to calculate range.
	 *			rangeRadius: radius of the calculation range.
	 *@return	a valid enemy object pointer, if it's available
	 *@			if not(destroyed of out of screen), the value NULL
	 */
	Entity* getEntity( ENTITY_ID entityID);

	ENTITY_ID generateID()
	{
		id_seed++;
		return id_seed;
	}

private:
	ENTITY_ID id_seed;
	std::map<ENTITY_ID, Entity*> mEntityMap;
};

#endif

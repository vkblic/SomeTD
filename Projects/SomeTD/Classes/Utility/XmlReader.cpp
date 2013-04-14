#include "XmlReader.h"
#include "../libs/tinyxml2.h"
#include "../Model/Enumeration.h"
#include "../Helper/SpriteHelpers.h"


bool XmlReader::readAllLevelInfo(std::map<std::string, LevelModel>& levelInfoMap, const char* fileName)
{
	tinyxml2::XMLDocument doc;
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	doc.LoadFile(fullPath.c_str());

	if(doc.Error())
	{
		CCLog("config file: %s can't be read!", fullPath.c_str());
		CCAssert(false, "");
	}
	auto levelsNode = doc.FirstChild()->NextSibling();
	if(levelsNode->NoChildren())
		return false;

	auto levelNode  = levelsNode->FirstChild();
	//std::map<std::string, EnemyModel>* dic = new std::map<std::string, EnemyModel>();
	do 
	{
		LevelModel levelModel;
		auto element = levelNode->ToElement();

		// 2. info 
		strcpy(levelModel.name, element->Attribute("name"));
		strcpy(levelModel.mapFile, element->Attribute("mapFile"));
		levelModel.waveCount = atoi(element->Attribute("waveCount"));
		levelModel.waveInterval = atof(element->Attribute("waveInterval"));
		levelModel.entryCount = atoi(element->Attribute("entryCount"));
		levelModel.waysEveryEntry = atoi(element->Attribute("waysEveryEntry"));


		// 2. animations
		auto waveNode = levelNode->FirstChildElement();

		do 
		{
			//wave
			WaveModel waveModel;
			waveModel.id = atoi(waveNode->Attribute("id"));
			auto entryNode = waveNode->FirstChildElement();

			do 
			{
				//entry every wave 
				auto enemyNode = entryNode->FirstChildElement();
				do 
				{
					//enemise every entry
					WaveEnemyModel waveEnemy;
					waveEnemy.entryID =  atoi(entryNode->Attribute("entryID"));

					strcpy(waveEnemy.enemyName, enemyNode->Attribute("enemyName"));
					waveEnemy.delay = atof(enemyNode->Attribute("delay"));
					waveEnemy.wayID = atoi(enemyNode->Attribute("wayID"));
					waveModel.enemise.push_back(waveEnemy);
					enemyNode = enemyNode->NextSiblingElement();
				} while (enemyNode != NULL);

				entryNode = entryNode->NextSiblingElement();
			} while (entryNode != NULL);

			levelModel.waves.push_back(waveModel);
			waveNode = waveNode->NextSiblingElement();
		} while (waveNode != NULL);

		levelInfoMap.insert(std::map<std::string, LevelModel>::value_type(levelModel.name, levelModel));
		levelNode = levelNode->NextSibling();
	} while (levelNode != NULL);

	return true;
}


bool XmlReader::readActiveObjectInfoFromFile(std::map<std::string, ActiveObjModel>& objectsInfoMap, const char* fileName)
{
	tinyxml2::XMLDocument doc;
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	doc.LoadFile(fullPath.c_str());
	
	if(doc.Error())
	{
		CCLog("config file: %s can't be read!", fullPath.c_str());
		CCAssert(false, "");
	}
	auto objectsNode = doc.FirstChild()->NextSibling();
	if(objectsNode->NoChildren())
		return false;

	auto objectNode  = objectsNode->FirstChild();
	//std::map<std::string, EnemyModel>* dic = new std::map<std::string, EnemyModel>();
	do 
	{
		ActiveObjModel object;
		auto element = objectNode->ToElement();

		// 2. info 
		strcpy(object.name, element->Attribute("name"));
		strcpy(object.textureSet, element->Attribute("textureSet"));
		strcpy(object.plist, element->Attribute("plist"));
		auto infoElement = objectNode->FirstChildElement();
		object.hp = atoi(infoElement->Attribute("hp"));
		object.physicalAttack = atoi(infoElement->Attribute("physicalAttack"));
		object.physicalDefend = atoi(infoElement->Attribute("physicalDefend"));
		object.magicDefend = atoi(infoElement->Attribute("magicDefend"));
		object.magicAttack = atoi(infoElement->Attribute("magicAttack"));
		object.speed = atof(infoElement->Attribute("speed"));
		object.alertRange = atoi(infoElement->Attribute("alertRange"));
		object.defaultFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(infoElement->Attribute("defaultFrame"));

		// 2. animations
		auto animations = objectNode->FirstChild()->NextSiblingElement();

		if(!animations->NoChildren())
		{
			std::string defaultTag = animations->Attribute("defaultTag");
			auto animateElement = animations->FirstChildElement();
			do 
			{
				bool restoreOriginalFrame = false;
				if(strcmp("true", animateElement->Attribute("restoreOriginalFrame")) == 0)
					restoreOriginalFrame = true;
				std::string tag = animateElement->Attribute("tag");
				CCAnimation* animate = addAnimationWithFramesToCache(
					animateElement->Attribute("name"), animateElement->Attribute("tag"),
					atoi(animateElement->Attribute("startIndex")), atoi(animateElement->Attribute("endIndex")), atoi(animateElement->Attribute("framesInterval")), 
					restoreOriginalFrame, atoi(animateElement->Attribute("loop"))) ;

				if(tag == "move_up")
				{
					object.animations[ActiveObjTag_MoveUp] = animate;
					if(defaultTag == tag)
						object.animations[ActiveObjTag_Default] = animate;
				}
				else if (tag == "move_down")
				{
					object.animations[ActiveObjTag_MoveDown] = animate;
					if(defaultTag == tag)
						object.animations[ActiveObjTag_Default] = animate;
				}
				else if (tag == "move_rightleft")
				{
					object.animations[ActiveObjTag_MoveRightLeft] = animate;
					if(defaultTag == tag)
						object.animations[ActiveObjTag_Default] = animate;
				}
				else if (tag == "dead")
				{
					object.animations[ActiveObjTag_Dead] = animate;
					if(defaultTag == tag)
						object.animations[ActiveObjTag_Default] = animate;
				}
				else if (tag == "attack")
				{
					object.animations[ActiveObjTag_Attack] = animate;
					if(defaultTag == tag)
						object.animations[ActiveObjTag_Attack] = animate;
				}
				else
				{
					CCLog("error! enemy animation tag:[%s], unidentifiable!", tag.c_str());
					CCAssert(false, "enemy animation tag:[%s], unidentifiable£¡");
					return false;
				}

				animateElement = animateElement->NextSiblingElement();
			} while (animateElement != NULL);
		}

		objectsInfoMap.insert(std::map<std::string, ActiveObjModel>::value_type(object.name, object));
		objectNode = objectNode->NextSibling();
	} while (objectNode != NULL);

	return true;
}
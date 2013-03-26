#include "XmlReader.h"
#include "../libs/tinyxml2.h"
#include "../Model/Enumeration.h"
#include "../Helper/SpriteHelpers.h"


bool XmlReader::readAllLevelInfo(std::map<std::string, LevelModel>& levelInfoMap, const char* fileName)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName);

	if(doc.Error())
		return false;
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


bool XmlReader::readAllEnemyInfo(std::map<std::string, EnemyModel>& enemyInfoMap, const char* fileName)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName);

	if(doc.Error())
		return false;
	auto enemiseNode = doc.FirstChild()->NextSibling();
	if(enemiseNode->NoChildren())
		return false;

	auto enemyNode  = enemiseNode->FirstChild();
	//std::map<std::string, EnemyModel>* dic = new std::map<std::string, EnemyModel>();
	do 
	{
		EnemyModel enemyModel;
		auto element = enemyNode->ToElement();

		// 2. info 
		strcpy(enemyModel.name, element->Attribute("name"));
		strcpy(enemyModel.textureSet, element->Attribute("textureSet"));
		strcpy(enemyModel.plist, element->Attribute("plist"));
		auto infoElement = enemyNode->FirstChildElement();
		enemyModel.hp = atoi(infoElement->Attribute("hp"));
		enemyModel.physicalAttack = atoi(infoElement->Attribute("physicalAttack"));
		enemyModel.physicalDefend = atoi(infoElement->Attribute("physicalDefend"));
		enemyModel.magicDefend = atoi(infoElement->Attribute("magicDefend"));
		enemyModel.magicAttack = atoi(infoElement->Attribute("magicAttack"));
		enemyModel.speed = atof(infoElement->Attribute("speed"));

		enemyModel.defaultFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(infoElement->Attribute("defaultFrame"));

		// 2. animations
		auto animations = enemyNode->FirstChild()->NextSiblingElement();

		if(!animations->NoChildren())
		{
			std::string defaultTag = animations->Attribute("defaultTag");
			auto animateElement = animations->FirstChildElement();
			do 
			{
				std::string tag = animateElement->Attribute("tag");
				CCAnimation* animate = addAnimationWithFramesToCache(
					animateElement->Attribute("name"), animateElement->Attribute("tag"),
					atoi(animateElement->Attribute("startIndex")), atoi(animateElement->Attribute("endIndex")), atoi(animateElement->Attribute("framesInterval")), 
					false, atoi(animateElement->Attribute("loop"))) ;

				if(tag == "move_up")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveUp] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "move_down")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveDown] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "move_right")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveRight] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "move_left")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveLeft] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "move_leftup")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveLeftUp] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "move_leftdown")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveLeftDown] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "move_rightup")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveRightUp] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "move_rightdown")
				{
					enemyModel.animations[eEnmeyTag::EnmeyTag_MoveRightDown] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "dead")
				{
					enemyModel.animations[eEnmeyTag::EnemyTag_Dead] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Default] = animate;
				}
				else if (tag == "attack")
				{
					enemyModel.animations[eEnmeyTag::EnemyTag_Attack] = animate;
					if(defaultTag == tag)
						enemyModel.animations[eEnmeyTag::EnemyTag_Attack] = animate;
				}
				else
				{
					CCLog("error! enemy animation tag:[%s], unidentifiable!",tag);
					CCAssert(false, "enemy animation tag:[%s], unidentifiable£¡");
					return false;
				}

				animateElement = animateElement->NextSiblingElement();
			} while (animateElement != NULL);
		}

		enemyInfoMap.insert(std::map<std::string, EnemyModel>::value_type(enemyModel.name, enemyModel));
		enemyNode = enemyNode->NextSibling();
	} while (enemyNode != NULL);

	return true;
}
/*
*Weapon information
**/

#ifndef _ENGINE_H_
#define _ENGINE_H_

namespace SomeTD
{
	namespace Models
	{
		enum EngineType
		{
			Normal,
			
			HyperDrive,  //ship has HyperDrive can jump to pos 

		};
		// 		enum BodyType
		// 		{
		// 			Type1,
		// 			Type2
		// 		};
		class Engine
		{
		private:
			static int _SpeedByType[2];
		protected:
			//const int speed; //pitch per second
			//const int damage; // HP decrease per hit, depends on ship
			int zOrder;

			EngineType mWeaponType;
		public:

			Engine(EngineType type);


			/************************************************************************/
			/* Get engine speed */
			/************************************************************************/
			int GetBulletSpeed()
			{
				return _SpeedByType[mWeaponType];
			}
		};
	}
}

#endif
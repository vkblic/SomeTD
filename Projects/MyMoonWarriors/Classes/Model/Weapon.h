/*
*Weapon information
**/

#ifndef _WEAPON_H_
#define _WEAPON_H_

namespace SomeTD
{
	namespace Models
	{
		enum WeaponType
		{
			MachineGun,
			NavalGun
		};
		// 		enum BodyType
		// 		{
		// 			Type1,
		// 			Type2
		// 		};
		class Weapon
		{
		private:
			static char* _BulletTextureNameByType[2]; //there's only two texture for now
			static int _DamageByType[2];
			static int _SpeedByType[2];
		protected:
			//const int speed; //pitch per second
			//const int damage; // HP decrease per hit, depends on ship
			int zOrder;

			WeaponType mWeaponType;
		public:

			Weapon(WeaponType type);

			/************************************************************************/
			/* Get damage number of this weapon*/
			/************************************************************************/
			int GetDamage()
			{
				return _DamageByType[mWeaponType];
			}

			/************************************************************************/
			/* Get bullet's texture name of this weapon*/
			/************************************************************************/
			char* GetBulletTextureName()
			{
				return _BulletTextureNameByType[mWeaponType];
			}

			/************************************************************************/
			/* Get bullet speed of this weapon*/
			/************************************************************************/
			int GetBulletSpeed()
			{
				return _SpeedByType[mWeaponType];
			}
		};
	}
}

#endif
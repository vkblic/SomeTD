
#ifndef _SHIP_BODY_H_
#define  _SHIP_BODY_H_

namespace SomeTD
{
	namespace Models
	{
		enum BodyType
		{
			Huge,
			Normal,
			Mini
		};
		struct ShipSize
		{
			int Height;
			int Weight;

		};
		class ShipBody
		{
		public:
			ShipBody();

			ShipBody(BodyType type);

			/************************************************************************/
			/* Get Texture name of this body*/
			/************************************************************************/
			char* GetTextureName()
			{
				return _ShipTextureNameByType[_type];
			}
			ShipSize GetShipSize()
			{
				return _ShipSizeByType[_type];
			}
		protected:
			BodyType _type;

		private:
			static char* _ShipTextureNameByType[3]; //there's only two texture for now
			static ShipSize _ShipSizeByType[3];
			//static int _DamageByType[2];
			//static int _SpeedByType[2];
		};
	}
}

#endif
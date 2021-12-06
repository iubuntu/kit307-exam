
#include "Mesh.h"
#include "GameObject.h"

namespace T3D
{
	class Clock : public GameObject
	{
	public:
		Clock(T3DApplication* app,float size);
		virtual ~Clock(void);
		void setMaterials(Material*);
		void setTransparencyEffect(Material* m);
		Transform* getMinuteHand();
	private:
		GameObject* base;
		GameObject* shell;
		GameObject* face;
		GameObject* face_center;
		GameObject* minute_center;
		GameObject* minuteHand;
		GameObject* hourHand;
		float size ;

		Mesh* createShell();
		Material* transparencyEffectMaterial;

	};
}



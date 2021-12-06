
#include "Mesh.h"
#include "GameObject.h"

namespace T3D
{
	class Clock : public GameObject
	{
	public:
		Clock(T3DApplication* app);
		virtual ~Clock(void);
		void setMaterials(Material*);
		void setTransparencyEffect(Material* m);
	private:
		GameObject* base;
		GameObject* glass;
		float size = 10;

		Mesh* createGlass();
		Material* transparencyEffectMaterial;

	};
}



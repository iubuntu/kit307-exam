
#include "Clock.h"
#include "Cylinder.h"
#include "Transform.h"
#include "Sweep.h"
#include "SweepPath.h"
#include "Sphere.h"
#include "ClockBase.h"

using namespace std;

namespace T3D
{


	void Clock::setMaterials(Material* m) {
		setMaterial(m);
		base->setMaterial(m);
		glass->setMaterial(transparencyEffectMaterial);

	}




	Clock::Clock(T3DApplication* app) : GameObject(app) {

		base = new GameObject(app);
		glass = new GameObject(app);
		
		base->setMesh(
			new ClockBase(size, 1, 3)
		);

		base->getTransform()->setParent(getTransform());
		base->getTransform()->name = "base";
		base->getTransform()->setLocalRotation(Vector3(0, 180 * Math::DEG2RAD,  0));


		glass->setMesh(
			createGlass()
		);

		glass->getTransform()->setParent(getTransform());
		glass->getTransform()->name = "glass";

	}

	Mesh* Clock::createGlass() {
		std::vector<Vector3> points;
		SweepPath path = SweepPath();
		path.makeCirclePath(1.1 * size, 16);

		points.push_back(Vector3(0, 2 * size, 0));
		points.push_back(Vector3(1.2*size, 2 * size, 0));
		points.push_back(Vector3(1.2*size, -size, 0));
		points.push_back(Vector3(1.1*size, -size, 0));
		points.push_back(Vector3(1.1*size, 1.9 * size, 0));
		points.push_back(Vector3(0, 1.9 * size, 0));

	
		return new Sweep(points, path,true);
	}

	void  Clock::setTransparencyEffect(Material* m) {
		transparencyEffectMaterial = m;
	}

	Clock::~Clock(void)
	{
		
	}
}

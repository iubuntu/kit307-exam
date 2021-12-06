
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
		face->setMaterial(m);
		face_center->setMaterial(m);
		minuteHand->setMaterial(m);
		hourHand->setMaterial(m);

		shell->setMaterial(transparencyEffectMaterial);

	}




	Clock::Clock(T3DApplication* app) : GameObject(app) {
		size = 10;
		float bezel_width = 1;
		float screen_depression = 3;
		float face_height = 1;
		base = new GameObject(app);
		shell = new GameObject(app);
		face = new GameObject(app);
		face_center = new GameObject(app);
		minute_center = new GameObject(app);
		minuteHand = new GameObject(app);
		hourHand = new GameObject(app);
		
		base->setMesh(
			new ClockBase(size, bezel_width, screen_depression)
		);

		base->getTransform()->setParent(getTransform());
		base->getTransform()->name = "base";
		base->getTransform()->setLocalRotation(Vector3(0, 180 * Math::DEG2RAD,  0));

		face->setMesh(
			new Cylinder(size / 2, face_height, 36)
		);

		face->getTransform()->name = "face";
		face->getTransform()->setParent(base->getTransform());
		face->getTransform()->setLocalPosition(Vector3(
			0,
			0,
			-(size-screen_depression+ face_height)
		));
		face->getTransform()->setLocalRotation(Vector3( 90 * Math::DEG2RAD,0, 0));

		face_center->setMesh(
			new Cylinder(1, face_height/2, 36)
		);

		face_center->getTransform()->name = "face_center";
		face_center->getTransform()->setParent(face->getTransform());
		face_center->getTransform()->setLocalPosition(Vector3(0,-face_height,0));

		minute_center->setMesh(
			new Cylinder(1, face_height / 2, 36)
		);

		minute_center->getTransform()->name = "face_center";
		minute_center->getTransform()->setParent(face->getTransform());
		minute_center->getTransform()->setLocalPosition(Vector3(0, -face_height, 0));

		
		minuteHand->setMesh(
			new Cylinder(face_height / 4, size / 4, 36)
		);

		minuteHand->getTransform()->name = "minuteHand";
		minuteHand->getTransform()->setParent(minute_center->getTransform());
		minuteHand->getTransform()->setLocalRotation(Vector3(-90 * Math::DEG2RAD, 0, 0));
		minuteHand->getTransform()->setLocalPosition(Vector3(0,0,-size / 4));


		hourHand->setMesh(
			new Cylinder(face_height / 2, size / 16 * 3, 36)
		);

		hourHand->getTransform()->name = "hourHand";
		hourHand->getTransform()->setParent(face_center->getTransform());
		hourHand->getTransform()->setLocalRotation(Vector3(-90 * Math::DEG2RAD, 90 * Math::DEG2RAD, 0));
		hourHand->getTransform()->setLocalPosition(Vector3(-size / 16 * 3,0,0));


		shell->setMesh(
			createShell()
		);

		shell->getTransform()->setParent(getTransform());
		shell->getTransform()->name = "shell";

	}

	Transform* Clock::getMinuteHand() {
		return minute_center->getTransform();
	};

	Mesh* Clock::createShell() {
		std::vector<Vector3> points;
		SweepPath path = SweepPath();
		path.makeCirclePath(0, 4);

		float r = sqrt(2 * size*size)+1;

		points.push_back(Vector3(0, 2.1 * size, 0));
		points.push_back(Vector3(r/4, 1.85 * size, 0));
		points.push_back(Vector3(r/4*2, 1.55 * size, 0));
		points.push_back(Vector3(r/4*3, 1.45 * size, 0));
		points.push_back(Vector3(r/4*4+0.1*r, size, 0));

		points.push_back(Vector3(1.1*r, -size, 0));
		points.push_back(Vector3(r, -size, 0));
		points.push_back(Vector3(r, size, 0));
		points.push_back(Vector3(r / 4 * 3, 1.35 * size, 0));
		points.push_back(Vector3(r / 4 * 2, 1.45 * size, 0));

		points.push_back(Vector3(r / 4, 1.75 * size, 0));
		points.push_back(Vector3(0, 2 * size, 0));


	
		return new Sweep(points, path,true);
	}

	void  Clock::setTransparencyEffect(Material* m) {
		transparencyEffectMaterial = m;
	}

	Clock::~Clock(void)
	{
		
	}
}

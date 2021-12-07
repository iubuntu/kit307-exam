
#include "Clock.h"
#include "Cylinder.h"
#include "Transform.h"
#include "Sweep.h"
#include "SweepPath.h"
#include "Sphere.h"
#include "ClockBase.h"
#include "Cube.h"

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
		decoration->setMaterial(m);

		shell->setMaterial(transparencyEffectMaterial);

	}



	/*

	 8 sub-meshes  and 1 joint

	 Clock
		--> baseJoints
				--> shell
				--> base
					--> decoration
					--> face
						--> face_center
							--> hourHand
							--> minute_center
								 --> minuteHand

	*/
	Clock::Clock(T3DApplication* app,float size) : GameObject(app) {
		this->size = size;
		float bezel_width = 1;
		float screen_depression = 3;
		float face_height = 1;
		baseJoints = new GameObject(app);
		base = new GameObject(app);
		shell = new GameObject(app);
		face = new GameObject(app);
		face_center = new GameObject(app);
		minute_center = new GameObject(app);
		minuteHand = new GameObject(app);
		hourHand = new GameObject(app);
		decoration = new GameObject(app);
		
		baseJoints->getTransform()->setParent(getTransform());
		
		base->setMesh(
			new ClockBase(size, bezel_width, screen_depression)
		);

		base->getTransform()->setParent(baseJoints->getTransform());
		base->getTransform()->name = "base";
		//base->getTransform()->setLocalRotation(Vector3(0, 180 * Math::DEG2RAD,  0));

		face->setMesh(
			//new Cylinder(size / 2, face_height, 36)
			new Cube(size / 2)
		);

		face->getTransform()->name = "face";
		face->getTransform()->setParent(base->getTransform());
		face->getTransform()->setLocalPosition(Vector3(
			0,
			0,
			-(size-screen_depression+ face_height)
		));
		face->getTransform()->setLocalRotation(Vector3( -180 * Math::DEG2RAD, 90 * Math::DEG2RAD, 0));

		face_center->setMesh(
			new Cylinder(1, face_height/2, 36)
		);

		face_center->getTransform()->name = "face_center";
		face_center->getTransform()->setParent(face->getTransform());
		//face_center->getTransform()->setLocalPosition(Vector3(0,-face_height,0));
		face_center->getTransform()->setLocalRotation(Vector3(-90 * Math::DEG2RAD, -90 * Math::DEG2RAD, 0));

		minute_center->setMesh(
			new Cylinder(1, face_height / 2, 36)
		);

		minute_center->getTransform()->name = "minute_center";
		minute_center->getTransform()->setParent(face_center->getTransform());
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
		hourHand->getTransform()->setLocalPosition(Vector3(size / 16 * 3,0,0));


		shell->setMesh(
			createShell()
		);

		shell->getTransform()->setParent(baseJoints->getTransform());
		shell->getTransform()->name = "shell";


		/*
		  the decoration shape is like this
		 |\
		 |	\
		 |	 \
		 |   _|
		 |	|
		 |	 \
		 |	  \
		 |	   \
		 |_____ |
		*/
		SweepPath path;
		float r = sqrt(2 * size * size) + 1;

		// Make a profile
		std::vector<Vector3> points;
		points.push_back(Vector3(0, 3, 0));
		points.push_back(Vector3(1, 2.5, 0));
		points.push_back(Vector3(1, 2, 0));
		points.push_back(Vector3(0.5, 2, 0));
		points.push_back(Vector3(0.5, 1.5, 0));
		points.push_back(Vector3(2, 1, 0));
		points.push_back(Vector3(2, 0, 0));
		points.push_back(Vector3(0, 0, 0));


		Transform t1, t2, t3, t4;
		float angle = 90 * Math::DEG2RAD;
		t1.setLocalPosition(Vector3(r * cosf(angle), 0, r * std::sinf(angle)));
		t1.setLocalRotation(Quaternion(Vector3(0, -angle, 0)));

		angle = 2* 90 * Math::DEG2RAD;
		t2.setLocalPosition(Vector3(r* cosf(angle), 0, r* std::sinf(angle)));
		t2.setLocalRotation(Quaternion(Vector3(0, -angle, 0)));

		angle = 3 * 90 * Math::DEG2RAD;

		t3.setLocalPosition(Vector3(r* cosf(angle), 0, r* std::sinf(angle)));
		t3.setLocalRotation(Quaternion(Vector3(0, -angle, 0)));

		angle = 4 * 90 * Math::DEG2RAD;
		t4.setLocalPosition(Vector3(r* cosf(angle), 0, r* std::sinf(angle)));
		t4.setLocalRotation(Quaternion(Vector3(0, -angle, 0)));

		path.addTransform(t1);
		path.addTransform(t2);
		path.addTransform(t3);
		path.addTransform(t4);



		decoration->setMesh(new Sweep(points, path, true));
		decoration->getTransform()->setParent(base->getTransform());
		decoration->getTransform()->setLocalRotation(
			Vector3(0,45*Math::DEG2RAD,0)
		);
		decoration->getTransform()->setLocalPosition(
			Vector3(0, -size, 0)
		);
	}

	void Clock::setFace(Material* m) {
		face->setMaterial(m);
	}

	Transform* Clock::getMinuteHand() {
		return minute_center->getTransform();
	};

	/*	
	*
	
	
	shell profile is like this 
		|\
		\ \
		 \ \
		  \	\
		   \ \
		   | |
		   | |
		   | |
		   | |
		   | |
		   | |
	*/
	Mesh* Clock::createShell() {
		std::vector<Vector3> points;
		SweepPath path = SweepPath();
		path.makeCirclePath(0, 36);

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

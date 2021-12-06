#include "ClockAnimation.h"
#include "Vector3.h"
#include "Transform.h"




namespace T3D {
	ClockAnimation::ClockAnimation(T3DApplication* app) :Task(app) {
		pos = rand() % 50;
		rotationDegree = (float)0;
		obj = NULL;

	}

	void ClockAnimation::update(float dt) {


		rotationDegree += dt*10;



		obj->setLocalRotation(
			Vector3(
				0, rotationDegree * Math::DEG2RAD, 0
			)
		);

	}

}
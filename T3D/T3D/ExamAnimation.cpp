#include "ExamAnimation.h"
#include "Vector3.h"
#include "Transform.h"




namespace T3D {
	ExamAnimation::ExamAnimation(T3DApplication* app) :Task(app) {
		pos = rand() % 50;
		elapsedTime = (float)0;
		obj = NULL;

	}

	void ExamAnimation::update(float dt) {

		//Modify the update method of ExamAnimation so that 
		//the lamp moves from (0,0,0) to (1,0,0) in 5 seconds, 
		//and then from (1,0,0) to (0,1,0) in the following five seconds. 
		//You will need an 'if' statement that checks the time and calls the appropriate lerp().
		elapsedTime += dt;


		if (elapsedTime <= 5.0) {
			obj->setLocalPosition(Vector3(Math::smoothedLerp(-20, 20, elapsedTime / 5.0, 0.4), obj->getLocalPosition().y, obj->getLocalPosition().z));
		}
		else if (elapsedTime > 5.0 && elapsedTime <= 10.0) {

			obj->setLocalPosition(Vector3(Math::smoothedLerp(20, -20, (elapsedTime - 5.0) / 5.0, 0.4), obj->getLocalPosition().y, obj->getLocalPosition().z));
		}
		else {
			elapsedTime = 0;
		}





	}

}
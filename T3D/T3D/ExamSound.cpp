// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// ExamSound.cpp
//
// Class to manage test the sound system

#include "ExamSound.h"
#include "Input.h"

namespace T3D {

	ExamSound::ExamSound(T3DApplication* app) : Task(app)
	{
		music = app->soundManager->createMusic("Resources/bgm.mp3");
		sound = app->soundManager->createSound("Resources/beep.wav");

		music->play();
	}


	ExamSound::~ExamSound(void)
	{
	}

	void ExamSound::update(float dt) {
		if (Input::keysDown[KEY_SPACE]) {
			sound->play();
		}
	}

}

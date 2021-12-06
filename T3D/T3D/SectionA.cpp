
#include "SectionA.h"
#include "WinGLApplication.h"
#include "GLRenderer.h"
#include "Camera.h"

namespace T3D {

	SectionA::SectionA(void)
	{
		QuaternionNumber = 0;
		drawClock = nullptr;
		drawArea = new Texture(1024, 640, false);
		drawArea->clear(Colour(255, 255, 255, 255));
	}


	SectionA::~SectionA(void)
	{
	}





	bool SectionA::init() {
		WinGLApplication::init();


		renderer->loadTexture(drawArea, false);
		renderer->add2DOverlay(drawArea, 0, 0);

		drawClock = new DrawClock(this, drawArea);
		addTask(drawClock);




		return true;
	}
}

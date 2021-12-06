#include "WinGLApplication.h"
#include "Texture.h"
#include "DrawClock.h"
#include "Quaternion.h"
namespace T3D {

	class SectionA : public WinGLApplication
	{
	public:
		SectionA(void);

		~SectionA(void);

		bool init();

	private:
		Texture* drawArea;
		DrawClock* drawClock;
		int QuaternionNumber;
		Quaternion GetShoulderQuaternion();
	};

}

#pragma once

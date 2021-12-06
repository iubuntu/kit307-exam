#pragma once
#include "Task.h"
#include "T3DApplication.h"

namespace T3D {
	class ClockAnimation : public Task
	{
	public:
		ClockAnimation(T3DApplication* app);

		void update(float dt) override;


		Transform* obj;

	private:
		float rotationDegree;
		float pos;

	};
}
#pragma once

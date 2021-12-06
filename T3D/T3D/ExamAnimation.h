#pragma once
#include "Task.h"
#include "T3DApplication.h"

namespace T3D {
	class ExamAnimation : public Task
	{
	public:
		ExamAnimation(T3DApplication* app);

		void update(float dt) override;


		Transform* obj;

	private:
		float elapsedTime;
		float pos;

	};
}
#pragma once

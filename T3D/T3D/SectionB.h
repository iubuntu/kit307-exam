
#include "WinGLApplication.h"
#include "Texture.h"
#include "DrawTask.h"
#include "Quaternion.h"
namespace T3D {

	class SectionB : public WinGLApplication
	{
	public:
		SectionB(void);

		~SectionB(void);

		bool init();

	private:
		Texture* drawArea;
		DrawTask* drawTask;
		int QuaternionNumber;
		Quaternion GetShoulderQuaternion();
	};

}


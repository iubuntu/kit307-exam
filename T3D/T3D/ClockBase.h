
// ClockBase.h
//
// Simple ClockBase mesh with coloured sides

#pragma once
#include "Mesh.h"

namespace T3D
{
	//! \brief A simple parametric ClockBase Mesh.
	class ClockBase :
		public Mesh
	{
	public:
		//! \brief Create ClockBase with volume = `size^3`.
		ClockBase(
			float size,
			float bezel_width,
			float screen_depression);

		//! \brief Destroy ClockBase.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~ClockBase(void) = default;
	private:


		Vector3 inner;
		Vector3 outer;
		float bezel_width;
		float corner_radius;
		float screen_depression;
		float size;
		void setSize();
	};
}


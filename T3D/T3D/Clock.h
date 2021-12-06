// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Clock.h
//
// Simple Clock mesh with coloured sides

#pragma once
#include "Mesh.h"

namespace T3D
{
	//! \brief A simple parametric Clock Mesh.
	class Clock :
		public Mesh
	{
	public:
		//! \brief Create Clock with volume = `size^3`.
		Clock(
			float size,
			float bezel_width,
			float screen_depression);

		//! \brief Destroy Clock.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~Clock(void) = default;
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


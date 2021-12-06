
// Glass.h
//
// Simple Glass mesh with coloured sides

#pragma once
#include "Mesh.h"

namespace T3D
{
	//! \brief A simple parametric Glass Mesh.
	class Glass :
		public Mesh
	{
	public:
		//! \brief Create Glass with volume = `size^3`.
		Glass();

		//! \brief Destroy Glass.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~Glass(void) = default;

	};
}


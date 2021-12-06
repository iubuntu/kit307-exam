#pragma once
#include "Mesh.h"
namespace T3D
{
	//! \brief A simple parametric Pyramid Mesh.
	class Cylinder :
		public Mesh
	{
	public:

		Cylinder(float radius, float height, unsigned short density);


		virtual ~Cylinder(void) = default;
	};
}
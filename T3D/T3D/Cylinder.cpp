// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// cube.cpp
//
// Simple cube mesh with coloured sides
// Faces are GL quads.

#include "Cylinder.h"
#include "Math.h"

namespace T3D
{
	Cylinder::Cylinder(float radius, float height, unsigned short density)
	{
		float theta;
		// Init vertex and index arrays
		initArrays(density * 2 + 2,	// num vertices
			2 * density,		// num tris
			density);		// num quads

 // Set vertices

		float dTheta = Math::TWO_PI / density;

		for (short i = 0; i < density; i++) {
			theta = i * dTheta;
			float x = radius * cos(theta);
			float z = radius * sin(theta);

			setVertex(i, x, height, z);
			setVertex(i + density, x, -height, z);
		}
		setVertex(2 * density, 0, height, 0);
		setVertex(2 * density + 1, 0, -height, 0);

		for (short i = 0; i < density; i++) {
			setQuadFace(i,
				i,
				(i + 1) % density,
				density + (1 + i) % density,
				density + i
			);
			setTriFace(i, 2 * density, (i + 1) % density, i);
			setTriFace(i + density, 2 * density + 1, density + i, density + (1 + i) % density);

		}


		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();


	}
}

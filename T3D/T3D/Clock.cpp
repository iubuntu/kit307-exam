// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Clock.cpp
//
// Simple Clock mesh with coloured sides
// Faces are GL quads.

#include "Clock.h"

namespace T3D
{
	Clock::Clock(
		float size,
		float bezel_width,
		float screen_depression){

		this->size = size;
		this->bezel_width = bezel_width;
		this->screen_depression = screen_depression;

		setSize();

		// Init vertex and index arrays
		initArrays(4 * 8,	// num vertices
			0,		// num tris
			14);		// num quads

		// Set vertices

		int pos = 0;
		// front 
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, -size, size, -size);

		//back 
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, -size, size, size);

		//left
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, -size, -size, size);
		//right
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, -size, size);
		//bottom
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, -size, -size);
		//top
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, size, -size);

		// front
		
		// outer front
		// 24 25 26 27
		setVertex(pos++, -inner.x, -inner.y, -size);
		setVertex(pos++, inner.x, -inner.y, -size);
		setVertex(pos++, inner.x, inner.y, -size);
		setVertex(pos++, -inner.x, inner.y, -size);

		// inner front
		// 28 29 30 31
		setVertex(pos++, -inner.x, -inner.y, -inner.z);
		setVertex(pos++, inner.x, -inner.y, -inner.z);
		setVertex(pos++, inner.x, inner.y, -inner.z);
		setVertex(pos++, -inner.x, inner.y, -inner.z);

		// Build quads
		pos = 0;
		//front inner
		setQuadFace(pos++, 31,30,29,28);
		//back
		setQuadFace(pos++, 4, 5, 6, 7);
		//left
		setQuadFace(pos++, 11, 10, 9, 8);
		//right
		setQuadFace(pos++, 12, 13, 14, 15);
		//bottom
		setQuadFace(pos++, 19, 18, 17, 16);
		//top
		setQuadFace(pos++, 20, 21, 22, 23);
		// out 
		
		setQuadFace(pos++, 3, 2, 26, 27);
		setQuadFace(pos++, 2, 1, 25, 26);
		setQuadFace(pos++, 1, 0, 24, 25);
		setQuadFace(pos++, 0, 3, 27, 24);

		setQuadFace(pos++, 24, 28, 29, 25);
		setQuadFace(pos++, 25, 29, 30, 26);
		setQuadFace(pos++, 26, 30, 31, 27);
		setQuadFace(pos++, 31, 28, 24, 27);


		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();

		// Setup other arrays		
		pos = 0;
		//front
		for (int i = 0; i < 4; i++) {
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		}
		//back
		for (int i = 0; i < 4; i++) {
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		}
		//left
		for (int i = 0; i < 4; i++) {
			colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		}
		//right
		for (int i = 0; i < 4; i++) {
			colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		}
		//bottom
		for (int i = 0; i < 4; i++) {
			colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}
		//top
		for (int i = 0; i < 4; i++) {
			colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}

		//uvs
		pos = 0;
		for (int f = 0; f < 6; f++) {
			uvs[pos++] = 0; uvs[pos++] = 0;
			uvs[pos++] = 0; uvs[pos++] = 1;
			uvs[pos++] = 1; uvs[pos++] = 1;
			uvs[pos++] = 1; uvs[pos++] = 0;
		}
	}

	
	void Clock::setSize() {
			inner.x = size - bezel_width;
			inner.y = size - bezel_width;
			inner.z = size - screen_depression;

			outer.x = size - bezel_width;
			outer.y = size - bezel_width;
			outer.z = -size;


		}



}

// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// DrawClock.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#pragma once
#include <vector>
#include <math.h>

#include "Task.h"
#include "T3DApplication.h"
#include "Renderer.h"
#include "Texture.h"
#include "Matrix3x3.h"
#include "Vector3.h"
#include "Math.h"

namespace T3D
{
	//! \brief Task subclass, used for implementing 2D drawing routines. 
	class DrawClock :
		public Task
	{
	public:
		//! \brief Creates a DrawClock that draws onto a Texture every frame.
		DrawClock(T3DApplication* app, Texture* tex);

		//! \brief Destroy DrawClock (trivially). 
		~DrawClock(void) = default;

		//! \brief Ensures that the drawing area is ready to be drawn onto.
		void init();

		//! \brief Draw a coloured line between two points using the Digital Differential Algorithm (DDA) algorithm.
		void drawDDALine(int x1, int y1, int x2, int y2, Colour c);

		//! \brief Draw a coloured line from between two points using the integer-only Bresenham algorithm
		void drawBresLine(int x1, int y1, int x2, int y2, Colour c);

		//! \brief Ticks the drawing routine for this frame.
		virtual void update(float dt);




	private:
		Texture* drawArea;

		//! \brief Add a pixel to be displayed this frame to the PixelPlotQueue.
		void pushPixel(int x, int y, Colour colour);

		//! \brief Write all pushed pixel changes to drawArea, displaying errors to the console and log file.
		void flushPixelQueue();

		//! \brief Wrapper for pixel data, used by the pixel plot queue
		struct Pixel
		{
			int x = 0;
			int y = 0;
			Colour colour = { 0xFF, 0, 0xFF, 0xFF }; // Anything dodgy should show up as magenta
		};

		//! \brief One frames worth of pixels to blit onto the drawArea
		std::vector<Pixel> pixelPlotQueue;

		// exam start
		void drawFilledCircle(int cx, int cy, int r, Colour c);
		void drawCircle(int cx, int cy, int r, Colour c);
		void drawTriangles(std::vector<Vector3>);
		void DrawHands();
		void drawSquare(std::vector<Vector3> points);
		void drawClockScale(int cx, int cy, int r, Colour c);
		void drawClockScale(int cx, int cy, int r, Colour c, float width, unsigned char density);
		float RotateData = 20;

		Vector3 center = Vector3(400, 300, 1);
		float width = 5;
		float height = 100;

		// exam end

	};

}


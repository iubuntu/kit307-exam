// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GameObject.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#include <math.h>
#include "Renderer.h"
#include "DrawClock.h"
#include "Logger.h"

namespace T3D
{
	/*
	 * \param app Application root
	 * \param tex Texture to draw onto
	 *
	 * \note `tex` should be initialised, and registered with the renderer as both a loaded Texture and a 2D Overlay. This can be done using `new Texture(...)`, `loadTexture(...)`, and finally `add2DOverlay(...)`.
	 * \note If nothing is drawing on the screen, ensure the returned DrawClock object is added to the list of Tasks from the callsite using `addTask(...).
	 * \note If there is nothing on the screen still, check the visual studio console for error messages in case something is out of bounds.
	 *
	 */
	DrawClock::DrawClock(T3DApplication* app, Texture* tex) : Task(app)
	{
		drawArea = tex;

		// @BoundsCheck - requires using pushPixel
		// Reserve some space for the buffer, as its unlikely only few pixels will be plotted
		// const uint32_t pixelsToReserve = 512;
		// pixelPlotQueue.reserve(pixelsToReserve);

		init();
		logger::Log(priority::Info, output_stream::All, category::Task, "Initialised DrawClock");
	}

	/*
	 * \param
	 * \note This isn't necessary. It could be inlined into the constructor.
	 * 
		- [x] Straight lines

		- [x] Curved lines

		- [x] Filled shapes

		- [x] Translation, scale and rotation transformations

		- [x] Matrix composition

	 */
	void DrawClock::init() {
		drawArea->clear(Colour(255, 255, 255, 255));
		
		std::vector<Vector3> clockBackGroundShape;

		clockBackGroundShape.push_back(Vector3(center.x-250, center.y-250 , 1));
		clockBackGroundShape.push_back(Vector3(center.x-250, center.y+250 - width, 1));
		clockBackGroundShape.push_back(Vector3(center.x+250, center.y+250 - width, 1));
		clockBackGroundShape.push_back(Vector3(center.x+250, center.y+250 - width, 1));

		// Straight lines
		drawSquare(clockBackGroundShape);
		// Filled shapes
		drawFilledCircle(center.x, center.y, 200, Colour(103, 51, 30, 255));

		drawFilledCircle(center.x, center.y, 180, Colour(101, 93, 66, 255));



	}

	/*
	 * \param x1 Start x pixel coordinate
	 * \param y1 Start y pixel coordinate
	 * \param x2 End x pixel coordinate
	 * \param y2 End y pixel coordinate
	 * \param Colour of line
	 *
	 * \note Uses floating-point numbers as seen in the 2D graphics lecture.
	 * \note `pushPixel` is used to do large batches of *bounds-checked* pixel drawing, which you may prefer to your application crashing if you go outside the texture area.
	 */
	void DrawClock::drawDDALine(int x1, int y1, int x2, int y2, Colour c) {
		float deltay = y2 - y1;
		float deltax = x2 - x1;
		int step = abs(abs(deltax) > abs(deltay) ? deltax : deltay);
		float x = x1;
		float y = y1;

		float xIncrement = (deltax) / (float)step;
		float yIncrement = (deltay) / (float)step;

		for (int i = 1; i <= step; ++i)
		{
			x = x + xIncrement;  // increment in x at each step
			y = y + yIncrement;  // increment in y at each step
			drawArea->plotPixel(round(x), round(y), c);
		}
	}


	/*
	 * \param x1 Start x pixel coordinate
	 * \param y1 Start y pixel coordinate
	 * \param x2 End x pixel coordinate
	 * \param y2 End y pixel coordinate
	 * \param Colour of line
	 *
	 * \note UNIMPLEMENTED! That's your job in the tutorials.
	 */
	void DrawClock::drawBresLine(int x1, int y1, int x2, int y2, Colour c)
	{ /* UNIMPLEMENTED */
	}

	/*
	 * \param dt Change in time
	 *
	 * \note Make sure to clear the `drawArea` before you write to it.
	 */
	void DrawClock::update(float dt) {
		RotateData += dt;

		drawFilledCircle(center.x, center.y, 175, Colour(212, 134, 78, 0));

		drawClockScale(center.x, center.y,170, Colour(200, 53, 20, 0),10,12);
		//drawCircle(center.x, center.y, 166, Colour(200, 53, 20, 0));
		//drawFilledCircle(center.x, center.y, 165, Colour(212, 134, 78, 0));
		
		// Translation, scale and rotation transformations
		//  Matrix composition
		DrawHands();
		drawFilledCircle(center.x, center.y, 22, Colour(0, 0, 0, 0));
		drawFilledCircle(center.x, center.y, 20, Colour(200, 53, 20, 0));

		// @BoundsCheck- requires using pushPixel
		// Plots pixels made to the drawArea this frame, clearing the pixel queue.
		// flushPixelQueue();
		app->getRenderer()->reloadTexture(drawArea);
	}


	/*
	 * Provides a bounds-checked and more efficient way to draw onto a surface then `plotPixel()`.
	 * Diagnostic messages for out-of-bounds drawing are displayed onto the console, and into `T3D_Log.txt`.
	 *
	 * \param x x pixel coordinate to draw onto
	 * \param y y pixel coordinate to draw onto
	 * \param Colour pixel colour
	 *
	 */
	void DrawClock::pushPixel(int x, int y, Colour colour)
	{
		pixelPlotQueue.push_back(Pixel{ x, y, colour });
	}

	/*
	 * Provides a bounds-checked and more efficient way to draw onto a surface then `plotPixel()`.
	 * Diagnostic messages for out-of-bounds drawing are displayed onto the console, and into `T3D_Log.txt`.
	 *
	 *
	 * \note This should be called at the end of the `update` function.
	 */
	void DrawClock::flushPixelQueue()
	{
		const uint32_t MaxOutOfBoundsCount = 10u;
		uint32_t OutOfBoundsCount = 0u;
		for (auto& Pixel : pixelPlotQueue)
		{
			bool PixelWithinWidth = (Pixel.x >= 0 && Pixel.x < drawArea->getWidth());
			bool PixelWithinHeight = (Pixel.y >= 0 && Pixel.y < drawArea->getHeight());
			bool PixelWithinBounds = (PixelWithinWidth && PixelWithinHeight);

			if (PixelWithinBounds)
			{
				drawArea->plotPixel(Pixel.x, Pixel.y, Pixel.colour);
			}
			else
			{
				if (OutOfBoundsCount < MaxOutOfBoundsCount)
				{
					logger::Log(priority::Tracing,
						output_stream::File,
						category::Debug,
						"Pixel out of bounds!\n"
						"\tWidth  :: [0 <= X <= %4u :: %4d :: %5s]%s\n"
						"\tHeight :: [0 <= Y <= %4u :: %4d :: %5s]%s\n"
						,
						app->getRenderer()->WindowWidth,
						Pixel.x, PixelWithinWidth ? "OK" : "ERROR",
						PixelWithinWidth ? "" : " <<<\n",
						app->getRenderer()->WindowHeight,
						Pixel.y, PixelWithinHeight ? "OK" : "ERROR",
						PixelWithinHeight ? "" : " <<<\n");
				}
				OutOfBoundsCount++;
			}
		}

		if (OutOfBoundsCount >= MaxOutOfBoundsCount)
		{
			logger::Log(priority::Tracing,
				output_stream::File,
				category::Debug,
				"... Repeats %u times ...\n"
				,
				OutOfBoundsCount - MaxOutOfBoundsCount);
		}

		pixelPlotQueue.clear();
	}

	// exam start
	void DrawClock::drawFilledCircle(int cx, int cy, int r, Colour c) {


		for (int cursor = 0; cursor <= r; cursor++) {
			int y, x;

			y = r - cursor;
			x = sqrt(r * r - y * y);

			drawDDALine(cx - x, cy - y, cx + x, cy - y, c);
			drawDDALine(cx - x, cy + y, cx + x, cy + y, c);

		}

	}


	void DrawClock::drawCircle(int cx, int cy, int r, Colour c) {



		std::vector<Vector3> points;


		for (float theta = 0; theta < Math::TWO_PI; theta += 0.03)
		{
			int x = cx + r * cos(theta);
			int y = cy + r * sin(theta);

			points.push_back(Vector3(x, y, 1));

		}

		int size = points.size();
		for (unsigned int i = 0; i < size; i++) {
			drawDDALine(
				points[i].x,
				points[i].y,
				points[(i + 1) % size].x,
				points[(i + 1) % size].y,
				c
			);
			//printf("from %d to %d\n", 3 * i + j, 3 * i + (j + 1) % 3);


		}


	}


	void DrawClock::drawClockScale (int cx, int cy, int r, Colour c) {



		std::vector<Vector3> points;


		for (float theta = 0; theta < Math::TWO_PI; theta += 0.1)
		{
			int x = cx + r * cos(theta);
			int y = cy + r * sin(theta);

			points.push_back(Vector3(x, y, 1));

		}

		int size = points.size();
		for (unsigned int i = 0; i < size; i++) {
			drawDDALine(
				cx,
				cy,
				points[(i + 1) % size].x,
				points[(i + 1) % size].y,
				c
			);
			//printf("from %d to %d\n", 3 * i + j, 3 * i + (j + 1) % 3);

		}

	}

	void DrawClock::drawClockScale(int cx, int cy, int r, Colour c,float width, unsigned char density) {


		// outer circle
		drawCircle(cx, cy, r, c);
		// inner circle
		drawCircle(cx, cy, r-width, c);

		std::vector<Vector3> points;


		for (float theta = 0; theta < Math::TWO_PI; theta += Math::TWO_PI/density)
		{
			for (float i = 0; i < 0.01; i += 0.005) {
				int innerX = cx + r * cos(theta + i);
				int innerY = cy + r * sin(theta + i);

				int outerX = cx + (r - width) * cos(theta + i);
				int outerY = cy + (r - width) * sin(theta + i);

				points.push_back(Vector3(innerX, innerY, 1));
				points.push_back(Vector3(outerX, outerY, 1));

			}

			for (int secondScale = 0; secondScale < 10; secondScale++) {

					float i = secondScale * Math::TWO_PI / density / 10;
					int innerX = cx + r * cos(theta + i);
					int innerY = cy + r * sin(theta + i);

					int outerX = cx + (r - width) * cos(theta + i);
					int outerY = cy + (r - width) * sin(theta + i);

					points.push_back(Vector3(innerX, innerY, 1));
					points.push_back(Vector3(outerX, outerY, 1));
					
			}


		}

		int size = points.size();
		for (unsigned int i = 0; i < size; i+=2) {
			drawDDALine(
				points[i].x,
				points[i].y,
				points[(i + 1) % size].x,
				points[(i + 1) % size].y,
				c
			);
			//printf("from %d to %d\n", 3 * i + j, 3 * i + (j + 1) % 3);

		}

	}


	void DrawClock::drawTriangles(std::vector<Vector3> points) {
		int size = points.size() / 3;
		for (unsigned int i = 0; i < size; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				drawDDALine(
					points[3 * i + j].x,
					points[3 * i + j].y,
					points[3 * i + (j + 1) % 3].x,
					points[3 * i + (j + 1) % 3].y,
					Colour(0, 0, 0, 255)
				);
				//printf("from %d to %d\n", 3 * i + j, 3 * i + (j + 1) % 3);
			}
		}
	}

	void DrawClock::DrawHands() {
		std::vector<Vector3> hourHand, minuteHand, secondHand, changeSecondHand;

		hourHand.push_back(Vector3(center.x, center.y + width, 1));
		hourHand.push_back(Vector3(center.x, center.y - width, 1));
		hourHand.push_back(Vector3(center.x + height, center.y, 1));



		minuteHand.push_back(Vector3(center.x - width, center.y, 1));
		minuteHand.push_back(Vector3(center.x + width, center.y, 1));
		minuteHand.push_back(Vector3(center.x, center.y - height, 1));


		secondHand.push_back(Vector3(center.x - width, center.y, 1));
		secondHand.push_back(Vector3(center.x + width, center.y, 1));
		secondHand.push_back(Vector3(center.x, center.y - height, 1));


		Matrix3x3 mScaleSecondHand = Matrix3x3(
			0.5, 0, 0,
			0, 1.5, 0,
			0, 0, 1
		);

		Matrix3x3 mOrgain = Matrix3x3(
			1, 0, -center.x,
			0, 1, -center.y,
			0, 0, 1
		);

		Matrix3x3 mBack = Matrix3x3(
			1, 0, center.x,
			0, 1, center.y,
			0, 0, 1
		);

		float _degree = RotateData * Math::DEG2RAD;
		Matrix3x3 mRotation = Matrix3x3(
			cos(_degree), -sin(_degree), 0,
			sin(_degree), cos(_degree), 0,
			0, 0, 1
		);


		Matrix3x3 trans = mBack * mRotation * mScaleSecondHand * mOrgain;
		for (int i = 0; i < 3; i++) {
			//std::cout << mHead.GetColumn(i) * mRotation << "\n";
			Vector3 point = trans * secondHand[i];

			changeSecondHand.push_back(point);
		}

		drawTriangles(minuteHand);
		drawTriangles(changeSecondHand);
		drawTriangles(hourHand);
	}


	void DrawClock::drawSquare(std::vector<Vector3> points) {
		int size = points.size() / 4;
		for (unsigned int i = 0; i < size; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				drawDDALine(
					points[4 * i + j].x,
					points[4 * i + j].y,
					points[4 * i + (j + 1) % 4].x,
					points[4 * i + (j + 1) % 4].y,
					Colour(111, 104, 80, 255)
				);
				//printf("from %d to %d\n", 3 * i + j, 3 * i + (j + 1) % 3);
			}

		}

		int startx = points[0].x;
		int stopx = points[2].x;

		int starty = points[0].y;
		int stopy = points[1].y;

		for (int i = starty; i <= stopy; i++) {
			drawDDALine(startx, i, stopx, i, Colour(111, 104, 80, 255));
		}

	}
	// exam end

}

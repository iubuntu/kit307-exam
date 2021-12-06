// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// main.cpp
//
// Main entry point. Creates and runs a T3DApplication

#include "T3DTest.h"
#include "SectionA.h"
#include "ShaderTest.h"
#include "GLTestApplication.h"

#ifdef main
#undef main
#endif


using namespace T3D;

int main(int argc, char* argv[]) {

	// !!!!  important 

	// uncomment SectionA and comment SectionB to play SectionA
	T3DApplication* theApp = new SectionA();
	//T3DApplication* theApp = new SectionB();


	theApp->run();
	delete theApp;

	return 0;
}

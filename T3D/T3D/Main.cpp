// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// main.cpp
//
// Main entry point. Creates and runs a T3DApplication

#include "SectionA.h"
#include "SectionB.h"
#include "GLTestApplication.h"

#ifdef main
#undef main
#endif


using namespace T3D;

int main(int argc, char* argv[]) {

	// !!!!  important 

	// uncomment SectionA and comment SectionB to play SectionA
	//T3DApplication* theApp = new SectionA();
	T3DApplication* theApp = new SectionB();


	theApp->run();
	delete theApp;

	return 0;
}

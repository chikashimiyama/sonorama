#include "ofMain.h"
#include "Const.hpp"
#include "ofApp.h"
#include <limits.h>


int main( ){
	ofLog() << APP_NAME;
	// main window as debug window
	ofSetupOpenGL(400,400,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

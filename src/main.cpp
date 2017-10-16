#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1280,480,OF_WINDOW);
    ofGLWindowSettings settings;
    
    settings.setGLVersion(3, 2);
    settings.width = 1280;
    settings.height = 768;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());

}


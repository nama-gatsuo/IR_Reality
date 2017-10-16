#pragma once

#include "ofMain.h"
#include "ofxSyphonServer.h"
#include "ofxOsc.h"
#include "ofxMidi.h"

#include "LilySystem.hpp"
#include "RadialSystem.hpp"
#include "Lake.hpp"
#include "Warm.hpp"
#include "OctaSphere.hpp"
#include "Buildings.hpp"
#include "SnowParticle.hpp"
#include "MarimbaBlocks.hpp"
#include "Spirals.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    void randomize();
			
    LilySystem system;
    Lake lake;
    Warm warm;
    OctaSphere sphere;
    RadialSystem radSys;
    MarimbaBlocks blocks;
    
    Buildings build;
    SnowParticle snow;
    Spirals sps;
    
    ofEasyCam cam;
    ofVec3f from, to;
    
    ofxSyphonServer server;
    ofFbo inputFbo;
    
    
    const int port = 9999;
    ofxOscReceiver receiver;
    ofxMidiOut midiOut;
};

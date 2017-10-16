#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    receiver.setup(port);
    midiOut.listPorts();
    midiOut.openPort(0);
    
    inputFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F);
    
    cam.setFarClip(10000);
    randomize();
    
    server.setName("WinterFlower");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while (receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        string address = m.getAddress();
        vector<string> split = ofSplitString(address, "/");
        
        float velFloat = m.getArgAsFloat(0);
        int velInt = (int)(velFloat * 127);
        
        cout << split[1] +","+ split[2] + " vel: " + ofToString(velInt) << endl;
        
        // ch, note, velocity
        midiOut.sendNoteOn(ofToInt(split[0])+1, ofToInt(split[2]), velInt);
        
        int x = ofToInt(split[0]);
        int y = ofToInt(split[1]);
        
        switch (x) {
            case 0: sphere.bang(y, velFloat); break;
            case 1: radSys.bang(y, velFloat); break;
            case 2: lake.bang(y, velFloat); break;
            case 3: sps.bang(y, velFloat); break;
            case 4: blocks.bang(y, velFloat); break;
            case 5: warm.bang(y, velFloat); break;
            case 6: system.bang(y    , velFloat); break;
            case 7: break;
            default: break;
        }
        
    }
    
    system.update();
    lake.update();
    warm.update();
    sphere.update();
    radSys.update();
    blocks.update();
    sps.update();
    
    if (ofGetFrameNum() % 120 == 0) randomize();
    
    from = cam.getPosition();
    cam.setPosition((to - from) * 0.005 + from);
    cam.lookAt(ofVec3f(0,0,0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    inputFbo.begin();
    ofClear(0, 0, 0, 0);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    cam.begin();
    
    lake.draw();
    system.draw();
    warm.draw();
    sphere.draw();
    radSys.draw();
    blocks.draw();
    sps.draw();
    
    build.draw();
    snow.draw();
    
    cam.end();
    
    ofDisableBlendMode();
    
    inputFbo.end();
    
    inputFbo.draw(0,0);
    
    server.publishFBO(&inputFbo);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == ' ') {
    
        system.bang(3, 1.0);
        lake.bang(5, 1.0);
        warm.bang(6, 1.0);
        sphere.bang(3, 1.0);
        blocks.bang(2, 1.0);
        radSys.bang(3, 1.0);
        sps.bang(1, 1.0);
        
    }
    
    
}

void ofApp::randomize() {
    
    float coin = ofRandom(1.0);
    
    if (coin < 0.05) {
        to = ofVec3f(0, ofRandom(900, 1600), 0);
    } else if (coin < 0.45) {
        to = ofVec3f(ofRandom(300, 1000), ofRandom(0,500), ofRandom(300, 1000));
    } else {
        to = ofVec3f(ofRandom(-3000, 3000), ofRandom(0, 1000), ofRandom(-3000, 3000));
    }
    
    

}

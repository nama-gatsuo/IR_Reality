#include "ofApp.h"

class SnowParticle {
public:
    SnowParticle(){
        
        shader.setGeometryInputType(GL_POINTS);
        shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
        shader.setGeometryOutputCount(6);
        shader.load("shader/shader.vert", "shader/shader.frag", "shader/shader.geom");
        
        img.load("img/0.png");
        texSize.x = img.getWidth();
        texSize.y = img.getHeight();
        
        for (int j = 0; j < 10000; j++) {
            
            mesh.addVertex(ofVec3f(ofRandom(-2400,2400), ofRandom(-100, 1900), ofRandom(-2400,2400)));
            mesh.addNormal(ofVec3f(ofRandom(1.0), ofRandom(1.0), ofRandom(1.0)));
            
        }
        mesh.setMode(OF_PRIMITIVE_POINTS);
    };
    void update(){};
    void draw(){
        
        shader.begin();
        shader.setUniform3f("pos", ofVec3f(0, -100, 0));
        shader.setUniform1f("uTime", ofGetElapsedTimef()/10);
        shader.setUniformTexture("uImg", img.getTexture(), 0);
        shader.setUniform2f("texSize", texSize);
        
        mesh.draw();
        
        shader.end();
    
    };
    
private:
    ofVboMesh mesh;
    ofShader shader;
    ofVec2f texSize;
    ofImage img;
};

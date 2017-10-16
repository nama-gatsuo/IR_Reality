#include "ofMain.h"

class RadialObj {
public:
    RadialObj(){};
    RadialObj(int index, float velocity){
        
        height = -150;
        
        life = 1.0;
        rad = 20;
        width = velocity * 80;
        
        tStart = TWO_PI / 8.0 * index;
        tStep = TWO_PI / 8.0 / 6.0;
        float vNum = 0;
        for (int i = 0; i < 6; i++) {
            
            mesh.addVertex(ofVec3f(rad * sin(tStart + tStep*i),
                                   height,
                                   rad * cos(tStart + tStep*i ) ));
            
            mesh.addVertex(ofVec3f((rad + width) * sin(tStart + tStep*i),
                                   height,
                                   (rad + width) * cos(tStart + tStep*i) ));
            
            mesh.addVertex(ofVec3f(rad * sin(tStart + tStep*((float)i+0.5)),
                                   height,
                                   rad * cos(tStart + tStep*((float)i+0.5)) ));
            
            mesh.addVertex(ofVec3f((rad + width) * sin(tStart + tStep*((float)i+0.5)),
                                   height,
                                   (rad + width) * cos(tStart + tStep*((float)i+0.5)) ));
            
            mesh.addIndex(vNum);
            mesh.addIndex(vNum+1);
            mesh.addIndex(vNum+2);
            mesh.addIndex(vNum+1);
            mesh.addIndex(vNum+2);
            mesh.addIndex(vNum+3);
            
            vNum += 4;
        }
    
    };
    void update(){
        
        life -= 0.002;
        rad += 5;
        
        for (int i = 0; i < 6; i++) {
            
            mesh.setVertex(i*4,
                           ofVec3f(rad * sin(tStart + tStep*i),
                                   height,
                                   rad * cos(tStart + tStep*i ) ));
            mesh.setVertex(i*4+1,
                           ofVec3f((rad + width) * sin(tStart + tStep*i),
                                   height,
                                   (rad + width) * cos(tStart + tStep*i) ));
            mesh.setVertex(i*4+2,
                           ofVec3f(rad * sin(tStart + tStep*((float)i+0.5)),
                                   height,
                                   rad * cos(tStart + tStep*((float)i+0.5)) ));
            mesh.setVertex(i*4+3,
                           ofVec3f((rad + width) * sin(tStart + tStep*((float)i+0.5)),
                                   height,
                                   (rad + width) * cos(tStart + tStep*((float)i+0.5)) ));
        }
        
        
    };
    void draw(){
        
        ofSetColor(color.r, color.g, color.b, 72 * life);
        mesh.draw(OF_MESH_FILL);
        
        ofSetColor(color.r, color.g, color.b, 64);
        mesh.draw(OF_MESH_WIREFRAME);
    };
    float life;
private:
    float tStart, tStep;
    float height;
    float rad;
    float width;
    ofVboMesh mesh;
    ofColor color = ofColor(163, 100, 218);
};

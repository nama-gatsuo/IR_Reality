#include "ofNode.h"

class Lily : public ofNode {
public:
    Lily(){
        
        ofMatrix4x4 m;
        m.glScale(5, 5, 5);
        
        bFirst = true;
        createRing(&m);
        bFirst = false;
    };
    void update(){
        
        radX -= 0.001;
        
        if (radX > 0.15) radX = 0.15;
        if (radX < 0.02) radX = 0.02;
        
        alpha -= 2.0;
        
        if (alpha < 20) alpha = 20;
        if (alpha > 255) alpha = 255;
        
        // mesh update
        mesh.clearVertices();
        ofMatrix4x4 m;
        m.glScale(5, 5, 5);
        createRing(&m);
    
    };
    void customDraw(const ofBaseRenderer * renderer) const {
        
        ofSetColor(color.r, color.g, color.b, 60);
        renderer->draw(mesh, OF_MESH_WIREFRAME);
        
        ofSetColor(color.r, color.g, color.b, alpha);
        renderer->draw(mesh, OF_MESH_FILL);
    
    };
    
    void bang(float velocity){
        
        radX += 0.13 * velocity;
        alpha += 230 * velocity;
        
    };
    
    void createPetal(ofMatrix4x4 * m){
        
        ofVec3f vArray[17] = {
            ofVec3f(0,  0, 0),
            
            ofVec3f(2,  hSpace*1, -0.5).rotateRad(radX, 0, 0),
            ofVec3f(0,  hSpace*1,0).rotateRad(radX, 0, 0),
            ofVec3f(-2, hSpace*1, -0.5).rotateRad(radX, 0, 0),
            
            ofVec3f(3.2,hSpace*2, -0.4).rotateRad(radX*2, 0, 0),
            ofVec3f(0,  hSpace*2,0).rotateRad(radX*2, 0, 0),
            ofVec3f(-3.2,hSpace*2, -0.4).rotateRad(radX*2, 0, 0),
            
            ofVec3f(4,  hSpace*3, -0.3).rotateRad(radX*3, 0, 0),
            ofVec3f(0,hSpace*3,0).rotateRad(radX*3, 0, 0),
            ofVec3f(-4,  hSpace*3, -0.3).rotateRad(radX*3, 0, 0),
            
            ofVec3f(3.2,hSpace*4, -0.2).rotateRad(radX*4, 0, 0),
            ofVec3f(0,hSpace*4,0).rotateRad(radX*4, 0, 0),
            ofVec3f(-3.2,hSpace*4, -0.2).rotateRad(radX*4, 0, 0),
            
            ofVec3f(2,  hSpace*5, -0.1).rotateRad(radX*5, 0, 0),
            ofVec3f(0,hSpace*5,0).rotateRad(radX*5, 0, 0),
            ofVec3f(-2,  hSpace*5, -0.1).rotateRad(radX*5, 0, 0),
            
            ofVec3f(0,  hSpace*6, 0).rotateRad(radX*6, 0, 0)
        };
        
        int startNum = mesh.getNumVertices();
        
        for (int i = 0; i < 17; i++) {
            mesh.addVertex( *m * vArray[i] );
        }
        
        if (bFirst) {
            for (int i = 0; i < 60; i++) {
                mesh.addIndex( ofIndexType(iArray[i] + startNum));
            }
        }
        
    };
    
    void createRing(ofMatrix4x4 * m) {
        
        ofMatrix4x4 _m = *m;
        for (int i = 0; i < 6; i++) {
            
            _m.glRotate(60, 0, 1, 0);
            createPetal(&_m);
        
        }
        
    }
    
protected:
    ofVboMesh mesh;
    ofColor color = ofColor(178, 189, 108);
    float alpha = 20; // 20 - 200
    
    float hSpace = 4;
    float radX = 0.02; //0.02 - 0.15
    bool bFirst;
    
    int iArray[60] = {
        0,1,2,    0,2,3,
        1,4,2,    2,4,5,    2,5,6,   2,6,3,
        4,7,5,    5,7,8,    5,8,9,   5,9,6,
        7,10,8,  8,10,11,   8,11,12, 8,12,9,
        10,13,11, 11,13,14, 11,14,15, 11,15,12,
        13,16,14, 14,16,15
    };
    
};

#include "ofMain.h"

class OctaSphere {
public:
    OctaSphere(){
        
        float height = 500.0;
        
        float ov[6][3] = {
            {1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}
        };
        
        unsigned int oi[8][3] = {
            {0, 2, 4}, {0, 4, 3}, {0, 3, 5}, {0, 5, 2},
            {1, 2, 5}, {1, 5, 3}, {1, 3, 4}, {1, 4, 2}
        };
        
        ofVec3f v;
        ofNode node;
        float r = 80;
        for (int t = 0; t < 16; t++) {
            
            for (int s = 0; s < 8; s++) {
                
                v.x = r * cos(TWO_PI * t/16.0) * sin(PI * (s+1)/10.0);
                v.z = r * sin(TWO_PI * t/16.0) * sin(PI * (s+1)/10.0);
                v.y = r * cos(PI * (s+1)/10.0);
                
                sphereVert.push_back(v);
                
                // createMatirx
                node.setPosition(v.x, v.y + height, v.z);
                node.lookAt(ofVec3f(0, height, 0));
                
                ms.push_back(node.getGlobalTransformMatrix());
                
            }
        
        }
        
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                polyhedron.addVertex(ofVec3f(ov[ oi[i][j] ][0], ov[ oi[i][j] ][1], ov[ oi[i][j] ][2] ) * size);
            }
        }
        
    };
    void update() {
        
        for (int i = 0; i < 8; i++) {
        
            power[i] -= 0.01;
            if (power[i] < 0.0) power[i] = 0.0;
            if (power[i] > 1.0) power[i] = 1.0;
            
        }
        
    };
    void draw() {
        
        ofMatrix4x4 m;
        ofPushMatrix();
        ofRotateY(ofGetElapsedTimef() * 10.0);
        
        for (int i = 0; i < ms.size(); i++) {
            
            float p = power[i % 8];
            
            m = ms[i];
            m.glScale(0.8, 0.8, 1.0 + p * 2.5);
            
            ofPushMatrix();
            ofMultMatrix(m);
            ofSetColor(color.r, color.g, color.b, 48);
            polyhedron.draw(OF_MESH_WIREFRAME);
            ofSetColor(color.r, color.g, color.b, 180 * p);
            polyhedron.draw(OF_MESH_FILL);
            ofPopMatrix();
        }
        ofPopMatrix();
    };
    
    void bang(int index, float velocity) {
        
        power[index] += velocity;
        
    };
    
private:
    vector<ofVec3f> sphereVert;
    ofVboMesh polyhedron;
    vector<ofMatrix4x4> ms;
    float power[8];
    
    float size = 20.0;
    ofColor color = ofColor(128, 154, 219);
    float alpha;
};

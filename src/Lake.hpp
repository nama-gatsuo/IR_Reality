#include "ofMain.h"

class Lake {
public:
    Lake(){
        
        y = -100;
        
        float r;
        for (int i = 0; i < 8; i++) {
            
            vs.clear();
            
            r = 150 * i + 180;
            power[i] = 0.0;
            
            for (int j = 0; j < 64; j++) {
                
                ofVec3f v = ofVec3f(r * cos(TWO_PI / 64 * j), y, r * sin(TWO_PI / 64 * j) );
                vs.push_back(v);
                vs.push_back(v);
            }
            ofVec3f v = ofVec3f(r * cos(0), y, r * sin(0) );
            vs.push_back(v);
            vs.push_back(v);

            vbo[i].setVertexData(vs.data(), vs.size(), GL_DYNAMIC_DRAW);
        }
        
    };
    
    void update(){
        
        float r;
        float random;
        for (int i = 0; i < 8; i++) {
            
            power[i] -= 0.01;
            if (power[i] > 1.0) power[i] = 1.0;
            if (power[i] < 0.0) power[i] = 0.0;
            
            r = 150 * i + 180;
            
            for (int j = 0; j < 64; j++) {
                
                random = ofRandom(-1.0, 1.0) * 120 * power[i];
                
                vs[j*2].x = r * cos(TWO_PI / 64 * j);
                vs[j*2].y = y + random;
                vs[j*2].z = r * sin(TWO_PI / 64 * j);
                
                vs[j*2+1].x = r * cos(TWO_PI / 64 * j);
                vs[j*2+1].y = y;
                vs[j*2+1].z = r * sin(TWO_PI / 64 * j);
                
            }
            
            vs[64*2].x = r * cos(0);
            vs[64*2].y = y;
            vs[64*2].z = r * sin(0);
            
            vs[64*2+1].x = r * cos(0);
            vs[64*2+1].y = y;
            vs[64*2+1].z = r * sin(0);
            
            vbo[i].setVertexData(vs.data(), vs.size(), GL_DYNAMIC_DRAW);
        }
        
    };
    
    void draw(){
        
        
        
        for (int i = 0; i < 8; i++) {
            ofNoFill();
            ofSetColor(color.r, color.g, color.b, 32);
            vbo[i].draw(GL_TRIANGLE_STRIP, 0, vbo[i].getNumVertices());
            ofFill();
            ofSetColor(color.r, color.g, color.b, 64);
            vbo[i].draw(GL_TRIANGLE_STRIP, 0, vbo[i].getNumVertices());
        }
        ofFill();
    };
    
    void bang(int index, float velocity) {
        
        power[index] += velocity;
    
    };
    
protected:
    float y;
    float power[8];
    ofVbo vbo[8];
    ofColor color = ofColor(128, 129, 255);
    
    vector<ofVec3f> vs;
};

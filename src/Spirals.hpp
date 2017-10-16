#include "ofMain.h"

class Datum {
public:
    Datum(){};
    Datum(float velocity){
        length = (int) floor(500 * velocity);
        head = 5000 - length;
        
    };
    void update(){
        
        head -= 10;
        
    };
    
    int head;
    int length;
    
};

class Spiral {
public:
    Spiral(){};
    Spiral(int index){
        
        float r, x, y, z;
        float t;
        float theta = 0;
        
        for (int i = 0; i < vertNum; i++) {
            
            r = exp(0.17 * theta) * 10;
            x = r * sin(theta);
            z = r * cos(theta);
            y = i * 0.18;
            
            trail.push_back( ofVec3f(x, y, z) );
            
            theta += 0.006;
            
        }
        
        mesh.setVertexData(trail.data(), trail.size(), GL_STATIC_DRAW);
        
    };
    void update() {
        
        vector<Datum>::iterator it;
        for (it = data.begin(); it < data.end(); it++) {
            
            it->update();
            if (it->head < 0) data.erase(it);
        }
    }
    
    void draw(){
        
        for (int i = 0; i < data.size(); i++) {
            
            mesh.draw(GL_LINE_STRIP, data[i].head, data[i].length);
            mesh.draw(GL_POINTS, data[i].head, 1);
            
        }
        
    };
    void bang(float velocity) {
        data.push_back(Datum(velocity));
    };
private:
    ofVbo mesh;
    
    int vertNum = 5000;
    vector<ofVec3f> trail;
    vector<Datum> data;
};


class Spirals {
public:
    
    Spirals(){
        
        for (int i = 0; i < 8; i++) {
            
            Spiral s = Spiral(i);
            sps.push_back(s);
            
        }
    
    };
    
    void update(){
    
        for (int i = 0; i < 8; i++) {
            
            sps[i].update();
        
        }
        
    };
    void draw(){
        
        ofSetColor(color.r, color.g, color.b, 128);
        
        glEnable(GL_POINT_SMOOTH);
        glPointSize(5.0);
        
        for (int i = 0; i < 8; i++) {
            
            ofPushMatrix();
            ofRotateY(360.0 / 8.0 * i);
            sps[i].draw();
            ofPopMatrix();
        }
        
    };

    void bang(int index, float velocity) {
        
        sps[index].bang(velocity);
        
    };
    
private:
  
    vector<Spiral> sps;
    ofColor color = ofColor(200, 189, 255);
    
};

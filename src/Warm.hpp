#include "ofMain.h"

class Bagian : public ofNode {
public:
    Bagian(float size) {
        
        createOcta(ofVec3f(0,0,0), size * 0.4, 0);
        
        createOcta(ofVec3f(size * 0.6, 0, 0), size * 0.1, 0);
        createOcta(ofVec3f(- size * 0.6, 0, 0), size * 0.1, 0);
        createOcta(ofVec3f(0, size * 0.6, 0), size * 0.1, 0);
        createOcta(ofVec3f(0, - size * 0.6, 0), size * 0.1, 0);
        
        float s = 20 * abs(sin(size));
        
        for (int i = 0; i < 10; i++) {
            
            createOcta(ofVec3f(s * (i * 0.5), 10 * sin(i*0.1), 10 - i), s * i * 0.1, i*10);
            createOcta(ofVec3f(- s * (i * 0.5), 10 * sin(i*0.1), 10 - i), s * i * 0.1, i*10);
            
        }
        
        
    };
    
    void update() {
        alpha -= 0.9;
        if (alpha > 100.0) alpha = 100.0;
        if (alpha < 10.0) alpha = 10.0;
    }
    
    void customDraw(const ofBaseRenderer * renderer) const {
        
        ofSetColor(color.r, color.g, color.b, 24);
        mesh.draw(OF_MESH_WIREFRAME);
        
        ofSetColor(color.r, color.g, color.b, alpha);
        mesh.draw(OF_MESH_FILL);
    };
    
    void createOcta(ofVec3f pos, float size, float deg) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                ofVec3f v = ofVec3f(ov[ oi[i][j] ][0], ov[ oi[i][j] ][1], ov[ oi[i][j] ][2]);
                v.rotate(deg, ofVec3f(1,0,0));
                v *= size;
                v += pos;
                mesh.addVertex(v);
            }
        }
    };
    
    void bang(float velocity) {
        alpha += 90 * velocity;
    };
    
    
private:
    ofVboMesh mesh;
    float ov[6][3] = {
        {1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}
    };
    unsigned int oi[8][3] = {
        {0, 2, 4}, {0, 4, 3}, {0, 3, 5}, {0, 5, 2},
        {1, 2, 5}, {1, 5, 3}, {1, 3, 4}, {1, 4, 2}
    };
    ofColor color = ofColor(128, 168, 150);
    float alpha = 20; // 10 - 100
    
};


class Warm {
public:
    Warm(){
        
        pos = ofVec3f(ofRandom(-1000, 1000), ofRandom(800), ofRandom(-1000, 1000));
        
        maxSpeed = 80;
        maxForce = 1.0;
        
        for (int i = 0; i < length; i++) {
            Bagian b(50 - i * 0.3);
            b.setPosition(pos);
            bs.push_back(b);
        }
        
        trails.assign(length*space, pos);
        
    };
    void seek(ofVec3f * target){
        
        ofVec3f desired = *target - pos;
        desired = desired.normalize() * maxSpeed;
        
        ofVec3f steer = desired - vel;
        
        applyForce(&steer);
        
    };
    
    void applyForce(ofVec3f * force) {
        
        force->limit(maxForce);
        acce += *force;
        
    };
    
    void update(){
        
        if (ofGetFrameNum() % 120 == 0) {
            ofVec3f target = ofVec3f(ofRandom(-1000, 1000), ofRandom(800), ofRandom(-1000, 1000));
            seek(&target);
        }
        
        vel += acce;
        vel.limit(maxSpeed);
        
        pos += vel;
        
        trails.erase(trails.begin());
        trails.push_back(pos);
        
        for (int i = 0; i < length; i++) {
            bs[i].update();
            if (i == 0) {
                ofVec3f la = -1 * (bs[i+1].getPosition() - pos);
                bs[i].lookAt( la, ofVec3f(0,1,0) );
                bs[i].setPosition( pos );
            } else {
                bs[i].lookAt( bs[i-1].getPosition(), ofVec3f(0,1,0) );
                bs[i].setPosition( trails[ trails.size() - i*space ] );
            }
        }
        
        acce *= 0.0;
        
        
    };
    void draw(){
        
        vector<Bagian>::iterator it;
        for (it = bs.begin(); it != bs.end(); it++) {
            it->draw();
        }
        
    };
    void bang(int index, float velocity) {
        
        for (int i = 0; i < length; i++) {
            
            if (i % 8 == index) bs[i].bang(velocity);
            
        }
        
    }
    
private:
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f acce;
    
    float maxSpeed;
    float maxForce;
    
    int length = 24;
    int space = 12;
    vector<Bagian> bs;
    vector<ofVec3f> trails;
    
    
};

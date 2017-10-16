#include "ofMain.h"
#include "Lily.hpp"

class LilySystem : public ofNode {
public:
    LilySystem(){
        
        ofNode * parent = this;
        setPosition(0, -60, 0);
        
        for (int i = 0; i < num; i++) {
            
            Lily l;
            
            ofVec3f p = ofVec3f(cos(i * TWO_PI / 2.6) * 20, 40 * i, sin(i * TWO_PI / 2.6) * 20);
            l.setPosition(p.x, p.y, p.z);
            
            ofVec3f la = p + ofVec3f(cos(i * TWO_PI / 2.6) * 22, -30 + (-3 + i * 1.0), sin(i * TWO_PI / 2.6) * 22);
            l.lookAt(la);
    
//            l.setParent(*parent);
            lilies.push_back(l);
            
            createStem(&p);
        }
        
        
        
    };
    
    void update(){
        
        for (int i = 0; i < 8; i++) {
            
            lilies[i].update();
        
        }
    
    };
    void customDraw(const ofBaseRenderer * renderer) const {
        
        ofSetColor(128, 128, 233, 150);
        for (int i = 0; i < 8; i++) {
            stems[i].draw(GL_LINES, 0, stems[i].getNumVertices());
        }
        
        
        for (int i = 0; i < 8; i++) {
            lilies[i].draw();
        }
        
    };
    
    void bang(int index, float velocity){
        lilies[index].bang(velocity);
    };
    
    void createStem(ofVec3f * to) {
        
        ofVec3f start = getPosition();
        float dist = start.distance(*to);

        
        ofVbo stem;
        vector<ofVec3f> vs;
        
        float r = 2.0;
        float step = 1.0;
        
        for (int i = 0; i < 3; i++) {
            
            float rhamda = TWO_PI / 3.0 * i;
            
            for (float j = 0; j < dist; j += step) {
                
                ofVec3f cur = start.getInterpolated(*to, j / dist);
                ofVec3f next = start.getInterpolated(*to, (j+step) / dist);
                
                vs.push_back(ofVec3f(
                                     r * sin(rhamda + PI/3 * j * 0.1) + cur.x,
                                     cur.y,
                                     r * cos(rhamda + PI/3 * j * 0.1) + cur.z
                                     ));
                
                vs.push_back(ofVec3f(
                                     r * sin(rhamda + PI/3 * (j+step) * 0.1) + next.x,
                                     next.y,
                                     r * cos(rhamda + PI/3 * (j+step) * 0.1) + next.z
                                     ));
            
            }
            
        }
        
        stem.setVertexData(vs.data(), vs.size(), GL_STATIC_DRAW);
        stems.push_back(stem);
        
    };
    
    int num = 8;
    vector<Lily> lilies;
    vector<ofVbo> stems;
};


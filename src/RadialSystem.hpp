#include "ofMain.h"
#include "RadialObj.hpp"

class RadialSystem {
public:
    
    RadialSystem(){};
    void update(){
        
        vector<RadialObj>::iterator it;
        for (it = objs.begin(); it < objs.end(); it++) {
            
            if (it->life < 0.0) {
                objs.erase(it);
            } else {
                it->update();
            }
        
        }
    
    };
    void draw(){
        
        vector<RadialObj>::iterator it;
        for (it = objs.begin(); it < objs.end(); it++) {
            
            it->draw();
            
        }

    };
    
    void bang(int index, float velocity) {
        
        RadialObj obj(index, velocity);
        objs.push_back(obj);
        
    };
    
private:
    
    vector<RadialObj> objs;
    
};

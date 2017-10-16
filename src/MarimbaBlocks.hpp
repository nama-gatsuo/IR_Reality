#include "ofApp.h"

class MarimbaBlocks {
public:
    MarimbaBlocks(){
        float x, y, z;
        
        ofMesh box = ofMesh::box(size, size, size);
        vector<ofVec3f> v = box.getVertices();
        vector<ofIndexType> is = box.getIndices();
        
        meshes.assign(4 * 8, ofVboMesh());
        
        for (int i = 0; i < 4; i++) {
            
            x = rad * cos(TWO_PI/4 * i);
            z = rad * sin(TWO_PI/4 * i);
            
            for (int j = 0; j < 8; j++) {
                
                y = (size + 15.0) * j;
                
                for (int k = 0; k < v.size(); k++) {
                    
                    meshes[i * 8 + j].addVertex(ofVec3f(v[k].x + x, v[k].y + y, v[k].z + z));
                    
                }
                
                for (int k = 0; k < is.size(); k++) {
                
                    meshes[i * 8 + j].addIndex(is[k]);
                    
                }
                
            }
        
        }
        
        
    };
    void update(){
        
        for (int i = 0; i < 8; i++) {
            
            power[i] -= 0.01;
            if (power[i] < 0.0) power[i] = 0.0;
            if (power[i] > 1.0) power[i] = 1.0;
            
        }
        
    };
    void draw(){
        
        for (int i = 0; i < 32; i++) {
            
            ofSetColor(color.r, color.g, color.b, 48);
            meshes[i].draw(OF_MESH_WIREFRAME);
            
            float p = power[i % 8];
            
            ofSetColor(color.r, color.g, color.b, 128 * p);
            meshes[i].draw(OF_MESH_FILL);
        
        }
        
    
    };
    void bang(int index, float velocity){
        power[index] += velocity;
    };
    
private:
    float rad = 900;
    float size = 60;
    
    float power[8];
    vector<ofVboMesh> meshes;
    ofColor color = ofColor(133, 100, 218);
    
};

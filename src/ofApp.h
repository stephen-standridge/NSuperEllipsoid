#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "MyEquations.h"

class ofApp : public ofBaseApp{

public:
    static const int MAX_SCENES = 3;
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void setPow1(float & newPow1);
    void setPow2(float & newPow2);
    void setRadii(ofVec4f & newRadii);
    void setDivision1(float & newDivision1);
    void setDivision2(float & newDivision2);
    void setRoot(float & newRoot);
    
    int currentScene;
    float currentW = 0.0;
    
    ofxPanel gui;
    ofxToggle drawWireFrame;
    ofxToggle drawPoints;
    ofxToggle drawNoramls;
    ofxToggle lightingOn;
    
    ofParameter<float>      power1;
    ofParameter<float>      power2;
    ofParameter<ofVec4f>    radii;
    ofParameter<float>      root;
    ofParameter<float>      division1;
    ofParameter<float>      division2;
    
    ofEasyCam cam;
    ofLight light;
    Torus torus;
    SuperEllipsoid superEllipsoid;
    HyperEllipsoid hyperEllipsoid;
    ofImage flower;

};

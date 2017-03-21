#pragma once

#include "ofxMathMesh.h"
#include "ofxAnimatableFloat.h"
#include "MyEquations.h"
#include "ofxParametricHyperSurface.hpp"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class HyperEllipsoid:public ofxParametricHyperSurface{
public:
    ofVec4f r = ofVec4f(1,1,1,1);
    float pow1 = 1.0;
    float pow2 = 1.0;
    float root = 2.0;
    float division1 = 4.0;
    float division2 = 4.0;
    
    HyperEllipsoid():ofxParametricHyperSurface(){
        currentW.setCurve(EASE_OUT);
        currentW.setRepeatType(LOOP_BACK_AND_FORTH);
        currentW.setDuration(4.0);
        currentW.animateFromTo(-M_PI, M_PI);
        ofAddListener(ofEvents().update, this, &HyperEllipsoid::update);
    }
    ofPoint valueForPoint(float u, float v, float w){
        float radius1 = getRadius(r.x, r.z, u, root, pow1, pow2, division1, division2);
        float radius2 = getRadius(r.x, r.y, v, root, pow1, pow2, division1, division2);
        float radius3 = getRadius(r.y, r.w, w, root, pow1, pow2, division1, division2);

        float x = radius3 * cos(w) * radius1 * cos(u) * radius2 * cos(v);
        float y = radius3 * cos(w) * radius1 * cos(u) * radius2 * sin(v);
        float z = radius3 * cos(w) * radius1 * sin(u);
        return ofPoint(x,y,z);
    }
    float getRadius(float r1, float r2, float angle, float n1, float n2, float n3, float m1, float m2){
        //might have to include w's radius here?
        float rad1 = pow(abs(cos((m1 * angle)/4) / r1), n2);
        float rad2 = pow(abs(sin((m2 * angle)/4) / r2), n3);
        return pow(rad1 + rad2, -1/n1);
    }
    void update(ofEventArgs &args){
        float dt = 1/ofGetFrameRate();
        currentW.update(dt);
    }

    ofFloatColor colorForPoint(float u,float v, float w, ofPoint value){
        return ofFloatColor::green;
    }
public:
    ofxAnimatableFloat currentW;
};


class SuperEllipsoid:public ofxParametricSurface{
public:
    ofVec3f r = ofVec3f(1,1,1);
    float pow1 = 1.0;
    float pow2 = 1.0;
    float root = 2.0;
    float division1 = 4.0;
    float division2 = 4.0;

    SuperEllipsoid():ofxParametricSurface(){
        rotU.setCurve(EASE_OUT);
        rotU.setRepeatType(LOOP_BACK_AND_FORTH);
        rotU.setDuration(4.0);
        rotU.animateFromTo(0.0, M_PI);
        ofAddListener(ofEvents().update, this, &SuperEllipsoid::update);
    }
    ofPoint valueForPoint(float u,float v){
        
        float radius1 = getRadius(r.x, r.z, u, root, pow1, pow2, division1, division2);
        float radius2 = getRadius(r.x, r.y, v, root, pow1, pow2, division1, division2);
        
        float x = radius1 * cos(u) * radius2 * cos(v);
        float y = radius1 * cos(u) * radius2 * sin(v);
        float z = radius1 * sin(u);

        return ofPoint(x,y,z);
    }
    float getRadius(float r1, float r2, float angle, float n1, float n2, float n3, float m1, float m2){
        float rad1 = pow(abs(cos((m1 * angle)/4) / r1), n2);
        float rad2 = pow(abs(sin((m2 * angle)/4) / r2), n3);
        return pow(rad1 + rad2, -1/n1);
    }
    void update(ofEventArgs &args){
        float dt = 1/ofGetFrameRate();
        rotU.update(dt);
    }
public:
    ofxAnimatableFloat rotU;
};


class Torus:public ofxParametricSurface{
public:
    Torus():ofxParametricSurface(){
        minU.setCurve(EASE_OUT);
        minU.setRepeatType(LOOP_BACK_AND_FORTH);
        minU.setDuration(4.0);
        minU.animateFromTo(2*M_PI,0);
        
        minV.setCurve(LINEAR);
        minV.setRepeatType(LOOP_BACK_AND_FORTH);
        minV.setDuration(4.0);
        minV.animateFromTo(2*M_PI,0);
        ofAddListener(ofEvents().update, this, &Torus::update);
    }
    ofPoint valueForPoint(float u,float v){
        float c = 2;
        float a = 1;
        float x = (c+ a* cos(v)) * cos(u);
        float y = a* sin(v);
        float z = (c+ a*cos(v)) *sin(u);
        return ofPoint(x,y,z);
    }
    
    ofVec2f texCoordForPoint(float u,float v,ofPoint value){
        float s = u/(2*M_PI);
        float t = v/(2*M_PI);
        return ofVec2f(s,t);
    }
    
    ofFloatColor backColorForPoint(float u,float v,ofPoint value){
        if (u <= M_PI/2) {
            return ofFloatColor::green;
        }else if(u <= M_PI ){
            return ofFloatColor::orange;
        }else if (u <= 3*M_PI/2){
            return ofFloatColor::pink;
        }else{
            return ofFloatColor::violet;
        }
    }
    
    void update(ofEventArgs &args){
        float dt = 1/ofGetFrameRate();
        minU.update(dt);
        minV.update(dt);
        setUMin(minU);
        setVMin(minV);
    }
    
public:
    ofxAnimatableFloat minU;
    ofxAnimatableFloat minV;
};








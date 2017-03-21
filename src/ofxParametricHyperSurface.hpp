#ifndef ofxParametricHyperSurface_hpp
#define ofxParametricHyperSurface_hpp

#pragma once

#include "ofxMathHyperSurface.hpp"

// create meshs of the form r = r(u,v)
class ofxParametricHyperSurface:public ofxMathHyperSurface{
public:
    virtual ~ofxParametricHyperSurface(){}
    ofxParametricHyperSurface(){isSetup = false;flatColors = false;}
    
    // override these functions to configure your mesh
    // valueForPoint is mandatory, the rest are optional
    // valueForPoint should return a 3dpoint for a given u,v coordinate
    // override backColor and/or backTexCoord if you are using the 2 sided draw function;
    virtual ofPoint valueForPoint(float u,float v, float w) = 0;
    virtual ofFloatColor colorForPoint(float u, float v, float w, ofPoint value){return ofFloatColor::white;}
    virtual ofVec2f texCoordForPoint(float u, float v, float w, ofPoint value){return ofVec2f::zero();}
    virtual ofFloatColor backColorForPoint(float u, float v, float w, ofPoint value){return ofFloatColor::white;}
    virtual ofVec2f backTexCoordForPoint(float u, float v, float w, ofPoint value){return ofVec2f::zero();}
    
    // retrives normal at point see http://mathworld.wolfram.com/NormalVector.html
    // really no need to override this
    virtual ofVec3f normalForPoint(float u,float v, float w, ofPoint value);
    
    void setup(float uMin, float uMax,
               float vMin, float vMax,
               float wMin, float wMax,
               float uStep, float vStep, float wStep);
    
    void reload();
    
    void setUBounds(float uMin,float uMax);
    void setVBounds(float vMin,float vMax);
    void setWBounds(float wMin,float wMax);
    
    void setUMin(float uMin);
    void setUMax(float uMax);
    void setVMin(float vMin);
    void setVMax(float vMax);
    void setWMin(float wMin);
    void setWMax(float wMax);
    
    float getUMin()const{return uMin;}
    float getUMax()const{return uMax;}
    float getVMin()const{return vMin;}
    float getVMax()const{return vMax;}
    float getWMin()const{return wMin;}
    float getWMax()const{return wMax;}
    float getAbsUMin()const{return absUMin;}
    float getAbsVMin()const{return absVMin;}
    float getAbsWMin()const{return absWMin;}
    float getAbsUMax()const{return absUMax;}
    float getAbsVMax()const{return absVMax;}
    float getAbsWMax()const{return absWMax;}
    
    float getUStep()const{return uStep;}
    float getVStep()const{return vStep;}
    float getWStep()const{return wStep;}

    
    
private:
    bool isSetup;
    float absUMin;
    float absUMax;
    float absVMin;
    float absVMax;
    float absWMin;
    float absWMax;
    float uMin;
    float uMax;
    float vMin;
    float vMax;
    float wMin;
    float wMax;
    float uStep;
    float vStep;
    float wStep;
    vector<float> uDomainPoints;
    vector<float> vDomainPoints;
    vector<float> wDomainPoints;
    
private:
    struct ParametricPosition{
        ParametricPosition(const float &u,const float &v, const float &w, const ofPoint &value){
            this->u = u;
            this->v = v;
            this->w = w;
            this->value = value;
        }
        float u;
        float v;
        float w;
        ofPoint value;
    };
    void addQuad(int which, const ParametricPosition &one,const ParametricPosition &two,const ParametricPosition &three,const ParametricPosition &four);
    void loadDomainPoints();
    void setUStep(float step_);
    void setVStep(float step_);
    void setWStep(float step_);
};

#endif /* ofxParametricHyperSurface_hpp */

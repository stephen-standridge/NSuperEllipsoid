#include "ofxParametricHyperSurface.hpp"

void ofxParametricHyperSurface::setUMin(float uMin_){
    if (uMin_ >= absUMin) {
        uMin = uMin_;
    }else{
        uMin = absUMin;
        ofLogWarning("ofxParametricHyperSurface") << "Cannot set uMin smaller than setup uMin";
    }
}

void ofxParametricHyperSurface::setUMax(float uMax_){
    if (uMax_ <= absUMax) {
        uMax = uMax_;
    }else{
        uMax = absUMax;
        ofLogWarning("ofxParametricHyperSurface") << "Cannot set uMax bigger than setup uMax";
    }
}

void ofxParametricHyperSurface::setVMin(float vMin_){
    if (vMin_ >= absVMin) {
        vMin = vMin_;
    }else{
        vMin = absVMin;
        ofLogWarning("ofxParametricHyperSurface") << "Cannot set vMin smaller than setup vMin";
    }
}

void ofxParametricHyperSurface::setVMax(float vMax_){
    if (vMax_ <= absVMax) {
        vMax = vMax_;
    }else{
        vMax = absVMax;
        ofLogWarning("ofxParametricHyperSurface") << "Cannot set vMax bigger than setup vMax";
        
    }
}

void ofxParametricHyperSurface::setWMin(float wMin_){
    if (wMin_ >= absWMin) {
        wMin = wMin_;
    }else{
        wMin = absWMin;
        ofLogWarning("ofxParametricHyperSurface") << "Cannot set wMin smaller than setup vMin";
    }
}

void ofxParametricHyperSurface::setWMax(float wMax_){
    if (wMax_ <= absWMax) {
        wMax = wMax_;
    }else{
        wMax = absWMax;
        ofLogWarning("ofxParametricHyperSurface") << "Cannot set vMax bigger than setup vMax";
        
    }
}

void ofxParametricHyperSurface::setUStep(float step_){
    float range = absUMax - absUMin;
    if (step_ > range) {
        ofLogWarning("ofxParametricHyperSurface") << "cannot set U step greater than range. STEP:" + ofToString(step_) + " RANGE:" + ofToString(range);
        uStep = range;
        return;
    }
    int res = round(range/step_);
    uStep = range/(float)res;
}

void ofxParametricHyperSurface::setVStep(float step_){
    float range = absVMax - absVMin;
    if (step_ > range) {
        ofLogWarning("ofxParametricHyperSurface") << "cannot set V step greater than range. STEP:" + ofToString(step_) + " RANGE:" + ofToString(range);
        vStep = range;
        return;
    }
    int res = round(range/step_);
    vStep = range/(float)res;
}

void ofxParametricHyperSurface::setWStep(float step_){
    float range = absWMax - absWMin;
    if (step_ > range) {
        ofLogWarning("ofxParametricHyperSurface") << "cannot set W step greater than range. STEP:" + ofToString(step_) + " RANGE:" + ofToString(range);
        wStep = range;
        return;
    }
    int res = round(range/step_);
    wStep = range/(float)res;
}

void ofxParametricHyperSurface::setUBounds(float uMin_,float uMax_){
    setUMin(uMin_);
    setUMax(uMax_);
}
void ofxParametricHyperSurface::setVBounds(float vMin_,float vMax_){
    setVMin(vMin_);
    setVMax(vMax_);
}
void ofxParametricHyperSurface::setWBounds(float wMin_,float wMax_){
    setWMin(wMin_);
    setWMax(wMax_);
}

void ofxParametricHyperSurface::loadDomainPoints(){
    float epsilon = uStep/100.0;
    for (float u = absUMin; u <= absUMax + epsilon; u+=uStep) {
        uDomainPoints.push_back(u);
    }
    epsilon = vStep/100.0;
    for (float v = absVMin; v <= absVMax + epsilon; v+=vStep) {
        vDomainPoints.push_back(v);
    }
    epsilon = wStep/100.0;
    for (float w = absWMin; w <= absWMax + epsilon; w+=wStep) {
        wDomainPoints.push_back(w);
    }
}

void ofxParametricHyperSurface::setup(float uMin_, float uMax_, float vMin_, float vMax_, float wMin_, float wMax_, float uStep_ ,float vStep_, float wStep_){
    if (uStep_ <= 0 || vStep_ <= 0 || wStep_ <= 0 ) {
        ofLogWarning("ofxParametricHyperSurface") << "step must be greater than zero";
        return;
    }
    isSetup = true;
    absUMin = uMin_;
    absUMax = uMax_;
    absVMin = vMin_;
    absVMax = vMax_;
    absWMin = wMin_;
    absWMax = wMax_;
    
    setUStep(uStep_);
    setVStep(vStep_);
    setWStep(wStep_);
    loadDomainPoints();
    setUBounds(uMin_, uMax_);
    setVBounds(vMin_, vMax_);
    setWBounds(wMin_, wMax_);
    reload();
}

ofVec3f ofxParametricHyperSurface::normalForPoint(float u, float v, float w, ofPoint value){
    // derivative u to the right
    ofVec3f duRight;
    float delta = uStep;
    ofVec3f valuePlus = valueForPoint(u+delta, v, w);
    duRight.x = (valuePlus.x - value.x)/delta;
    duRight.y = (valuePlus.y - value.y)/delta;
    duRight.z = (valuePlus.z - value.z)/delta;
    
    //    // derivative u to the left
    //    ofVec3f duLeft;
    //    ofVec3f valueMinus = valueForPoint(u-delta, v);
    //    duLeft.x = (valueMinus.x - value.x)/delta;
    //    duLeft.y = (valueMinus.y - value.y)/delta;
    //    duLeft.z = (valueMinus.z - value.z)/delta;
    //
    //    ofVec3f du = (-duLeft + duRight);
    
    // derivative v to the right
    ofVec3f dvRight;
    delta = vStep;
    valuePlus = valueForPoint(u, v+delta, w);
    dvRight.x = (valuePlus.x - value.x)/delta;
    dvRight.y = (valuePlus.y - value.y)/delta;
    dvRight.z = (valuePlus.z - value.z)/delta;
    
    //    // deravative v to the left
    //    ofVec3f dvLeft;
    //    valueMinus = valueForPoint(u, v-delta);
    //    dvLeft.x = (valueMinus.x - value.x)/delta;
    //    dvLeft.y = (valueMinus.y - value.y)/delta;
    //    dvLeft.z = (valueMinus.z - value.z)/delta;
    //
    //    ofVec3f dv = (dvRight + -dvLeft);
    
    ofVec3f dwRight;
    delta = wStep;
    valuePlus = valueForPoint(u, v, w+delta);
    dvRight.x = (valuePlus.x - value.x)/delta;
    dvRight.y = (valuePlus.y - value.y)/delta;
    dvRight.z = (valuePlus.z - value.z)/delta;
    
    //    // deravative w to the left
    //    ofVec3f dvLeft;
    //    valueMinus = valueForPoint(u, v-delta);
    //    dvLeft.x = (valueMinus.x - value.x)/delta;
    //    dvLeft.y = (valueMinus.y - value.y)/delta;
    //    dvLeft.z = (valueMinus.z - value.z)/delta;
    //
    //    ofVec3f dv = (dvRight + -dvLeft);
    
    ofVec3f normal = duRight.cross(dvRight).cross(dwRight).normalize();
    return -normal;
}

void ofxParametricHyperSurface::reload(){
    if (!isSetup) {
        ofLogError("ofxParametricHyperSurface") << "cannot reload if the surface is not setup";
        return;
    }
    clear();
    int uMinDomainPoint = round(ofMap(uMin, absUMin, absUMax, 0, uDomainPoints.size()-1));
    int uMaxDomainPoint = round(ofMap(uMax, absUMin, absUMax, 0, uDomainPoints.size()-1));
    int vMinDomainPoint = round(ofMap(vMin, absVMin, absVMax, 0, vDomainPoints.size()-1));
    int vMaxDomianPoint = round(ofMap(vMax, absVMin, absVMax, 0, vDomainPoints.size()-1));
    int wMinDomainPoint = round(ofMap(wMin, absWMin, absWMax, 0, wDomainPoints.size()-1));
    int wMaxDomianPoint = round(ofMap(wMax, absWMin, absWMax, 0, wDomainPoints.size()-1));
    
    for (int w = wMinDomainPoint; w < wMaxDomianPoint; w++) {
        for (int u = uMinDomainPoint; u < uMaxDomainPoint; u++) {
            for (int v = vMinDomainPoint; v < vMaxDomianPoint; v++) {
                ofPoint value1 = valueForPoint(uDomainPoints[u], vDomainPoints[v], wDomainPoints[w]);
                ofPoint value2 = valueForPoint(uDomainPoints[u], vDomainPoints[v+1], wDomainPoints[w]);
                ofPoint value3 = valueForPoint(uDomainPoints[u+1], vDomainPoints[v+1], wDomainPoints[w]);
                ofPoint value4 = valueForPoint(uDomainPoints[u+1], vDomainPoints[v], wDomainPoints[w]);
                
                ParametricPosition one(uDomainPoints[u],vDomainPoints[v], wDomainPoints[w], value1);
                ParametricPosition two(uDomainPoints[u],vDomainPoints[v+1],wDomainPoints[w], value2);
                ParametricPosition three(uDomainPoints[u+1],vDomainPoints[v+1], wDomainPoints[w], value3);
                ParametricPosition four(uDomainPoints[u+1],vDomainPoints[v], wDomainPoints[w], value4);
                addQuad(w, one, two, three, four);
            }
        }
    }
    
}

void ofxParametricHyperSurface::addQuad(int which, const ofxParametricHyperSurface::ParametricPosition &one, const ofxParametricHyperSurface::ParametricPosition &two, const ofxParametricHyperSurface::ParametricPosition &three, const ofxParametricHyperSurface::ParametricPosition &four){
    if(wVertices.size() == which){
        vector<ofVec3f>         vertices;
        vector<ofVec3f>         ffNormals;
        vector<ofFloatColor>    ffColors;
        vector<ofVec2f>         ffTexCoords;
        vector<ofVec3f>         bfNormals;
        vector<ofFloatColor>    bfColors;
        vector<ofVec2f>         bfTexCoords;
        
        wVertices.push_back(vertices);
        frontFaceNormals.push_back(ffNormals);
        frontFaceColors.push_back(ffColors);
        frontFaceTexCoords.push_back(ffTexCoords);
        backFaceNormals.push_back(bfNormals);
        backFaceColors.push_back(bfColors);
        backFaceTexCoords.push_back(bfTexCoords);
    }
    
    wVertices[which].push_back(one.value);
    wVertices[which].push_back(two.value);
    wVertices[which].push_back(four.value);
    wVertices[which].push_back(two.value);
    wVertices[which].push_back(three.value);
    wVertices[which].push_back(four.value);
    
    // load normals
    ofVec3f normal1 = normalForPoint(one.u, one.v, one.w, one.value);
    ofVec3f normal2 = normalForPoint(two.u, two.v, two.w, two.value);
    ofVec3f normal3 = normalForPoint(three.u, three.v, three.w, three.value);
    ofVec3f normal4 = normalForPoint(four.u, four.v, four.w, four.value);
    
    frontFaceNormals[which].push_back(normal1);
    frontFaceNormals[which].push_back(normal2);
    frontFaceNormals[which].push_back(normal4);
    frontFaceNormals[which].push_back(normal2);
    frontFaceNormals[which].push_back(normal3);
    frontFaceNormals[which].push_back(normal4);
    
    backFaceNormals[which].push_back(-normal1);
    backFaceNormals[which].push_back(-normal2);
    backFaceNormals[which].push_back(-normal4);
    backFaceNormals[which].push_back(-normal2);
    backFaceNormals[which].push_back(-normal3);
    backFaceNormals[which].push_back(-normal4);
    
    // load colors
    ofFloatColor color1 = colorForPoint(one.u, one.v, one.w, one.value);
    ofFloatColor color2 = colorForPoint(two.u, two.v, two.w, two.value);
    ofFloatColor color3 = colorForPoint(three.u, three.v, three.w, three.value);
    ofFloatColor color4 = colorForPoint(four.u, four.v,  four.w, four.value);
    if (flatColors) {
        frontFaceColors[which].push_back(color1);
        frontFaceColors[which].push_back(color1);
        frontFaceColors[which].push_back(color1);
        frontFaceColors[which].push_back(color1);
        frontFaceColors[which].push_back(color1);
        frontFaceColors[which].push_back(color1);
    }else{
        frontFaceColors[which].push_back(color1);
        frontFaceColors[which].push_back(color2);
        frontFaceColors[which].push_back(color4);
        frontFaceColors[which].push_back(color2);
        frontFaceColors[which].push_back(color3);
        frontFaceColors[which].push_back(color4);
    }
    
    color1 = backColorForPoint(one.u, one.v, one.w, one.value);
    color2 = backColorForPoint(two.u, two.v, two.w, two.value);
    color3 = backColorForPoint(three.u, three.v, three.w, three.value);
    color4 = backColorForPoint(four.u, four.v, four.w, four.value);
    
    if (flatColors) {
        backFaceColors[which].push_back(color1);
        backFaceColors[which].push_back(color1);
        backFaceColors[which].push_back(color1);
        backFaceColors[which].push_back(color1);
        backFaceColors[which].push_back(color1);
        backFaceColors[which].push_back(color1);
    }else{
        backFaceColors[which].push_back(color1);
        backFaceColors[which].push_back(color2);
        backFaceColors[which].push_back(color4);
        backFaceColors[which].push_back(color2);
        backFaceColors[which].push_back(color3);
        backFaceColors[which].push_back(color4);
    }
    
    //load texCoords
    ofVec2f tex1 = texCoordForPoint(one.u, one.v, one.w, one.value);
    ofVec2f tex2 = texCoordForPoint(two.u, two.v, two.w, two.value);
    ofVec2f tex3 = texCoordForPoint(three.u, three.v, three.w, three.value);
    ofVec2f tex4 = texCoordForPoint(four.u, four.v, four.w, four.value);
    
    frontFaceTexCoords[which].push_back(tex1);
    frontFaceTexCoords[which].push_back(tex2);
    frontFaceTexCoords[which].push_back(tex4);
    frontFaceTexCoords[which].push_back(tex2);
    frontFaceTexCoords[which].push_back(tex3);
    frontFaceTexCoords[which].push_back(tex4);
    
    tex1 = backTexCoordForPoint(one.u, one.v, one.w, one.value);
    tex2 = backTexCoordForPoint(two.u, two.v, two.w, two.value);
    tex3 = backTexCoordForPoint(three.u, three.v, three.w, three.value);
    tex4 = backTexCoordForPoint(four.u, four.v, four.w, four.value);
    
    backFaceTexCoords[which].push_back(tex1);
    backFaceTexCoords[which].push_back(tex2);
    backFaceTexCoords[which].push_back(tex4);
    backFaceTexCoords[which].push_back(tex2);
    backFaceTexCoords[which].push_back(tex3);
    backFaceTexCoords[which].push_back(tex4);
}







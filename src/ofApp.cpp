#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setAutoDistance(false);
    cam.setNearClip(.001);
    cam.setTarget(ofVec3f::zero());
    cam.setPosition(0, 0, 10);
    ofDisableArbTex();
    ofSetSmoothLighting(true);
    #ifdef glPointSize
        glPointSize(3.0);
    #endif
    glLineWidth(1.0);
    
    power1.addListener(this, &ofApp::setPow1);
    power2.addListener(this, &ofApp::setPow2);
    radii.addListener(this, &ofApp::setRadii);
    division1.addListener(this, &ofApp::setDivision1);
    division2.addListener(this, &ofApp::setDivision2);
    root.addListener(this, &ofApp::setRoot);
    
    gui.setup();
    gui.add(drawWireFrame.setup("draw wireframe",true));
    gui.add(drawPoints.setup("draw points",false));
    gui.add(drawNoramls.setup("draw normals",false));
    gui.add(lightingOn.setup("Lighting On",false));
    
    gui.add(power1.set("shaping power 1", 1.0, 0.0, 3.0));
    gui.add(power2.set("shaping power 2", 1.0, 0.0, 3.0));
    gui.add(root.set("root", 2.0, 0.0, 10.0));
    gui.add(division1.set("division 1", 1.0, 0.0, 10.0));
    gui.add(division2.set("division 2", 1.0, 0.0, 10.0));
    gui.add(radii.set("radii", ofVec4f(1.0, 1.0, 1.0, 1.0), ofVec4f(0.1, 0.1, 0.1, 0.1), ofVec4f(10, 10, 10, 10)));

    
    currentScene = 0;
    
    light.setPosition(0, 3, 0);
    light.setScale(.01);
    light.setAttenuation(1.0,.2);
    
    
    torus.enableFlatColors();
    superEllipsoid.enableFlatColors();
    hyperEllipsoid.enableFlatColors();

    
    hyperEllipsoid.setup(-M_PI/2, M_PI/2, -M_PI, M_PI, -M_PI, M_PI, .3, .3, .3);
    superEllipsoid.setup(-M_PI/2, M_PI/2, -M_PI, M_PI, .1, .1);
    
    torus.setup(0, 2*M_PI, 0,2*M_PI, .1, .1);
    flower.load("flower.jpg");

}

void ofApp::setPow1(float & newPow1) {
    superEllipsoid.pow1 = newPow1;
    hyperEllipsoid.pow1 = newPow1;
}

void ofApp::setPow2(float & newPow2) {
    superEllipsoid.pow2 = newPow2;
    hyperEllipsoid.pow2 = newPow2;
}

void ofApp::setRadii(ofVec4f & newRadii) {
    superEllipsoid.r = ofVec3f(newRadii.x, newRadii.y, newRadii.z);
    hyperEllipsoid.r = newRadii;
}

void ofApp::setDivision1(float & newDivision1) {
    superEllipsoid.division1 = newDivision1;
    hyperEllipsoid.division1 = newDivision1;
}

void ofApp::setDivision2(float & newDivision2) {
    superEllipsoid.division2 = newDivision2;
    hyperEllipsoid.division2 = newDivision2;
}

void ofApp::setRoot(float & newRoot) {
    superEllipsoid.root = newRoot;
    hyperEllipsoid.root = newRoot;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (currentScene == 0) {
        hyperEllipsoid.reload();
    }
    if (currentScene == 1) {
        superEllipsoid.reload();
    }
    if (currentScene == 2) {
        torus.reload();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofEnableDepthTest();
    
    cam.begin();
    if (lightingOn) {
        ofEnableLighting();
        light.enable();
    }
    if(currentScene == 0){
        int wToDraw = ofMap(currentW, 0, hyperEllipsoid.getWMax(), 0, hyperEllipsoid.totalWLayers() - 1, true);
        if (drawNoramls) {
            ofSetColor(ofColor::turquoise);
            hyperEllipsoid.drawNormals(.2, wToDraw);
        }
        if (drawPoints) {
            hyperEllipsoid.drawPoints(true, wToDraw);
        }else{
            ofSetColor(255, 255, 255);
            flower.bind();
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1.0f, 1.0f);
            hyperEllipsoid.drawFrontFaces(false, true, wToDraw);
            flower.unbind();
            hyperEllipsoid.drawBackFaces(true, false, wToDraw);
            glDisable(GL_POLYGON_OFFSET_FILL);
            if (drawWireFrame) {
                ofSetColor(ofColor::black);
                glEnable(GL_LINE_STRIP);
                hyperEllipsoid.drawWireFrame(false, wToDraw);
                glDisable(GL_LINE_STRIP);
            }
        }
    }else if(currentScene == 1){
        if (drawNoramls) {
            ofSetColor(ofColor::turquoise);
            superEllipsoid.drawNormals(.2);
        }
        if (drawPoints) {
            superEllipsoid.drawPoints(true);
        }else{
            ofSetColor(255, 255, 255);
            flower.bind();
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1.0f, 1.0f);
            superEllipsoid.drawFrontFaces(false, true);
            flower.unbind();
            superEllipsoid.drawBackFaces(true, false);
            glDisable(GL_POLYGON_OFFSET_FILL);
            if (drawWireFrame) {
                ofSetColor(ofColor::black);
                glEnable(GL_LINE_STRIP);
                superEllipsoid.drawWireFrame(false);
                glDisable(GL_LINE_STRIP);
            }
        }
    } else if(currentScene == 2){
        if (drawNoramls) {
            ofSetColor(ofColor::turquoise);
            torus.drawNormals(.2);
        }
        if (drawPoints) {
            torus.drawPoints(true);
        }else{
            ofSetColor(255, 255, 255);
            flower.bind();
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1.0f, 1.0f);
            torus.drawFrontFaces(false, true);
            flower.unbind();
            torus.drawBackFaces(true, false);
            glDisable(GL_POLYGON_OFFSET_FILL);
            if (drawWireFrame) {
                ofSetColor(ofColor::black);
                glEnable(GL_LINE_STRIP);
                torus.drawWireFrame(false);
                glDisable(GL_LINE_STRIP);
            }
        }
    }
    
   if (lightingOn) {
        light.draw();
        light.disable();
        ofDisableLighting();
    }
    
    cam.end();
    
    ofDisableDepthTest();
    gui.draw();
    ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_RIGHT) {
        currentScene++;
        if (currentScene == MAX_SCENES) {
            currentScene = 0;
        }
    }else if(key == OF_KEY_LEFT){
        currentScene--;
        if (currentScene == -1) {
            currentScene = MAX_SCENES - 1;
        }
    } else if(key == OF_KEY_UP) {
        currentW += 0.05;
        if (currentW >= hyperEllipsoid.getWMax()) {
            currentW = 0;
        }
    } else if(key == OF_KEY_DOWN) {
        currentW-=0.05;
        if (currentW <= 0.0) {
            currentW = hyperEllipsoid.getWMax();
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}



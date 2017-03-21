#ifndef ofxMathHyperSurface_hpp
#define ofxMathHyperSurface_hpp

#pragma once
#include "ofMain.h"

// This class is an abstract base for ofx3dFunction and ofxParametricCurve
class ofxMathHyperSurface{
public:
    // 'colors' and 'texcoords' arguments specify if you want to use the colorForPoint and texCoordForPoint functions
    //  you defined. drawBackFaces will use functions 'backColorForPoint' and 'backTexCoordForPoint', if you pass 'true' to 'colors' and 'texCoords'
    void draw(bool colors,bool texCoords, int which=0);
    void drawFrontFaces(bool colors, bool texCoords, int which=0);
    void drawBackFaces(bool colors,bool texCoords, int which=0);
    void drawWireFrame(bool colors, int which=0);
    void drawPoints(bool colors, int which=0);
    void drawNormals(float length, int which=0) const;
    void drawFaceNormals(float length, int which=0) const;
    
    // flatColors will set the same color for each vertex in a quad;
    void enableFlatColors(){flatColors = true;}
    void disableFlatColors(){flatColors = false;}
    int totalWLayers(){return wVertices.size();}
    
    // returns a vbo which with vertices,frontNormals,frontColors,and frontTexCoords
    ofVbo getVbo(int which=0) const;
    
    // returns a vbo which with vertices,backNormals,backColors,and backTexCoords
    ofVbo getBackVbo(int which=0) const;
    
    // returns a mesh which with vertices,frontNormals,frontColors,and frontTexCoords
    ofMesh getMesh(int which=0) const;
    
    // returns a mesh which with vertices,backNormals,backColors,and backTexCoords
    ofMesh getBackMesh(int which=0) const;
    
private:
    ofVbo vbo;
    ofShader shader;
    
protected:
    vector<vector<ofFloatColor>>    backFaceColors;
    vector<vector<ofVec2f>>         backFaceTexCoords;
    vector<vector<ofFloatColor>>    frontFaceColors;
    vector<vector<ofVec2f>>         frontFaceTexCoords;
    vector<vector<ofVec3f>>         frontFaceNormals;
    vector<vector<ofVec3f>>         backFaceNormals;
    vector<ofVec3f>                 vertices;
    vector<vector<ofVec3f>>         wVertices;

    ofBufferObject                  prev;
    ofBufferObject                  next;
    
    int direction = 1.0;
    int currentW;
    bool flatColors;
    int getPrev(int which);
    int getNext(int which);
    void setWAttributes(int which);
    
protected:
    void clear();
    static float distFromPlane(const ofVec3f &point,const ofVec3f &planeNormal,const float &planeD);
    static bool getSegmentPlaneIntersection(const ofVec3f &a,const ofVec3f &b,ofVec3f &intersectionPoint,const ofVec3f &planeNormal,const float &planeD);
    static void addTriangleToMesh(ofMesh &mesh,const ofVec3f &one,const ofVec3f &two,const ofVec3f &three);
    static void addQuadToMesh(ofMesh &mesh,const ofVec3f &one,const ofVec3f &two,const ofVec3f &three,const ofVec3f &four);
    static ofVec3f getCenter(const ofMeshFace& face);
};

#endif /* ofxMathHyperSurface_hpp */

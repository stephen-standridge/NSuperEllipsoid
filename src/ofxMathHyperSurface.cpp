#include "ofxMathHyperSurface.hpp"

int ofxMathHyperSurface::getNext(int which){
    if(which == wVertices.size() -1){ return 0; }
    return which + 1;
}
int ofxMathHyperSurface::getPrev(int which){
    if(which == 0){ return wVertices.size() - 1; }
    return which - 1;
}

void ofxMathHyperSurface::setWAttributes(int which){
    if(currentW != which){
        prev.setData(wVertices[getPrev(which)], GL_DYNAMIC_DRAW);
        next.setData(wVertices[getNext(which)], GL_DYNAMIC_DRAW);
        currentW = which;
    }
    vbo.setAttributeBuffer(shader.getAttributeLocation("next"),
                           next,
                           wVertices[which].size(),
                           3);
    vbo.setAttributeBuffer(shader.getAttributeLocation("prev"),
                           prev,
                           wVertices[which].size(),
                           3);
}

void ofxMathHyperSurface::draw(bool colors, bool texCoords, int which){
    setWAttributes(which);
    vbo.setVertexData(wVertices[which].data(),
                      wVertices[which].size(),
                      GL_DYNAMIC_DRAW);
    
    
    if (colors) {
        vbo.enableColors();
        vbo.setColorData(frontFaceColors[which].data(),
                         frontFaceColors[which].size(),
                         GL_DYNAMIC_DRAW);
    }else{
        vbo.disableColors();
    }
    
    if (texCoords) {
        vbo.enableTexCoords();
        vbo.setTexCoordData(frontFaceTexCoords[which].data(),
                            frontFaceTexCoords[which].size(),
                            GL_DYNAMIC_DRAW);
    }else{
        vbo.disableTexCoords();
    }
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    vbo.setNormalData(frontFaceNormals[which].data(),
                      frontFaceNormals[which].size(),
                      GL_DYNAMIC_DRAW);
    vbo.draw(GL_TRIANGLES, 0, wVertices[which].size());
    glCullFace(GL_FRONT);
    vbo.setNormalData(backFaceNormals[which].data(),
                      backFaceNormals[which].size(),
                      GL_DYNAMIC_DRAW);
    vbo.draw(GL_TRIANGLES, 0, wVertices[which].size());
    glDisable(GL_CULL_FACE);
}

void ofxMathHyperSurface::drawFrontFaces(bool colors, bool texCoords, int which){
    vbo.setVertexData(wVertices[which].data(),
                      wVertices[which].size(),
                      GL_DYNAMIC_DRAW);
    
    setWAttributes(which);
    
    vbo.setNormalData(frontFaceNormals[which].data(),
                      frontFaceNormals[which].size(),
                      GL_DYNAMIC_DRAW);
    if (colors) {
        vbo.enableColors();
        vbo.setColorData(frontFaceColors[which].data(),
                         frontFaceColors[which].size(),
                         GL_DYNAMIC_DRAW);
    }else{
        vbo.disableColors();
    }
    if (texCoords) {
        vbo.enableTexCoords();
        vbo.setTexCoordData(frontFaceTexCoords[which].data(),
                            frontFaceTexCoords[which].size(),
                            GL_DYNAMIC_DRAW);
    }else{
        vbo.disableTexCoords();
    }
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    vbo.draw(GL_TRIANGLES, 0, wVertices[which].size());
    glDisable(GL_CULL_FACE);
}

void ofxMathHyperSurface::drawBackFaces(bool colors,bool texCoords, int which){
    vbo.setVertexData(wVertices[which].data(),
                      wVertices[which].size(),
                      GL_DYNAMIC_DRAW);
    
    setWAttributes(which);
    
    vbo.setNormalData(backFaceNormals[which].data(),
                      backFaceNormals[which].size(),
                      GL_DYNAMIC_DRAW);
    if (colors) {
        vbo.enableColors();
        vbo.setColorData(backFaceColors[which].data(),
                         backFaceColors[which].size(),
                         GL_DYNAMIC_DRAW);
    }else{
        vbo.disableColors();
    }
    if (texCoords) {
        vbo.enableTexCoords();
        vbo.setTexCoordData(backFaceTexCoords[which].data(),
                            backFaceTexCoords[which].size(),
                            GL_DYNAMIC_DRAW);
    }else{
        vbo.disableTexCoords();
    }
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    vbo.draw(GL_TRIANGLES, 0, wVertices[which].size());
    glDisable(GL_CULL_FACE);
}

void ofxMathHyperSurface::drawWireFrame(bool colors, int which){
#ifdef GL_LINE
    if (colors) {
        vbo.enableColors();
        vbo.setColorData(frontFaceColors[which].data(),
                         frontFaceColors[which].size(),
                         GL_DYNAMIC_DRAW);
    }else{
        vbo.disableColors();
    }
    vbo.setNormalData(frontFaceNormals[which].data(),
                      frontFaceNormals[which].size(),
                      GL_DYNAMIC_DRAW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    vbo.setVertexData(wVertices[which].data(),
                      wVertices[which].size(),
                      GL_DYNAMIC_DRAW);
    
    setWAttributes(which);
    
    vbo.draw(GL_TRIANGLES, 0, wVertices[which].size());
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
}

void ofxMathHyperSurface::drawPoints(bool colors, int which){
    vbo.setVertexData(wVertices[which].data(),
                      wVertices[which].size(),
                      GL_DYNAMIC_DRAW);
    
    setWAttributes(which);
    
    if (colors) {
        vbo.enableColors();
        vbo.setColorData(frontFaceColors[which].data(),
                         frontFaceColors[which].size(),
                         GL_DYNAMIC_DRAW);
    }else{
        vbo.disableColors();
    }
    vbo.setNormalData(frontFaceNormals[which].data(),
                      frontFaceNormals[which].size(),
                      GL_DYNAMIC_DRAW);
    vbo.draw(GL_POINTS, 0, wVertices[which].size());
}

void ofxMathHyperSurface::drawNormals(float length, int which) const{
    ofMesh normalsMesh;
    normalsMesh.setMode( OF_PRIMITIVE_LINES );
    normalsMesh.getVertices().resize( frontFaceNormals[which].size() * 2);
    const vector<ofVec3f>& normals = frontFaceNormals[which];
    ofVec3f normal;
    ofVec3f vert;
    
    for(int i = 0; i < (int)frontFaceNormals[which].size(); i++) {
        vert = wVertices[which][i];
        normal = ofVec3f(normals[i]).normalize();
        normalsMesh.setVertex( i*2, vert);
        normal *= length;
        normalsMesh.setVertex(i*2+1, normal+vert);
    }
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    normalsMesh.draw();
    
    normalsMesh.getVertices().resize( backFaceNormals[which].size() * 2);
    const vector<ofVec3f>& backNormals = backFaceNormals[which];
    for(int i = 0; i < (int)backNormals.size(); i++) {
        vert = wVertices[which][i];
        normal = ofVec3f(backNormals[which][i]).normalize();
        normalsMesh.setVertex( i*2, vert);
        normal *= length;
        normalsMesh.setVertex(i*2+1, normal+vert);
    }
    glCullFace(GL_BACK);
    normalsMesh.draw();
    glDisable(GL_CULL_FACE);
}

ofVec3f ofxMathHyperSurface::getCenter(const ofMeshFace& meshface){
    const ofVec3f &v1 = meshface.getVertex(0);
    const ofVec3f &v2 = meshface.getVertex(1);
    const ofVec3f &v3 = meshface.getVertex(2);
    return (v1 + v2 + v3)/3.0;
}

void ofxMathHyperSurface::drawFaceNormals(float length, int which) const {
    ofMesh nMesh;
    nMesh.setMode(OF_PRIMITIVE_LINES);
    const vector<ofVec3f> &verts = wVertices[which];
    int c = 0;
    for (int i = 0; i < verts.size(); i+=3) {
        ofVec3f v1 = verts[i];
        ofVec3f v2 = verts[i+1];
        ofVec3f v3 = verts[i+2];
        ofMeshFace meshFace;
        meshFace.setVertex(0, v1);
        meshFace.setVertex(1, v2);
        meshFace.setVertex(2, v3);
        ofVec3f norm = meshFace.getFaceNormal() * length;
        ofVec3f center = getCenter(meshFace);
        nMesh.addVertex(center);
        nMesh.addVertex(center + norm);
    }
    nMesh.draw();
}

ofVbo ofxMathHyperSurface::getVbo(int which)const{
    ofVbo mesh;
    mesh.setVertexData(wVertices[which].data(),
                       wVertices[which].size(),
                       GL_DYNAMIC_DRAW);
    mesh.setNormalData(frontFaceNormals[which].data(),
                       frontFaceNormals[which].size(),
                       GL_DYNAMIC_DRAW);
    mesh.setColorData(frontFaceColors[which].data(),
                      frontFaceColors[which].size(),
                      GL_DYNAMIC_DRAW);
    mesh.setTexCoordData(frontFaceTexCoords[which].data(),
                         frontFaceTexCoords[which].size(),
                         GL_DYNAMIC_DRAW);
    return mesh;
}

ofVbo ofxMathHyperSurface::getBackVbo(int which)const{
    ofVbo mesh;
    mesh.setVertexData(wVertices[which].data(),
                       wVertices[which].size(),
                       GL_DYNAMIC_DRAW);
    mesh.setNormalData(backFaceNormals[which].data(),
                       backFaceNormals[which].size(),
                       GL_DYNAMIC_DRAW);
    mesh.setColorData(backFaceColors[which].data(),
                      backFaceColors[which].size(),
                      GL_DYNAMIC_DRAW);
    mesh.setTexCoordData(backFaceTexCoords[which].data(),
                         backFaceTexCoords[which].size(),
                         GL_DYNAMIC_DRAW);
    return mesh;
}

ofMesh ofxMathHyperSurface::getMesh(int which)const{
    ofMesh mesh;
    mesh.addVertices(wVertices[which]);
    mesh.addNormals(frontFaceNormals[which]);
    mesh.addColors(frontFaceColors[which]);
    mesh.addTexCoords(frontFaceTexCoords[which]);
    return mesh;
}

ofMesh ofxMathHyperSurface::getBackMesh(int which)const{
    ofMesh mesh;
    mesh.addVertices(wVertices[which]);
    mesh.addNormals(backFaceNormals[which]);
    mesh.addColors(backFaceColors[which]);
    mesh.addTexCoords(backFaceTexCoords[which]);
    return mesh;
}

void ofxMathHyperSurface::clear(){
    for(int i=0; i<wVertices.size(); i++){
        wVertices[i].resize(0);
        frontFaceNormals[i].resize(0);
        backFaceNormals[i].resize(0);
        frontFaceColors[i].resize(0);
        backFaceColors[i].resize(0);
        frontFaceTexCoords[i].resize(0);
        backFaceTexCoords[i].resize(0);
    }
    wVertices.resize(0);
    frontFaceNormals.resize(0);
    backFaceNormals.resize(0);
    frontFaceColors.resize(0);
    backFaceColors.resize(0);
    frontFaceTexCoords.resize(0);
    backFaceTexCoords.resize(0);
}

float ofxMathHyperSurface::distFromPlane(const ofVec3f &point, const ofVec3f &planeNormal, const float &planeD){
    return planeNormal.dot(point) + planeD;
    
}

bool ofxMathHyperSurface::getSegmentPlaneIntersection(const ofVec3f &a, const ofVec3f &b, ofVec3f &intersectionPoint, const ofVec3f &planeNormal, const float &planeD){
    float d1 = distFromPlane(a, planeNormal, planeD);
    float d2 = distFromPlane(b, planeNormal, planeD);
    if (d1*d2 > 0) {
        return false;
    }
    float t = d1/(d1-d2);
    intersectionPoint = a + t * (b-a);
    return true;
}

void ofxMathHyperSurface::addTriangleToMesh(ofMesh &mesh, const ofVec3f &one, const ofVec3f &two, const ofVec3f &three){
    mesh.addVertex(one);
    mesh.addVertex(two);
    mesh.addVertex(three);
}

void ofxMathHyperSurface::addQuadToMesh(ofMesh &mesh, const ofVec3f &one, const ofVec3f &two, const ofVec3f &three, const ofVec3f &four){
    mesh.addVertex(one);
    mesh.addVertex(two);
    mesh.addVertex(four);
    mesh.addVertex(two);
    mesh.addVertex(three);
    mesh.addVertex(four);
}





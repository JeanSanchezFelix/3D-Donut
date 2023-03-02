#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    
    // Create a donut mesh
    float radius = 150; // Outer radius
    float holeRadius = 100; // Inner hole radius
    float cornerRadius = 25; // Corner radius
    int resolution = 60; // Number of segments around the circle
    int holeResolution = 30; // Number of segments around the hole
    
    // Create vertices
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for (int i = 0; i <= resolution; i++) {
        float angle = ofMap(i, 0, resolution, 0, 2 * PI);
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        for (int j = 0; j <= holeResolution; j++) {
            float holeAngle = ofMap(j, 0, holeResolution, 0, 2 * PI);
            float holeX = cos(holeAngle) * holeRadius;
            float holeY = sin(holeAngle) * holeRadius;
            float cornerAngle = ofMap(j, 0, holeResolution, 0, 2 * PI);
            float cornerX = cos(cornerAngle) * (radius - cornerRadius);
            float cornerY = sin(cornerAngle) * (radius - cornerRadius);
            ofVec3f vertex(x + holeX + cornerX, y + holeY + cornerY, 0);
            mesh.addVertex(vertex);
            ofVec3f normal(vertex.x - x, vertex.y - y, 0);
            normal.normalize();
            mesh.addNormal(normal);
            float u = ofMap(i, 0, resolution, 0, 1);
            float v = ofMap(j, 0, holeResolution, 0, 1);
            mesh.addTexCoord(ofVec2f(u, v));
        }
    }
    // Create indices
    for (int i = 0; i < resolution; i++) {
        int indexOffset = i * (holeResolution + 1);
        for (int j = 0; j < holeResolution; j++) {
            mesh.addIndex(indexOffset + j);
            mesh.addIndex(indexOffset + j + holeResolution + 1);
            mesh.addIndex(indexOffset + j + 1);
            mesh.addIndex(indexOffset + j + 1);
            mesh.addIndex(indexOffset + j + holeResolution + 1);
            mesh.addIndex(indexOffset + j + holeResolution + 2);
        }
    }
    
    donutMesh = mesh;
}

//--------------------------------------------------------------
void ofApp::update(){
    // Animate the donut mesh
    float time = ofGetElapsedTimef();
    float angle = time * 30.0; // Rotate 30 degrees per second
    ofQuaternion rotation(angle, ofVec3f(0, 1, 0));
    ofMatrix4x4 rotationMatrix(rotation);
    ofPushMatrix();
    ofMultMatrix(rotationMatrix);
    donutMesh.drawWireframe();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Set up the camera
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, -800);
    ofEnableDepthTest();
    ofCamera camera;
    camera.setPosition(0, 0, 800);
    camera.begin();
    
    // Draw the donut mesh
    ofPushMatrix();
    ofTranslate(0, 0, 0);
    ofSetColor(255, 255, 255);
    donutMesh.drawWireframe();
    ofPopMatrix();
    
    // End the camera
    camera.end();
    ofDisableDepthTest();
    ofPopMatrix();
}

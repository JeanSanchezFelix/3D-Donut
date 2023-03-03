
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
    ofSetFrameRate(60);

    // set up mesh
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    float radius1 = 150; // outer radius
    float radius2 = 85; // inner radius
    int numSegments = 50; // number of segments in the torus
    int numSides = 30; // number of sides for each segment
    float segmentAngle = 2 * PI / numSegments;
    float sideAngle = 2 * PI / numSides;
    float x, y, z;

    // generate vertices
    for (int i = 0; i <= numSegments; i++) {
        float angle1 = i * segmentAngle;
        for (int j = 0; j <= numSides; j++) {
            float angle2 = j * sideAngle;
            x = (radius1 + radius2 * cos(angle2)) * cos(angle1);
            y = (radius1 + radius2 * cos(angle2)) * sin(angle1);
            z = radius2 * sin(angle2);
            mesh.addVertex(ofVec3f(x, y, z));
            mesh.addNormal(ofVec3f(x - radius1 * cos(angle1), y - radius1 * sin(angle1), z));
            mesh.addTexCoord(ofVec2f(i / (float)numSegments, j / (float)numSides));
        }
    }

    // generate indices
    for (int i = 0; i < numSegments; i++) {
        for (int j = 0; j < numSides; j++) {
            int index1 = i * (numSides + 1) + j;
            int index2 = index1 + numSides + 1;
            mesh.addTriangle(index1, index2, index1 + 1);
            mesh.addTriangle(index2, index2 + 1, index1 + 1);
        }
    }
    donutMesh = mesh;
}




//--------------------------------------------------------------
void ofApp::update()
{
    // Animate the donut mesh
    float time = ofGetElapsedTimef();
    float angleX = ofSignedNoise(time * 0.2, 0) * 5.0; // Rotate smoothly and slowly for the X axis
    float angleY = ofSignedNoise(0, time * 0.2) * 5.0; // Rotate smoothly and slowly for the Y axis
    static ofQuaternion previousRotationX(0, ofVec3f(0, 0, 0));
    static ofQuaternion previousRotationY(0, ofVec3f(0, 0, 0));

    ofQuaternion rotationX(angleX, ofVec3f(1, 0, 0)); // Create a quaternion for rotating around X axis
    ofQuaternion rotationY(angleY, ofVec3f(0, 1, 0)); // Create a quaternion for rotating around Y axis

    // Use slerp to interpolate between previous rotation and current rotation smoothly
    float t = ofClamp(ofGetLastFrameTime() * 0.5, 0, 0.1); // Increase interpolation time for smoother rotation
    ofQuaternion currentRotationX, currentRotationY;
    currentRotationX.slerp(t, previousRotationX, rotationX);
    currentRotationY.slerp(t, previousRotationY, rotationY);

    ofQuaternion rotation = currentRotationX * currentRotationY; // Combine X and Y rotations
    previousRotationX = currentRotationX;                        // Store current rotation for next frame
    previousRotationY = currentRotationY;                        // Store current rotation for next frame

    ofMatrix4x4 rotationMatrix(rotation); // Create a rotation matrix from the quaternion
    ofPushMatrix();
    ofMultMatrix(rotationMatrix);

    // Apply rotation matrix to mesh vertices
    for (size_t i = 0; i < donutMesh.getVertices().size(); i++)
    {
        auto vertex = donutMesh.getVertices()[i];
        ofVec3f transformedVertex = ofVec3f(vertex) * rotationMatrix;
        donutMesh.getVertices()[i] = transformedVertex;
    }

    // Draw the donut mesh
    donutMesh.drawWireframe();

    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::draw()
{
    // Set up the camera
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, -800);
    ofEnableDepthTest();
    ofCamera camera;
    camera.setPosition(0, 0, 500);
    camera.begin();

    // Draw the donut mesh
    ofPushMatrix();
    ofTranslate(0, 0, 0);
    ofSetColor(34, 139, 34);
    donutMesh.drawWireframe();
    ofPopMatrix();

    // End the camera
    camera.end();
    ofDisableDepthTest();
    ofPopMatrix();
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
    ofSetFrameRate(60);

    // Create a donut mesh
    float radius = 150;      // Outer radius
    float holeRadius = 125;  // Inner hole radius
    float cornerRadius = 25; // Corner radius
    int resolution = 60;     // Number of segments around the circle
    int holeResolution = 30; // Number of segments around the hole

    // Create vertices
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for (int i = 0; i <= resolution; i++)
    {
        float angle = ofMap(i, 0, resolution, 0, 2 * PI);
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        for (int j = 0; j <= holeResolution; j++)
        {
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
    for (int i = 0; i < resolution; i++)
    {
        int indexOffset = i * (holeResolution + 1);
        for (int j = 0; j < holeResolution; j++)
        {
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
    camera.setPosition(0, 0, 850);
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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("Scary.ttf", 14);
    text = "Hello all and welcome to the Advanced Programming course! We hope the semester is going good so far and we cannot wait to see what great coders you are.";
    xPos = ofRandom(ofGetWidth()-font.stringWidth(text));
    yPos = ofRandom(ofGetHeight()-font.stringHeight(text));
    xSpeed = 115;
    ySpeed = 100;
    bounce.load("bounce.mp3");
    bounce.setVolume(0.3);
    title.load("Scary.ttf", 26);

}

//--------------------------------------------------------------
void ofApp::update(){
    if(xPos + font.stringWidth(text) >= ofGetWidth() || xPos <= 0){
        xSpeed *= -1;
        bounce.play();
    }
    if(yPos + font.stringHeight(text)>= ofGetHeight() || yPos <= 0){
        ySpeed *=-1;
        bounce.play();
    }
    xPos += xSpeed;
    yPos += ySpeed;
}

//--------------------------------------------------------------
void ofApp::draw(){
    title.drawString("PA0",(ofGetWidth() - title.stringWidth("PA0"))/2, 50);
    font.drawString(text, xPos, yPos);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
//
// ofApp.cpp
//


#include "ofApp.h"


using namespace glm; // vec3


namespace {
const char* keyPressedTextDefault = 
    "keyPressed():\tkey\tkeycode codepoint modifiers scancode\n";
}


void ofApp::setup()
{
    ofSetVerticalSync(true);

    keyPressedText = keyPressedTextDefault;
    camera.setPosition(100, 50, 600);
}


void ofApp::update()
{
    camera.move(cameraVelocity);    
}


void ofApp::draw()
{
    ofBackground(20);

    camera.begin();
    //rotateAxes();
    drawScene();
    camera.end();

    drawUsage();
}


void ofApp::rotateAxes()
{
    // rotate to math coordinate system (x out, y right, z up)

    ofRotateYRad(-PI/2);
    ofRotateXRad(-PI/2);

    // rotate for viewpoint in first octant

    ofRotateYRad(PI/12);
    ofRotateZRad(-PI/12);
}


void ofApp::drawScene()
{
    // from examples/3d/easyCamExample

    ofSetConeResolution(20, 2);
    ofSetCylinderResolution(20, 2);
    ofEnableDepthTest();
    ofSetColor(ofColor::orange);//RIGHT
    ofDrawCone(100, 0, 0, 50, 100);
    
    ofSetColor(ofColor::white);//LEFT
    ofDrawSphere(-100, 0, 0, 50);
    
    ofSetColor(ofColor::blue);//BOTTOM
    ofDrawBox(0, 100, 0, 100);
    
    ofSetColor(ofColor::cyan);//TOP
    ofDrawCylinder(0, -100, 0, 50, 100);
    
    ofSetColor(ofColor::yellow);//FRONT
    ofDrawBox(0, 0, 100, 100);
    
    ofSetColor(ofColor::magenta);//BACK
    ofDrawBox(0, 0, -100, 100);
    
    ofDrawGrid(20,10,true,true,true,true);
    ofDisableDepthTest();
}


void ofApp::drawUsage()
{
    stringstream ss;
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) << endl << endl;
    ss << "Camera movement:\n";
    ss << "asdw:        translate x/z\n";
    ss << "arrow keys:  translate x/y\n";

    ofSetColor(255);
    ofDrawBitmapString(ss.str().c_str(), 20, 20);
    ofDrawBitmapString(keyPressedText.c_str(), ofGetWindowWidth()/2, 20);
}


//void ofApp::keyPressed(int key)
void ofApp::keyPressed(ofKeyEventArgs& key)
{
    ostringstream oss;
    oss << keyPressedTextDefault 
        << "\t\t" << key.key << "\t" << key.keycode 
        << "\t" << key.codepoint << "\t\t" << key.modifiers << "\t" << key.scancode << endl;
    keyPressedText = oss.str();

    cout << keyPressedText << flush;

    float d = 5;

    switch(key.key) 
    {
        case 'a':
        case OF_KEY_LEFT:
            cameraVelocity.x = -d;
            break;
        case 'd':
        case OF_KEY_RIGHT:
            cameraVelocity.x = d;
            break;
        case OF_KEY_UP:
            cameraVelocity.y = d;
            break;
        case OF_KEY_DOWN:
            cameraVelocity.y = -d;
            break;
        case 'w':
            cameraVelocity.z = -d;
            break;
        case 's':
            cameraVelocity.z = d;
            break;
    }
}


void ofApp::keyReleased(int key)
{
    keyPressedText = keyPressedTextDefault;

    switch(key) 
    {
        case 'a':
        case OF_KEY_LEFT:
        case 'd':
        case OF_KEY_RIGHT:
            cameraVelocity.x = 0;
            break;
        case OF_KEY_UP:
        case OF_KEY_DOWN:
            cameraVelocity.y = 0;
            break;
        case 'w':
        case 's':
            cameraVelocity.z = 0;
            break;
    }
}


void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}



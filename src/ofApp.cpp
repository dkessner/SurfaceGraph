//
// ofApp.cpp
//


#include "ofApp.h"


using namespace glm; // vec3


void ofApp::setup()
{
    ofSetVerticalSync(true);

    helpVisible = false;

    camera.setPosition(100, 50, 400);

    //cam.setRelativeYAxis(true);
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

    drawHelp();
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


void ofApp::drawHelp()
{
    if (!helpVisible) return;

    drawInteractionArea();
    ofSetColor(255);

    stringstream ss;
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) <<endl<<endl;
//    ss << "MODE: " << (cam.getOrtho()?"ORTHO":"PERSPECTIVE")<<endl;
//    ss << "MOUSE INPUT ENABLED: " << (cam.getMouseInputEnabled()?"TRUE":"FALSE")<<endl;
//    ss << "INERTIA ENABLED: " << (cam.getInertiaEnabled()?"TRUE":"FALSE")<<endl;
//    ss << "ROTATION RELATIVE Y AXIS: " << (cam.getRelativeYAxis()?"TRUE":"FALSE")<<endl;
    ss << "Camera position: " << camera.getPosition() << endl;
    ss << endl;
    ss << "Toogle camera projection mode (ORTHO or PERSPECTIVE):"<< endl;
    ss << "    press space bar."<< endl;
    ss << "Toggle mouse input:"<<endl;
    ss << "    press 'c' key."<< endl;
    ss << "Toggle camera inertia:"<<endl;
    ss << "    press 'i' key."<< endl;
    ss << "Toggle rotation relative Y axis:"<<endl;
    ss << "    press 'y' key."<< endl;
    ss << "Toggle this help:"<<endl;
    ss << "    press 'h' key."<< endl;
    ss << endl;
    ss << "camera x,y rotation:" <<endl;
    ss << "    LEFT MOUSE BUTTON DRAG inside yellow circle"<<endl;
    ss << endl;
    ss << "camera z rotation or roll"<<endl;
    ss << "    LEFT MOUSE BUTTON DRAG outside yellow circle"<<endl;

    ss << endl;
    ss << "move over x,y axis / truck and boom:"<<endl;
    ss << "    LEFT MOUSE BUTTON DRAG + m"<<endl;
    ss << "    MIDDLE MOUSE BUTTON PRESS"<<endl;
    ss << endl;
    ss << "move over z axis / dolly / zoom in or out:"<<endl;
    ss << "    RIGHT MOUSE BUTTON DRAG"<<endl;
    ss << "    VERTICAL SCROLL"<<endl<<endl;
    /*
    if (cam.getOrtho()) {
        ss << "    Notice that in ortho mode zoom will be centered at the mouse position." << endl;
    }
    */

    ofDrawBitmapString(ss.str().c_str(), 20, 20);
}


void ofApp::drawInteractionArea()
{
    ofSetCircleResolution(64);

    ofRectangle vp = ofGetCurrentViewport();
    float r = std::min<float>(vp.width, vp.height) * 0.5f;
    float x = vp.width * 0.5f;
    float y = vp.height * 0.5f;

    ofPushStyle();
    ofSetLineWidth(3);
    ofSetColor(255, 255, 0);
    ofNoFill();
    glDepthMask(false);
    ofDrawCircle(x, y, r);
    glDepthMask(true);
    ofPopStyle();
}


void ofApp::keyPressed(int key)
{
    float d = 5;

    switch(key) {
      case OF_KEY_LEFT:
          cameraVelocity.x = -d;
          break;
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

      case ' ':
    	    //cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
            break;
	    case 'C':
	    case 'c':
            //cam.getMouseInputEnabled() ? cam.disableMouseInput() : cam.enableMouseInput();
            break;
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'H':
		case 'h':
			helpVisible ^= true;
			break;
        case 'I':
        case 'i':
		    //cam.getInertiaEnabled() ? cam.disableInertia() : cam.enableInertia();
            break;
        case 'Y':
        case 'y':
            //cam.setRelativeYAxis(!cam.getRelativeYAxis());
            break;
	}
}


void ofApp::keyReleased(int key)
{
    switch(key) 
    {
      case OF_KEY_LEFT:
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


//
// ofApp.cpp
//


#include "ofApp.h"


using namespace glm; // vec3


//
// TODO: use ofDrawArrow for vectors
// TODO: try ofDrawRotationAxes for moving along parametric curves
//


namespace {
float f(float x, float y)
{
    return x*x - y*y;
}

float f2(float x, float y)
{
    return x*x + y*y;
}
}//namespace

void ofApp::createSurface()
{
    const float size = 5;
    const float step = .5;

    //vector<ofPath> surface; 

    // lines f(c,y)

    for (float x=-size; x<=size; x+=step)
    {
        ofPath path;
        path.clear();
        path.setStrokeColor(ofColor(0, 255, 0));
        path.setStrokeWidth(.5);
        path.setFilled(false);

        path.setMode(ofPath::POLYLINES); // TODO: testing on OSX

        for (float y=-size; y<size; y+=step)
        {
            path.lineTo(x, y, f(x,y));
        }
        surface.push_back(path);
    }

    // lines f(x, c)

    for (float y=-size; y<=size; y+=step)
    {
        ofPath path;
        path.clear();
        path.setStrokeColor(ofColor(0, 255, 0));
        path.setStrokeWidth(.5);
        path.setFilled(false);

        path.setMode(ofPath::POLYLINES); // TODO: testing on OSX

        for (float x=-size; x<size; x+=step)
        {
            path.lineTo(x, y, f(x,y));
        }
        surface.push_back(path);
    }

    //return surface; // TODO: check on move semantics
}


void ofApp::createSurface2()
{
    const float size = 5;
    const float step = .5;

    for (float x=-size; x<=size; x+=step)
    for (float y=-size; y<size; y+=step)
    {
        surface2.addVertex(ofVec3f(x, y, f2(x,y)));
        surface2.addColor(ofColor::blue);
    }

    for (float y=-size; y<size; y+=step)
    for (float x=-size; x<=size; x+=step)
    {
        surface2.addVertex(ofVec3f(x, y, f2(x,y)));
        surface2.addColor(ofColor::yellow);
    }

    surface2.setMode(OF_PRIMITIVE_LINE_STRIP);
}


void ofApp::setup()
{
    ofSetVerticalSync(true);

    camera.setDistance(20);
    camera.setRelativeYAxis(true);

    createSurface();
    createSurface2();
}


void ofApp::update()
{}


void ofApp::draw()
{
    ofBackground(20);

    camera.begin();
    rotateAxes();
    drawScene();
    camera.end();

    if (showUsage) drawUsage();

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


void ofApp::drawCoordinateSystem()
{
    const float stepSize = 1;
    const size_t stepCount = 10;
    const bool labels = true;
    const bool showYZ = false;
    const bool showXZ = false;
    const bool showXY = true;

    ofDrawGrid(stepSize, stepCount, labels, showYZ, showXZ, showXY);
    ofSetLineWidth(5);
    ofDrawAxis(stepSize*stepCount);
}


void ofApp::drawScene()
{
    drawCoordinateSystem();
    ofEnableDepthTest();
    
    for (auto line : surface)
        line.draw();

    ofSetLineWidth(.5);
    surface2.draw();

    ofDisableDepthTest();
}


void ofApp::drawUsage()
{
    stringstream ss;
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) <<endl<<endl;
    ss << "MODE: " << (camera.getOrtho()?"ORTHO":"PERSPECTIVE")<<endl;
    ss << "MOUSE INPUT ENABLED: " << (camera.getMouseInputEnabled()?"TRUE":"FALSE")<<endl;
    ss << "INERTIA ENABLED: " << (camera.getInertiaEnabled()?"TRUE":"FALSE")<<endl;
    ss << "ROTATION RELATIVE Y AXIS: " << (camera.getRelativeYAxis()?"TRUE":"FALSE")<<endl;
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
    if (camera.getOrtho()) {
        ss << "    Notice that in ortho mode zoom will be centered at the mouse position." << endl;
    }
    ofDrawBitmapString(ss.str().c_str(), 20, 20);
}


void ofApp::keyPressed(int key)
{
    switch(key) 
    {
        case ' ':
    	    camera.getOrtho() ? camera.disableOrtho() : camera.enableOrtho();
            break;
        case 'C':
        case 'c':
            camera.getMouseInputEnabled() ? camera.disableMouseInput() : camera.enableMouseInput();
            break;
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            showUsage = !showUsage;
        case 'I':
        case 'i':
            camera.getInertiaEnabled() ? camera.disableInertia() : camera.enableInertia();
            break;
        case 'Y':
        case 'y':
            camera.setRelativeYAxis(!camera.getRelativeYAxis());
            break;
    }
}


void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}



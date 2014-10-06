#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    ofBackground(10, 10, 10);

    camera.setDistance(10);
    light.setPosition(10,30,-25);

    objectLoader = new waveFrontLoader();
    objectLoader->loadMaterial(true); //true or false depending on if a .mtl file exists
    objectLoader->loadFile("test.obj");
    mesh = objectLoader->generateMesh();
    delete objectLoader;
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{
    camera.begin();
    light.enable();
    mesh.draw();
    light.disable();
    camera.end();
}

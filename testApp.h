#pragma once

#include "ofMain.h"
#include "waveFrontLoader.h"

class testApp : public ofBaseApp{

	public:
	
	void setup();
	void update();
	void draw();

	waveFrontLoader *objectLoader;
        ofMesh mesh;
        ofEasyCam camera;
        ofLight light;

};

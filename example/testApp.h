#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxTouchHelper.h"


class testApp : public ofxiPhoneApp {

	public:
		void setup();
		void update();
		void draw();
		void exit(){};

		void touchDown(ofTouchEventArgs &touch);
		void touchMoved(ofTouchEventArgs &touch);
		void touchUp(ofTouchEventArgs &touch);
		void touchDoubleTap(ofTouchEventArgs &touch){};
		void touchCancelled(ofTouchEventArgs &touch){};

		ofxTouchHelper touches;
};


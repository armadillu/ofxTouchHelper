#include "testApp.h"

void testApp::setup(){
	ofRegisterTouchEvents(this);
	ofxiPhoneAlerts.addListener(this);
	ofBackground(16);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	touches.setup();

}


void testApp::update(){

	float dt = 1./60.;
	touches.update(dt);
}


void testApp::draw(){

	vector<ofxTouchHelper::TouchUnit> t = touches.getTouches();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(ofColor::red);
	for(int i = 0 ; i < t.size(); i++){
		ofCircle(t[i].pos, 40.0f + fmodf(t[i].duration * 50.0f, 15.0f) );
	}
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	touches.draw(); //overlay debug sstuff
}


void testApp::touchDown(ofTouchEventArgs &t){
	touches.touchDown(t);
}


void testApp::touchMoved(ofTouchEventArgs &t){
	touches.touchMoved(t);
}


void testApp::touchUp(ofTouchEventArgs &t){
	touches.touchUp(t);
}
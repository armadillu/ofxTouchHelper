//
//  ofxTouchHelper.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 28/12/12.
//
//

#ifndef ofxTouchHelper_h
#define ofxTouchHelper_h

#include "ofMain.h"

#define	MAX_TOUCHES		12

class ofxTouchHelper{

	public:

	struct TouchUnit{
		bool down;
		float duration;
		ofVec2f pos;
		ofVec2f prevPos;
		float speed;
	};


	void setup(){
		for (int i = 0; i < MAX_TOUCHES; i++){
			touch[i].down = false;
			touch[i].duration = 0.0f;
			touch[i].speed = 0.0f;
		}
	}


	void update(float dt){
		for (int i = 0; i < MAX_TOUCHES; i++){
			if( touch[i].down ){
				touch[i].duration += dt;
				touch[i].speed = ( touch[i].pos - touch[i].prevPos ).length() / dt;
				touch[i].prevPos = touch[i].pos;

			}else{
				touch[i].speed = 0.0f;
			}
		}
	}


	void draw(){
		for (int i = 0; i < MAX_TOUCHES; i++){
			if( touch[i].down ){
				ofFill();
				ofSetColor(255,32);
				ofCircle(touch[i].pos, 40);
				ofNoFill();
				ofSetColor(64);
				ofCircle(touch[i].pos, 40);
				ofSetColor(255,64);
				ofDrawBitmapString( "#" + ofToString(i), touch[i].pos + ofVec2f(-10,-50));
				ofDrawBitmapString( "pos: " + ofToString(touch[i].pos), touch[i].pos + ofVec2f(50,-14));
				ofDrawBitmapString( "duration: " + ofToString(touch[i].duration,1) + " sec", touch[i].pos + ofVec2f(50,0));
				char aux[128];
				sprintf(aux, "speed: %5.1f pixels/sec", touch[i].speed);
				ofDrawBitmapString( aux, touch[i].pos + ofVec2f(50,14));
			}
		}
	}


	void touchDown(ofTouchEventArgs &t){
		touch[t.id].duration = 0.0f;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].prevPos = touch[t.id].pos;
		touch[t.id].down = true;
	}


	void touchMoved(ofTouchEventArgs &t){
		if ( touch[t.id].down == false) return;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
	}


	void touchUp(ofTouchEventArgs &t){
		touch[t.id].down = false;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].duration = 0.0f;
	};


	TouchUnit* getTouchWithID(int ID){

		if (ID >= 0 && ID < MAX_TOUCHES){
			return &touch[ID];
		}
		return NULL;
	};

	
	vector<TouchUnit> getTouches(){
		vector<TouchUnit> t;
		for (int i = 0; i < MAX_TOUCHES; i++) {
			if (touch[i].down == true){
				t.push_back(touch[i]);
			}
		}
		return t;
	}

	int getNumTouches(){

		int touchDown = 0;
		for (int i = 0; i < MAX_TOUCHES; i++) {
			if (touch[i].down == true){
				touchDown ++;
			}
		}
		return touchDown;
	}


	TouchUnit touch[MAX_TOUCHES];

};


#endif

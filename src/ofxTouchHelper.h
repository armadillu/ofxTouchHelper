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
#define SPEED_SMOOTH_RATIO	0.5f
class ofxTouchHelper{

	public:

	struct TouchUnit{
		TouchUnit(){
			doubleTap = false;
			speed = 0.0f;
			down = false;
			duration = 0.0f;
		}
		bool doubleTap;
		bool down;
		float duration;
		ofVec2f pos;
		ofVec2f prevPos;
		ofVec2f smoothSpeed;
		float speed;
	};


	void setup(){
		debug = false;
		for (int i = 0; i < MAX_TOUCHES; i++){
			touch[i].down = false;
			touch[i].duration = 0.0f;
			touch[i].speed = 0.0f;
		}
		timeSinceLastDownEvent = timeSinceLastUpEvent = 0.0f;
	}


	void update(float dt){
		for (int i = 0; i < MAX_TOUCHES; i++){
			if( touch[i].down ){
				touch[i].duration += dt;
				touch[i].speed = (1.0f-SPEED_SMOOTH_RATIO) * touch[i].speed + SPEED_SMOOTH_RATIO * ( touch[i].pos - touch[i].prevPos ).length() / dt;
				touch[i].smoothSpeed = (1.0f-SPEED_SMOOTH_RATIO) * touch[i].smoothSpeed + SPEED_SMOOTH_RATIO * ( touch[i].pos - touch[i].prevPos ) / dt;
				touch[i].prevPos = touch[i].pos;
			}else{
				touch[i].smoothSpeed *= 0.5;
				touch[i].speed = 0.0f;
			}
		}
		timeSinceLastDownEvent += dt;
		timeSinceLastUpEvent += dt;
	}


	void draw(){
		for (int i = 0; i < MAX_TOUCHES; i++){
			if( touch[i].down ){
				ofFill();
				ofSetColor(255,32);
				ofCircle(touch[i].pos, 40);
				ofNoFill();
				ofSetColor(96);
				ofCircle(touch[i].pos, 40);
				if (touch[i].doubleTap){
					ofSetColor(96);
					ofCircle(touch[i].pos, 47);
				}
				ofSetColor(255,64);

				ofDrawBitmapString( "#" + ofToString(i), touch[i].pos + ofVec2f(-10,-50));
				ofDrawBitmapString( "pos: " + ofToString(touch[i].pos), touch[i].pos + ofVec2f(50,-14));
				ofDrawBitmapString( "duration: " + ofToString(touch[i].duration,1) + " sec", touch[i].pos + ofVec2f(50,0));
				char aux[128];
				sprintf(aux, "speed: %5.1f pixels/sec", touch[i].speed);
				ofDrawBitmapString( aux, touch[i].pos + ofVec2f(50,14));
			}
		}
		ofFill();
	}


	void touchDown(ofTouchEventArgs &t){
		if(debug) printf("touchDown %d\n", t.id);
		timeSinceLastDownEvent = 0.0f;
		touch[t.id].duration = 0.0f;
		//touch[t.id].doubleTap = false;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].prevPos = touch[t.id].pos;
		touch[t.id].down = true;
	}


	void touchMoved(ofTouchEventArgs &t){
		if(debug) printf("touchMoved %d\n", t.id);
		if ( touch[t.id].down == false) return;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
	}


	void touchUp(ofTouchEventArgs &t){
		if(debug) printf("touchUp %d\n", t.id);
		timeSinceLastUpEvent = 0.0f;
		touch[t.id].doubleTap = false;
		touch[t.id].down = false;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].duration = 0.0f;
	};

	void touchDoubleTap(ofTouchEventArgs &t){
		if(debug) printf("touchDoubleTap %d\n", t.id);
		timeSinceLastUpEvent = 0.0f;
		touch[t.id].down = true;
		touch[t.id].doubleTap = true;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].duration = 0.0f;
	}

	void touchCancelled(ofTouchEventArgs & touch){
	}

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

	void setVerbose(bool v){ debug = v;}

	float getTimeSinceLastUpEvent(){
		return timeSinceLastUpEvent;
	}


	float getTimeSinceLastDownEvent(){
		return timeSinceLastDownEvent;
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


	float timeSinceLastDownEvent;
	float timeSinceLastUpEvent;
	TouchUnit touch[MAX_TOUCHES];
	bool debug;

};

#endif

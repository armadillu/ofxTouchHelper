
/*
 *  TouchAnimation.mm
 *  emptyExample
 *
 *  Created by Oriol Ferrer Mesià on 28/03/12.
 *  Copyright 2012 uri.cat. All rights reserved.
 *
 */

#include "TouchAnimation.h"

#ifdef TARGET_WIN32
#define _USE_MATH_DEFINES
#include <math.h>
#endif

void TouchAnimation::setup(){
	touchImage.loadImage("touchCircle.png");
	touchImage2.loadImage("touchCircle2.png");
}


void TouchAnimation::update(float dt){

	//to keep it simple, walk the vector backwards and delete dead touches easily
	for (int i = touches.size() - 1; i >= 0; i--){
		touch t = touches[i];
		t.time -= dt;
		touches[i] = t;
		if( touches[i].time <= 0){
			touches.erase( touches.begin() + i);
		}
	}
}


void TouchAnimation::addTouch(float x, float y, TouchType type){
	touch t;
	t.pos = ofVec2f(x, y);
	t.type = type;
	switch (type) {
		case T_SINGLE: t.time = t.duration =  TOUCH_ANIM_DURATION * 2; break;
		case T_DOUBLE: t.time = t.duration = TOUCH_ANIM_DURATION * 2; break;
		case T_UP: t.time = t.duration = TOUCH_ANIM_DURATION ; break;
	}
	touches.push_back(t);
}


void TouchAnimation::draw(ofImage & hand){

	ofSetRectMode(OF_RECTMODE_CENTER);
	for (int i = 0; i < touches.size(); i++){
		touch t = touches[i];
		ofVec2f p = touches[i].pos;
		float lifePercent = (t.duration - t.time) / t.duration; //[0..1]
		float radius = touchImage.getWidth() * lifePercent;
		float alpha = 1.0f;
		if ( lifePercent < 0.5f){
			alpha = 1.0f;
		}else {
			alpha = 0.5 + 0.5 * cosf( -M_PI + 2.0f * M_PI * lifePercent );
		}

		ofSetColor(255,255,255, alpha * 128);
		switch (touches[i].type) {
			case T_SINGLE:
				ofSetColor(255, alpha * 128);
				touchImage.draw(p.x, p.y, radius, radius);
				break;
			case T_DOUBLE:
				ofSetColor(255, alpha * 128);
				touchImage2.draw(p.x, p.y, radius, radius);
				break;
			case T_UP:
				if (lifePercent < 0.5){
					ofSetColor(255, alpha * 128 );
				}else{
					ofSetColor(255, (1 - lifePercent) * 128 );
				}
				hand.draw(p.x, p.y);
				break;

		}
	}
}
	

/*
 *  TouchAnimation.h
 *  emptyExample
 *
 *  Created by Oriol Ferrer Mesià on 28/03/12.
 *  Copyright 2012 uri.cat. All rights reserved.
 *
 */

#include "ofMain.h"
#include <vector>

#define TOUCH_ANIM_DURATION	0.5f

class TouchAnimation{

public:

	enum TouchType{ T_SINGLE, T_DOUBLE, T_UP };
	
	typedef struct touch{
		ofVec2f pos;
		float time;
		float duration;
		TouchType type;
	};
	
	vector<touch> touches;

	void setup();
	void update(float dt);
	void addTouch(float x, float y, TouchType type);
	void draw(ofImage & hand);

	ofImage touchImage;
	ofImage touchImage2;

};

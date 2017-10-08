#pragma once

#include "ofMain.h"
#include "ofxFontStash.h"




class mirrorType{

	public:
		mirrorType(){};
		~mirrorType(){};
		void setup();
		void reset(float timeLimit);
		void draw(vector<ofFbo>cam, ofFbo grad,string text,int size,ofVec2f pos);
		ofRectangle getRect(string text, int size, ofVec2f pos);

		bool isAlive();
	//	ofVideoGrabber cam;

private:
		ofxFontStash  font[5];
		ofFbo fboMask[4];
		ofFbo fboDraw[4];
	//	string text;

		ofShader mask;
		ofRectangle rectText;

		float lifeSpan;
		float timeCounter;
		bool active;
};

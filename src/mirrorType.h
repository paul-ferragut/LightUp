#pragma once

#include "ofMain.h"
#include "ofxFontStash.h"




class mirrorType{

	public:
		mirrorType(){};
		~mirrorType(){};
		void setup();//ofxFontStash *FONT1, ofxFontStash *FONT2, ofxFontStash *FONT3, ofxFontStash *FONT4, ofxFontStash *FONT5
		void reset(float timeLimit);
		void update();//vector<ofFbo>cam, ofFbo grad,string text,int size,ofVec2f pos
	//	ofRectangle getRect(string text, int size, ofVec2f pos);

		bool isAlive();
	//	ofVideoGrabber cam;
float opacityCounter[4];
private:
	/*
	ofxFontStash *font1;
	ofxFontStash *font2;
	ofxFontStash *font3;
	ofxFontStash *font4;
	ofxFontStash *font5;
	*/

	//	ofxFontStash  font[5];
	//	ofFbo fboMask[4];
	//	ofFbo fboDraw[4];
	//	string text;

		ofShader mask;
		ofRectangle rectText;

		float lifeSpan;
		float timeCounter;
		bool active;

	//	float opacity[4];
		
};

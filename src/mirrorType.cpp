#include "mirrorType.h"

//--------------------------------------------------------------
void mirrorType::setup(){
	/*
	ofxFontStash *FONT1, ofxFontStash *FONT2, ofxFontStash *FONT3, ofxFontStash *FONT4, ofxFontStash *FONT5
	font1= FONT1;
	font2= FONT2;
	font3= FONT3;
	font4= FONT4;
	font5= FONT5;
	*/
	 lifeSpan=0;
	timeCounter=0;
	active=false;
}

void mirrorType::reset(float timeLimit)
{
	active = true;
	timeCounter = ofGetFrameNum();
	lifeSpan=timeLimit;

	for (int i = 0; i < 4; i++) {		
			opacityCounter[i] = 0;
	}
}

//--------------------------------------------------------------
void mirrorType::update(){
//vector<ofFbo>cam, ofFbo grad, string text, int size, ofVec2f pos
	int inc =15;
	if (ofGetFrameNum() - timeCounter < (lifeSpan-37)) {

		opacityCounter[0]+= inc;
		if (opacityCounter[0] > 155) {
			opacityCounter[1] += inc;
		}
		if (opacityCounter[1] > 155) {
			opacityCounter[2] += inc;
		}
		if (opacityCounter[2] > 155) {
			opacityCounter[3] += inc;
		}

		for (int i = 0; i < 4; i++) {
			if (opacityCounter[i] > 155) {
				opacityCounter[i]=255;
			}
		}
	}
	else {
		opacityCounter[3] -= inc;
		if (opacityCounter[3] < 100) {
			opacityCounter[2] -= inc;
		}
		if (opacityCounter[2] < 100) {
			opacityCounter[1]-= inc;
		}
		if (opacityCounter[1] < 100) {
			opacityCounter[0] -= inc;
		}

		for (int i = 0; i < 4; i++) {
			if (opacityCounter[i] <0 ) {
				opacityCounter[i] = 0;
			}
		}
	}

	if (ofGetFrameNum() - timeCounter > lifeSpan) {
	
		active = false;

	}

}
/*
ofRectangle mirrorType::getRect(string text, int size, ofVec2f pos)
{

	//font[0].getBBox(text, size, pos.x, pos.y);

	return font[0].getBBox(text, size, pos.x, pos.y);
}
*/

//--------------------------------------------------------------

bool mirrorType::isAlive() {

	return active;

}
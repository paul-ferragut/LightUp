#include "mirrorType.h"

//--------------------------------------------------------------
void mirrorType::setup(){


	 lifeSpan=0;
	timeCounter=0;
	active=false;
}

void mirrorType::reset(float timeLimit)
{
	active = true;
	timeCounter = ofGetElapsedTimeMillis();
	lifeSpan=timeLimit;
}

//--------------------------------------------------------------
void mirrorType::draw(vector<ofFbo>cam, ofFbo grad, string text, int size, ofVec2f pos){





	if (ofGetElapsedTimeMillis() - timeCounter > lifeSpan) {
	
		active = false;

	}

}

ofRectangle mirrorType::getRect(string text, int size, ofVec2f pos)
{

	//font[0].getBBox(text, size, pos.x, pos.y);

	return font[0].getBBox(text, size, pos.x, pos.y);
}

//--------------------------------------------------------------

bool mirrorType::isAlive() {

	return active;

}
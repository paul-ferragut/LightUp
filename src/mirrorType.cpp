#include "mirrorType.h"

//--------------------------------------------------------------
void mirrorType::setup(){

	for (int i = 0; i < 4; i++) {

		fboMask[i].allocate(ofGetWidth(),ofGetHeight(), GL_RGB);
		fboDraw[i].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	}

	int fontSize = 72;

	font[0].setup("fonts/Detroit11BevelOne.ttf", 1.0, 1024, false, 8, 1.5);//Vera.ttf

	font[1].setup("fonts/Detroit06PrismLeft.ttf", 1.0, 1024, false, 8, 1.5);

	font[2].setup("fonts/Detroit07PrismRight.ttf", 1.0, 1024, false, 8, 1.5);

	font[3].setup("fonts/Detroit08PrismTop.ttf", 1.0, 1024, false, 8, 1.5);

	font[4].setup("fonts/Detroit09PrismBottom.ttf", 1.0, 1024, false, 8, 1.5);

	for (int i = 0; i < 5; i++) {
		font[i].setCharacterSpacing(0);
	}
	
	
	mask.load("mask");
	cout << "SETUP" << endl;

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


	for (int i = 0; i < 4; i++) {



	fboMask[i].begin();
	//ofScale(0.5, 0.5);
	ofClear(0,0,0,255);
	//ofBackgroundGradient(ofColor(0, 0, 0), ofColor(0, 0, 0), OF_GRADIENT_LINEAR);	
	ofSetColor(255, 255, 255);
	ofNoFill();
	ofDrawRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
	ofFill();
	ofDrawCircle(10, 10, 20);
	ofDrawCircle( 10, ofGetHeight() - 10, 20);
	ofDrawCircle(ofGetWidth() - 10, ofGetHeight() - 10, 20);

	ofPushMatrix();
	ofTranslate(pos.x, pos.y);// + font[0].getBBox(text, size, 0, 0).height
	font[i+1].draw(text, size, 0,0);//pos.x,pos.y
	ofPopMatrix();
	fboMask[i].end();



	fboDraw[i].begin();
	ofClear(0, 0);
	//ofClearAlpha();
	ofSetColor(255, 255, 255);

	/*

	*/
	/*
	ofFbo camFBO;
	camFBO.allocate(ofGetWidth(), ofGetHeight());

	camFBO.begin();		

		ofPushMatrix();
	switch (i) {
	
	case 0:
		ofScale(1, 1);
		break;
	case 1:
		ofScale(-1,1);
		ofTranslate(-ofGetWidth(), 0);
		break;
	case 2:
		ofScale(-1, -1);
		ofTranslate(-ofGetWidth(), -ofGetHeight());
		break;
	case 3:
		ofScale(1, -1);
		ofTranslate(0, -ofGetHeight());
		break;
	}
	cam.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	ofPopMatrix();

	camFBO.end();

	*/

	mask.begin();
	mask.setUniformTexture("maskTex", fboMask[i].getTexture(), 1);
	ofFill();
	//ofSetColor(255, 0, 0);
	//ofDrawRectangle(10, 10, ofGetWidth() - 10, ofGetHeight() - 10);
//	ofPushMatrix();
	//ofPopMatrix();

//	ofScale(2, 2);

	
	cam[i].draw(0,0);

	mask.end();
	fboDraw[i].end();

	//fboDraw[i].getTexture().setAlphaMask(fboMask[i].getTexture());

	
	}

	//cout << "d2" << endl;
	ofSetColor(255, 255, 255);
	for (int i = 0; i < 4; i++) {
		//fboDraw[i].begin();
	
		//fboDraw[i].end();

		fboDraw[i].draw(0, 0);
	}
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);//+ font[0].getBBox(text, size, 0, 0).height
	//ofVec2f pos(20, ofGetHeight() / 2);
	ofSetColor(0, 0, 0);
	font[0].draw(text, size, 0,0);
	ofNoFill();
	ofSetColor(255,255,255);
	if (active) { ofSetColor(255, 0, 0); }
	ofDrawRectangle(font[0].getBBox(text, size, 0,0));
	ofPopMatrix();
	ofFill();


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
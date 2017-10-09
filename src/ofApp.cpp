#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//for (int i = 0; i < TYPE_MAX; i++) {

	//	type[i].setup();

	//}

	cam.setup(640*2, 480*2);


	currentType = 0;


	for (int i = 0; i < 4; i++) {	
		ofFbo ncamFBO;
		
	ncamFBO.allocate(ofGetWidth(), ofGetHeight());
		camFBO.push_back(ncamFBO);
	}
	
	int squareSize = ofGetHeight() / GRID_HEIGHT;
	int gridHN = ofGetHeight() / squareSize;
	int gridWN= ofGetWidth() / squareSize;

	for (int i = 0; i < gridWN; i++) {
		for (int j = 0; j < gridHN; j++) {
			ofRectangle nR(i*squareSize, j*squareSize, squareSize, squareSize);
			gridRect.push_back(nR);
			gridRectFilled.push_back(false);
		}
	}

	typeSizeOptions.push_back(72);
	typeSizeOptions.push_back(90);
	typeSizeOptions.push_back(120);
	typeSizeOptions.push_back(180);
	typeSizeOptions.push_back(220);

	typeStringChoice[0] = "Lorem ipsum dolor sit amet,";
	typeStringChoice[1] = "consectetur adipiscing";
	typeStringChoice[2] = "Sed porta";
	typeStringChoice[3] = "Morbi";
	typeStringChoice[4] = "vel vulputate ex iaculis";
	typeStringChoice[5] = "Pellentesque vitae quam vehicula, rhoncus risus quis, dignissim ligula";

	//currentType = 0;

	for (int i = 0; i < TYPE_MAX; i++) {
		//cout << "DRAW" << endl;
		typeM[i].type.setup();
		//cout << "DRAW" << endl;
		//type[i]

	}
	setupType();

}

//--------------------------------------------------------------
void ofApp::update() {
	
	ofSetWindowTitle("Light Up The Room - FPS:"+ofToString(ofGetFrameRate()));
	cam.update();
	
//	camFBO.begin();
//	ofSetColor(255, 255, 255);
//	cam.draw(0,0);
//	camFBO.end();






//	ofFbo camFBO;
	//camFBO.allocate(ofGetWidth(), ofGetHeight());
	for (int i = 0; i < 4; i++) {
		camFBO[i].begin();
		ofClear(255, 255);
		ofPushMatrix();
		switch (i) {

		case 0:
			ofScale(1, 1);
			break;
		case 1:
			ofScale(-1, 1);
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

		camFBO[i].end();
	}





}
//--------------------------------------------------------------
void ofApp::draw(){
//	cam.draw(0,0);


	
	for (int i = 0; i < TYPE_MAX; i++) {

	}
	


	ofBackgroundGradient(ofColor(0, 0, 0), ofColor(100, 100, 100), OF_GRADIENT_LINEAR);
	ofSetColor(255, 255, 255);

		ofNoFill();
	for (int i = 0; i<gridRect.size(); i++) {
		//fboDraw[i].begin();
	
		//fboDraw[i].end();
		if (gridRectFilled[i]) {
			ofFill();
			ofSetColor(20, 120, 0);
		}
		else {
			ofNoFill();
			ofSetColor(40, 40, 40);
		}

		ofDrawRectangle(gridRect[i]);/// [i].draw(0, 0);
	}
ofNoFill();
	for (int i = 0; i < debugRect.size(); i++) {
		ofSetColor(190, 40, 40);
		ofDrawRectangle(debugRect[i]);
	}
	for (int i = 0; i < debugRect2.size(); i++) {
		ofSetColor(190, 255, 40);
		ofDrawRectangle(debugRect2[i]);
	}
	ofFill();


	ofSetColor(0, 0, 255);
//	ofVec2f pos(20, ofGetHeight() / 2);
	//font[0].draw(text,172, pos.x, pos.y);
//	font[1].draw(text, 172, pos.x, pos.y);
//	font[2].draw(text, 172, pos.x, pos.y);
//	font[3].draw(text, 172, pos.x, pos.y);


	for (int i = 0; i < TYPE_MAX; i++) {
		//cout << "DRAW" << endl;
	
		//cout << "DRAW" << endl;
		//type[i]

		if(typeM[i].type.isAlive()==false){

			ofRectangle tRect= font[0].getBBox(typeM[i].typeString, typeM[i].sizeType, typeM[i].posType.x, typeM[i].posType.y);
			//typeM[i].type.getRect(typeM[i].typeString, typeM[i].sizeType, typeM[i].posType);
		//	tRect.y += tRect.height;
			for (int j = 0; j < gridRect.size(); j++) {
				if (rectOverlap( gridRect[j], tRect)) {
					//rect2.inside(gridRect[i].x, gridRect[i].y)|| rect2.inside(gridRect[i].x+ gridRect[i].width, gridRect[i].y), rect2.inside(gridRect[i].x, gridRect[i].y + gridRect[i].height), rect2.inside(gridRect[i].x + gridRect[i].width, gridRect[i].y + gridRect[i].height)) {
					//cout << "inside" << endl;
					gridRectFilled[j] = false;
				}
			}
			typeM[i].typeString = "";
		}
	typeM[i].type.draw(camFBO, camFBO[0], typeM[i].typeString, typeM[i].sizeType, typeM[i].posType);
	}

	drawType();
}

//--------------------------------------------------------------
void ofApp::placeType() {


	//mType newType;



	string nTypeString = typeStringChoice[ (int)ofRandom(0, TYPE_MAX) ];
	
	int sizeText = typeSizeOptions[ofRandom(0, typeSizeOptions.size())];
	
	//cout << nTypeString << endl;

	ofRectangle rect= font[0].getBBox(nTypeString, sizeText, 0, 0);
		//typeM[currentType].type.getRect(nTypeString, sizeText, ofVec2f(0, 0));
	


	if (rect.width > ofGetWidth()) {
		sizeText = ((sizeText*ofGetWidth()) / rect.width)*0.95;
		cout << "scaled text, new size:" << sizeText<< endl;
		rect = font[0].getBBox(nTypeString, sizeText, 0,0);

			//typeM[currentType].type.getRect(nTypeString, sizeText, ofVec2f(0, 0));
	}



	bool isFree = false;
	int counterFindPlace = 0;
	ofRectangle rect2;
	ofVec2f posRect;
	while (isFree == false && counterFindPlace<10) {
		ofVec2f randomPos(ofRandom(0, ofGetWidth() - rect.width), ofRandom(0, ofGetHeight() - rect.height));
			counterFindPlace++;
			cout << randomPos << endl;
			posRect = randomPos;
			
			rect2 = font[0].getBBox(nTypeString, sizeText, posRect.x, posRect.y);

				
				
				//typeM[currentType].type.getRect(nTypeString, sizeText, posRect);//.set(randomPos.x, randomPos.y, rect.width, rect.height);// //


		//	rect2.y -= rect.height;

			debugRect2.push_back(rect2);
																					 //rect2.y += rect2.height;																	   //	rect2.y += rect2.height;
			cout << "new RECT2 attempt:" << rect2 << endl;
			bool atLeastOne = false;
			for (int i = 0; i < gridRect.size(); i++) {
	
				if (gridRectFilled[i]) {
				if (rectOverlap(rect2, gridRect[i]))//(rect2.inside(gridRect[i].x, gridRect[i].y) || rect2.inside(gridRect[i].x + gridRect[i].width, gridRect[i].y), rect2.inside(gridRect[i].x, gridRect[i].y + gridRect[i].height), rect2.inside(gridRect[i].x + gridRect[i].width, gridRect[i].y + gridRect[i].height))
					//(gridRect[i].inside(rect2.x,rect2.y) || gridRect[i].inside(rect2.x+rect2.width, rect2.y) || gridRect[i].inside(rect2.x, rect2.y+ rect2.height)|| gridRect[i].inside(rect2.x + rect2.width, rect2.y + rect2.height))
				{
					//isFree=false;
					atLeastOne = true;
					cout << " one is not free:" <<i<< endl;
				}}

				
			}
			//if none was used
			if (atLeastOne==false) {
				isFree = true;
				cout << "none were used break" << endl;
				break;
			}

			//counterFindPlace++;

	}
	cout << "afterwhile" << endl;
	if (isFree) {

		cout << "is free" << rect2 << endl;
		
		typeM[currentType].posType = posRect;// ofVec2f(rect2.x, rect2.y);
		typeM[currentType].sizeType = sizeText;
		typeM[currentType].typeString = nTypeString;
		typeM[currentType].type.reset(ofRandom(1000,3000));
		rect2 = font[0].getBBox(typeM[currentType].typeString, typeM[currentType].sizeType, typeM[currentType].posType.x, typeM[currentType].posType.y);
			
			//typeM[currentType].type.getRect(typeM[currentType].typeString, typeM[currentType].sizeType, typeM[currentType].posType);
		currentType++;
		if (currentType >= TYPE_MAX) {
			currentType = 0;
		}
		//newType.type.setup();
		//typeM.push_back(newType);
		//typeM[typeM.size()-1].type.setup();
		//cout << "push_back" << typeM.size()<< endl;

		debugRect.push_back(rect2);

		for (int i = 0; i < gridRectFilled.size(); i++) {
			if (rectOverlap(rect2, gridRect[i])) {
				//rect2.inside(gridRect[i].x, gridRect[i].y)|| rect2.inside(gridRect[i].x+ gridRect[i].width, gridRect[i].y), rect2.inside(gridRect[i].x, gridRect[i].y + gridRect[i].height), rect2.inside(gridRect[i].x + gridRect[i].width, gridRect[i].y + gridRect[i].height)) {
				//cout << "inside" << endl;
				gridRectFilled[i] = true;
			}
		}
	}

	if (counterFindPlace >= 10) {
	//DELETE A TEXT SPOT
	//TRY AGAIN
		cout << "counterFindPlace >= 10" << endl;
	//	placeType();
	}




}

bool ofApp::valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool ofApp::rectOverlap(ofRectangle A, ofRectangle B)
{
	bool xOverlap = valueInRange(A.x, B.x, B.x + B.width) ||
		valueInRange(B.x, A.x, A.x + A.width);

	bool yOverlap = valueInRange(A.y, B.y, B.y + B.height) ||
		valueInRange(B.y, A.y, A.y + A.height);

	return xOverlap && yOverlap;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	placeType();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void ofApp::setupType() {

	for (int i = 0; i < 4; i++) {

		fboMask[i].allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
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
}

//--------------------------------------------------------------
void ofApp::drawType() {


	for (int k = 0; k < TYPE_MAX ; k++) {









	for (int i = 0; i < 4; i++) {



		fboMask[i].begin();
		//ofScale(0.5, 0.5);
		ofClear(0, 0, 0, 255);
		//ofBackgroundGradient(ofColor(0, 0, 0), ofColor(0, 0, 0), OF_GRADIENT_LINEAR);	
		ofSetColor(255, 255, 255);
		ofNoFill();
		ofDrawRectangle(10, 10, ofGetWidth() - 20, ofGetHeight() - 20);
		ofFill();
		ofDrawCircle(10, 10, 20);
		ofDrawCircle(10, ofGetHeight() - 10, 20);
		ofDrawCircle(ofGetWidth() - 10, ofGetHeight() - 10, 20);

		ofPushMatrix();
		ofTranslate(typeM[k].posType);// + font[0].getBBox(text, size, 0, 0).height
		font[i + 1].draw(typeM[k].typeString, typeM[k].sizeType, 0, 0);//pos.x,pos.y
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


		camFBO[i].draw(0, 0);

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
	ofTranslate(typeM[k].posType);//+ font[0].getBBox(text, size, 0, 0).height
							  //ofVec2f pos(20, ofGetHeight() / 2);
	ofSetColor(0, 0, 0);
	font[0].draw(typeM[k].typeString, typeM[k].sizeType, 0, 0);
	ofNoFill();
	ofSetColor(255, 255, 255);
	///if (active) { ofSetColor(255, 0, 0); }
	ofDrawRectangle(font[0].getBBox(typeM[k].typeString, typeM[k].sizeType, 0, 0));
	ofPopMatrix();
	ofFill();






}

}
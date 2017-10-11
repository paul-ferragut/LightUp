#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//for (int i = 0; i < TYPE_MAX; i++) {

	//	type[i].setup();

	//}

	gui.setup("GUI", "settings.xml");

	gui.add(durationText.setup("duration text", 75, 75, 600));

	gui.add(durationVerticalColorTransition.setup("duration color transitions", 1000, 500, 15000));
	timerVerticalColor = 0;

	gui.add(durationStayBright.setup("duration stayBright", 100, 1,800));
	timerStayBright = 0;

	gui.add(sentimentDecrement.setup("sentiment Decrement", 0.5, 0.01, 5.0));
	gui.add(sentimentIncrement.setup("sentiment Increment", 0.5, 0.01,150.0));
	gui.add(debug.setup("debug", false));
	gui.add(useCam.setup("use cam reflection", false));
	gui.add(bgDebug.setup("bgDebug", false));


	gui.loadFromFile("settings.xml");
	gui.setPosition(20, 600);
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



	// Load test media.
	pingPlayer.load("media/ping.wav");
	pongPlayer.load("media/pong.wav");

	ofx::HTTP::JSONRPCServerSettings settings;
	settings.setPort(8197);

	// Initialize the server.
	server.setup(settings);


	// Register RPC methods.
	server.registerMethod("get-text",
		"Returns a random chunk of text to the client.",
		this,
		&ofApp::getText);

	server.registerMethod("set-text",
		"Sets text from the user.",
		this,
		&ofApp::setText);

	server.registerMethod("set-text-speech",
		"Sets speech text from the user.",
		this,
		&ofApp::setTextSpeech);


	server.registerMethod("ping",
		"Send a JSONRPC Ping Notification",
		this,
		&ofApp::ping);

	server.registerMethod("pong",
		"Send a JSONRPC Pong Notification",
		this,
		&ofApp::pong);

	// Start the server.
	server.start();
	//cout << "start" << endl;
	// Launch a browser with the address of the server.
	ofLaunchBrowser(server.url());

	 

	colorPaletteNegative.push_back(ofColor(168, 62, 93));
	colorPaletteNegative.push_back(ofColor(232, 35, 92));
	colorPaletteNegative.push_back(ofColor(75, 58, 79));
	colorPaletteNegative.push_back(ofColor(105, 9, 179));
	colorPaletteNegative.push_back(ofColor(224, 31, 31));
	colorPaletteNegative.push_back(ofColor(69, 9, 9));
	colorPaletteNegative.push_back(ofColor(153, 153, 124));
	colorPaletteNegative.push_back(ofColor(255, 59, 88));
	colorPaletteNegative.push_back(ofColor(79, 47, 50));
	colorPaletteNegative.push_back(ofColor(220, 42, 66));
	colorPaletteNegative.push_back(ofColor(177, 108, 103));
	colorPaletteNegative.push_back(ofColor(152, 134, 132));
	colorPaletteNegative.push_back(ofColor(201, 154, 134));

	colorPalettePositive.push_back(ofColor(105, 210, 231));
	colorPalettePositive.push_back(ofColor(167, 219, 216));
	colorPalettePositive.push_back(ofColor(250, 105, 0));
	colorPalettePositive.push_back(ofColor(224, 228, 204));
	colorPalettePositive.push_back(ofColor(145, 207, 202));
	colorPalettePositive.push_back(ofColor(239, 189, 192));
	colorPalettePositive.push_back(ofColor(92, 172, 196));
	colorPalettePositive.push_back(ofColor(140, 209, 157));
	colorPalettePositive.push_back(ofColor(206, 232, 121));
	colorPalettePositive.push_back(ofColor(252, 182, 83));
	colorPalettePositive.push_back(ofColor(255, 82, 84));
	colorPalettePositive.push_back(ofColor(255, 245, 0));
	colorPalettePositive.push_back(ofColor(255, 162, 0));
	colorPalettePositive.push_back(ofColor(57, 142, 182));
	colorPalettePositive.push_back(ofColor(34, 104, 136));



}

//--------------------------------------------------------------
void ofApp::update() {
	
	ofSetWindowTitle("Light Up The Room - FPS:"+ofToString(ofGetFrameRate()));
	if (useCam) {
	cam.update();
	}
	
	

	ofSetFrameRate(60);
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
		
		if (useCam) {
			ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
		}
		

		switch (i) {

		case 0:
			ofBackground(typoColor[0]);
			ofScale(1, 1);
			break;
		case 1:
			ofBackground(typoColor[1]);
			ofScale(-1, 1);
			ofTranslate(-ofGetWidth(), 0);
			break;
		case 2:
			ofBackground(typoColor[2]);
			ofScale(-1, -1);
			ofTranslate(-ofGetWidth(), -ofGetHeight());
			break;
		case 3:
			ofBackground(typoColor[3]);
			ofScale(1, -1);
			ofTranslate(0, -ofGetHeight());
			break;
		}

		
		if (useCam) {
		cam.draw(0, 0, ofGetWidth(), ofGetHeight());
		ofDisableBlendMode();
}
		ofPopMatrix();

		camFBO[i].end();
	}



	updateCol();

	if (prevText != userText) {
		cout << userText << endl;
		if (prevText == "") {
			cout << "NEW SENTENCE" << endl;
		}
		else {
			string newWord;
			vector<string>prevWords =ofSplitString(prevText," ",true,true);
			vector<string>newWords= ofSplitString(userText, " ", true, true);


			if (prevWords.size() == newWords.size() && prevWords.size() > 0){
				cout << "REPLACED WORD: " << newWords[newWords.size() - 1] << "  .prev word: "<< prevWords[prevWords.size() - 1]<<endl;
				typeM[currentType].typeString = newWords[newWords.size() -1];
			}
			else if(newWords.size()>prevWords.size()){
				cout << "NEW WORD" << newWords[newWords.size()-1] << endl;
				placeType(newWords[newWords.size()-1],ofRandom(1.0,1.5));
			}
		}
	}

	prevText = userText;

}

void ofApp::updateCol() {

	if (ofGetElapsedTimeMillis() - timerStayBright > durationStayBright) {
		timerStayBright = ofGetElapsedTimeMillis();
		currentLight -= (1.0*(sentimentDecrement))*ofMap(averageLight,120,255,1.0,5.0);
		if (currentLight <= 0) {
			currentLight = 0;
		}
	}

	
	if (ofGetElapsedTimeMillis() - timerVerticalColor > durationVerticalColorTransition) {
		timerVerticalColor = ofGetElapsedTimeMillis();	
		for (int i = 0; i < 4; i++) {
			prevColor[i] = currentColor[i];
			if (i == 0 || i == 1) { targetColor[i] = colorPaletteNegative[(int)ofRandom(0, colorPaletteNegative.size() - 1)]; }
			if (i == 2 || i == 3) { targetColor[i] = colorPalettePositive[(int)ofRandom(0, colorPalettePositive.size() - 1)]; }
		}
	}

	float verticalPosColor = ofMap(ofGetElapsedTimeMillis() - timerVerticalColor, 0, durationVerticalColorTransition, 0.0, 1.0, true);
	for (int i = 0; i < 4; i++) {
		//currentColor[i] = prevColor[i].lerp(targetColor[i], verticalPosColor);
		currentColor[i] = prevColor[i].getLerped(targetColor[i], verticalPosColor);
	}
	

	historyLight.push_back(currentLight);
	if (historyLight.size() > 10) {
		historyLight.erase(historyLight.begin());
	}
	float averagedHistoryVal = 0;
	for (int i = 0; i < historyLight.size(); i++) {
		averagedHistoryVal += historyLight[i];
	}
	averageLight = averagedHistoryVal / historyLight.size();

	float currentColSentimentMap = ofMap(averageLight, 100, 155, 0.0, 1.0, true);
		currentColor[4] = currentColor[0].getLerped(currentColor[2], currentColSentimentMap);
		currentColor[5] = currentColor[1].getLerped(currentColor[3], currentColSentimentMap);



		mappedBrightnessLED=ofMap(averageLight,0,200,0,255);
		mappedBrightnessTypo=ofMap(averageLight,0,255,100,255);


		ledColor[0] = currentColor[4];
		ledColor[0].setBrightness(mappedBrightnessLED);
		ledColor[1] = currentColor[5];
		ledColor[1].setBrightness(mappedBrightnessLED);

		//1 left - 2 right - 3 top - 4 bottom
		typoColor[0] = currentColor[4];
		typoColor[0].setBrightness(mappedBrightnessTypo-50);
		typoColor[1] = currentColor[5];
		typoColor[1].setBrightness(mappedBrightnessTypo);
		typoColor[2] = currentColor[4];
		typoColor[2].setBrightness(mappedBrightnessTypo);
		typoColor[3] = currentColor[5];
		typoColor[3].setBrightness(mappedBrightnessTypo-50);


}

//--------------------------------------------------------------
void ofApp::draw(){
//	cam.draw(0,0);
	ofBackground(ofColor(0, 0, 0));


	if (bgDebug) {
	
		ofBackgroundGradient(ledColor[0], ledColor[1], OF_GRADIENT_LINEAR);

	}
	
	for (int i = 0; i < TYPE_MAX; i++) {

	}
	
	
#ifdef DEBUG
	if (debug) {
		ofBackgroundGradient(ofColor(0, 0, 0), ofColor(100, 100, 100), OF_GRADIENT_LINEAR);
		ofSetColor(255, 255, 255);

		ofNoFill();
		for (int i = 0; i < gridRect.size(); i++) {
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
		
	}
#endif // DEBUG

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
	typeM[i].type.update();//(camFBO, camFBO[0], typeM[i].typeString, typeM[i].sizeType, typeM[i].posType // actually just an update
	}

	drawType();

	ofSetColor(255, 255, 255,255);
	if (debug) {
	ofDrawBitmapStringHighlight("sentiment level:" + ofToString(lastSentiment), 20, 50);
	ofDrawBitmapStringHighlight("user speech:" + userText, 20, 65);
	ofDrawBitmapStringHighlight("current light:" + ofToString(currentLight), 20, 80);


	ofSetColor(currentColor[0]);
	ofDrawRectangle(300, 20, 100, 100);
	ofSetColor(currentColor[1]);
	ofDrawRectangle(300, 120, 100, 100);
	ofDrawBitmapStringHighlight("negative" , 300, 20);
	/*
	ofxColorGradient<ofColor> gradientN;
	gradientN.addColor(currentColor[0]);
	gradientN.addColor(currentColor[1]);
	gradientN.drawDebug(400, 20, 100, 200, 25);
	*/

	ofSetColor(currentColor[2]);
	ofDrawRectangle(400, 20, 100, 100);
	ofSetColor(currentColor[3]);
	ofDrawRectangle(400, 120, 100, 100);
	ofDrawBitmapStringHighlight("positive", 400, 20);
	/*
	ofxColorGradient<ofColor> gradientP;
	gradientP.addColor(currentColor[2]);
	gradientP.addColor(currentColor[3]);
	gradientP.drawDebug(600, 20, 100, 200, 25);
	*/

	ofSetColor(currentLight, currentLight);
	ofDrawRectangle(500, 20, 100, 100);
	ofDrawBitmapStringHighlight("Brightness", 500, 20);
	ofSetColor(averageLight, averageLight);
	ofDrawRectangle(500, 120, 100, 100);
	ofDrawBitmapStringHighlight("Averaged", 500,120);


	ofSetColor(currentColor[4]);
	ofDrawRectangle(600, 20, 100, 100);
	ofSetColor(currentColor[5]);
	ofDrawRectangle(600, 120, 100, 100);
	ofDrawBitmapStringHighlight("current", 600, 20);


	ofSetColor(ledColor[0]);
	ofDrawRectangle(700, 20, 100, 100);
	ofSetColor(ledColor[1]);
	ofDrawRectangle(700, 120, 100, 100);
	ofDrawBitmapStringHighlight("LED Color", 700, 20);

	}

	ofSetColor(255, 255, 255, 255);
	gui.draw();
	

}

void ofApp::exit()
{
	gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::placeType(string inputType, float durationSpecial) {


	//mType newType;

	cout << "Place type" << inputType << endl;
	if (inputType != "") {
		string nTypeString = inputType;// typeStringChoice[(int)ofRandom(0, TYPE_MAX)];

		int sizeText = typeSizeOptions[ofRandom(0, typeSizeOptions.size())];

		//cout << nTypeString << endl;

		ofRectangle rect = font[0].getBBox(nTypeString, sizeText, 0, 0);
		//typeM[currentType].type.getRect(nTypeString, sizeText, ofVec2f(0, 0));



		if (rect.width > ofGetWidth()) {
			sizeText = ((sizeText*ofGetWidth()) / rect.width)*0.95;
			cout << "scaled text, new size:" << sizeText << endl;
			rect = font[0].getBBox(nTypeString, sizeText, 0, 0);
			cout << "new size passed:" << sizeText << endl;
			//typeM[currentType].type.getRect(nTypeString, sizeText, ofVec2f(0, 0));
		}



		bool isFree = false;
		int counterFindPlace = 0;
		ofRectangle rect2;
		ofVec2f posRect;
		while (isFree == false && counterFindPlace < 10) {
			ofVec2f randomPos(ofRandom(0, ofGetWidth() - rect.width), ofRandom(rect.height, ofGetHeight()));
			counterFindPlace++;
			cout << randomPos << endl;
			posRect = randomPos;

			rect2 = font[0].getBBox(nTypeString, sizeText, posRect.x, posRect.y);



			//typeM[currentType].type.getRect(nTypeString, sizeText, posRect);//.set(randomPos.x, randomPos.y, rect.width, rect.height);// //


	//	rect2.y -= rect.height;
#ifdef DEBUG
			debugRect2.push_back(rect2);
#endif // DEBUG


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
						cout << " one is not free:" << i << endl;
					}
				}
			}
			//if none was used
			if (atLeastOne == false) {
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
			
			if (durationSpecial != 1) {
				typeM[currentType].type.reset(durationText*durationSpecial); //durationText*durationSpecial;
			}
			else {
				typeM[currentType].type.reset((durationText* ofRandom(5.0,9.0)));
			}
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
#ifdef DEBUG
			debugRect.push_back(rect2);
#endif // DEBUG



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
	//placeType();
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
	float spacingChar = 0.2;
	/*
	font1 = new ofxFontStash;
	font1->setup("fonts/Detroit11BevelOne.ttf", 1.0, 1024, false, 8, 1.5);//Vera.ttf
	font1->setCharacterSpacing(spacingChar);

	font2 = new ofxFontStash;
	font2->setup("fonts/Detroit06PrismLeft.ttf", 1.0, 1024, false, 8, 1.5);//Vera.ttf
	font2->setCharacterSpacing(spacingChar);

	font3 = new ofxFontStash;
	font3->setup("fonts/Detroit07PrismRight.ttf", 1.0, 1024, false, 8, 1.5);//Vera.ttf
	font3->setCharacterSpacing(spacingChar);

	font4 = new ofxFontStash;
	font4->setup("fonts/Detroit08PrismTop.ttf", 1.0, 1024, false, 8, 1.5);//Vera.ttf
	font4->setCharacterSpacing(spacingChar);

	font5 = new ofxFontStash;
	font5->setup("fonts/Detroit09PrismBottom.ttf", 1.0, 1024, false, 8, 1.5);//Vera.ttf
	font5->setCharacterSpacing(spacingChar);
	*/
	
	font[0].setup("fonts/Detroit11BevelOne.ttf",1.0,2048,false,0,1.0);// , 1.0, 1024, false, 8, 1.5);//Vera.ttf

	//font[1].setup("fonts/Detroit06PrismLeft.ttf", 1.0, 2048, false, 0, 1.0);//, 1.0, 1024, false, 8, 1.5);
	font[1].setup("fonts/Detroit05Base.ttf", 1.0, 2048, false, 0, 1.0);//, 1.0, 1024, false, 8, 1.5);

	font[2].setup("fonts/Detroit07PrismRight.ttf", 1.0, 2048, false, 0, 1.0);//, 1.0, 1024, false, 8, 1.5);

	font[3].setup("fonts/Detroit08PrismTop.ttf", 1.0, 2048, false, 0, 1.0);//, 1.0, 1024, false, 8, 1.5);

	font[4].setup("fonts/Detroit09PrismBottom.ttf", 1.0, 2048, false, 0, 1.0);//, 1.0, 1024, false, 8, 1.5);

	for (int i = 0; i < 5; i++) {
		font[i].setCharacterSpacing(spacingChar);
	}
	

	mask.load("mask");
	cout << "SETUP" << endl;
}

//--------------------------------------------------------------
void ofApp::drawType() {

	for (int i = 0; i < 5; i++) {
		
		font[i].beginBatch();
	}

		for (int k = 0; k < TYPE_MAX ; k++) {

			if (typeM[k].typeString != "") {

				for (int i = 0; i < 4; i++) {

					fboMask[i].begin();
					//ofScale(0.5, 0.5);
					ofClear(0, 0, 0, 255);
					//ofBackgroundGradient(ofColor(0, 0, 0), ofColor(0, 0, 0), OF_GRADIENT_LINEAR);	
					ofSetColor(255, 255, 255);
#ifdef DEBUG
					ofNoFill();
					ofDrawRectangle(10, 10, ofGetWidth() - 20, ofGetHeight() - 20);
					ofFill();
					ofDrawCircle(10, 10, 20);
					ofDrawCircle(10, ofGetHeight() - 10, 20);
					ofDrawCircle(ofGetWidth() - 10, ofGetHeight() - 10, 20);
#endif // DEBUG

					ofPushMatrix();
					ofTranslate(typeM[k].posType);// + font[0].getBBox(text, size, 0, 0).height

					font[i + 1].drawBatch(typeM[k].typeString, typeM[k].sizeType, 0, 0);//pos.x,pos.y

					ofPopMatrix();
					fboMask[i].end();



					fboDraw[i].begin();
					ofClear(0, 0);
					//ofClearAlpha();
					ofSetColor(255, 255, 255);

					mask.begin();
					mask.setUniformTexture("maskTex", fboMask[i].getTexture(), 1);
					ofFill();

					camFBO[i].draw(0, 0);

					mask.end();
					
					fboDraw[i].end();

				}

				ofSetColor(255, 255, 255);
				for (int i = 0; i < 4; i++) {
					//fboDraw[i].begin();

					//fboDraw[i].end();
					ofSetColor(255, typeM[k].type.opacityCounter[i]);
					fboDraw[i].draw(0, 0);
				}
				ofPushMatrix();
				ofTranslate(typeM[k].posType);//+ font[0].getBBox(text, size, 0, 0).height
										  //ofVec2f pos(20, ofGetHeight() / 2);
				ofSetColor(0, 0, 0);
				//font[0].drawBatch(typeM[k].typeString, typeM[k].sizeType, 0, 0);
				ofNoFill();
				ofSetColor(255, 255, 255);
				///if (active) { ofSetColor(255, 0, 0); }
				if (debug) {
					ofDrawRectangle(font[0].getBBox(typeM[k].typeString, typeM[k].sizeType, 0, 0));
				}

				ofPopMatrix();
				ofFill();
			}
	}

		for (int i = 0; i < 5; i++) {
			font[i].endBatch();
		}
}

void ofApp::ping()
{	if (userText.size() > 1) {
	
	pingPlayer.play();
	ofLogVerbose("ofApp::ping") << "Ping'd";
	//	sendToThread = true;


	//cout << thread.exec("gcloud ml language analyze-sentiment --content=\"suck my dick\"") << endl;

	//	thread.lock();

	// copy image
	//myImage = thread.image;
	//cout << thread. << endl
	// done with the resource
	//	thread.update();
	//cout << thread.getOutput() << endl;
	//	thread.setInput(userText);

	//thread.unlock();
	//cout << "ping" << endl;

		placeType(userText);

	string inputChar = "gcloud ml language analyze-sentiment --content=\"" + userText + "\"";
	//std::vector<char> cstr(inputChar.c_str(), inputChar.c_str() + inputChar.size() + 1);
	char *cstr = &inputChar[0u];
	string cmd = thread.exec(cstr);   // create the command
	cout << cmd << endl;
	//system(cmd.c_str());
	//string read = ofSystem(cmd.c_str());
	//cout << "read:" << read << endl;
	vector<string>s = ofSplitString(cmd,":",true,true);
	if (s.size() > 3) {
		vector<string>ss = ofSplitString(s[3], "}", true, true);
		if (ss.size() >0) {
			cout << "sentiment value" << ss[0] << endl;
			lastSentiment = ofToFloat(ss[0]);
			currentLight += lastSentiment*sentimentIncrement;
			if (currentLight < 0) {
				currentLight = 0;
			}
			if (currentLight > 255) {
				currentLight = 255;
			}
		}
	}


	}
	//cout << "end ping" << endl;
	userText = "";
	//cout << "change color bg "<< endl;
	//targetCol.r = ofLerp(c[0].r, c[1].r, ofMap(ofToFloat(ss[0]), -1.0, 1.0, 0.0, 1.0, true));
	//targetCol.g = ofLerp(c[0].g, c[1].g, ofMap(ofToFloat(ss[0]), -1.0, 1.0, 0.0, 1.0, true));
	//targetCol.b = ofLerp(c[0].b, c[1].b, ofMap(ofToFloat(ss[0]), -1.0, 1.0, 0.0, 1.0, true));
	
}


void ofApp::pong()
{
	pongPlayer.play();
	ofLogVerbose("ofApp::pong") << "Pong'd";

	
	//thread.callCommand("gcloud ml language analyze-sentiment --content=\"suck my dick\"");
}


void ofApp::getText(ofx::JSONRPC::MethodArgs& args)
{
	// Set the result equal to the substring.
	//   args.result = getRandomText();
	//   ofLogVerbose("ofApp::getText") << args.result.dump(4);
}


void ofApp::setText(ofx::JSONRPC::MethodArgs& args)
{
	// Set the user text.
	setUserText(args.params);
	ofLogVerbose("ofApp::setText") << args.params.dump(4);
}


void ofApp::setTextSpeech(ofx::JSONRPC::MethodArgs& args)
{
	// Set the user text.
	setUserTextSpeech(args.params);
	ofLogVerbose("ofApp::setTextSpeech") << args.params.dump(4);
}

std::string ofApp::getUserText() const
{
	std::unique_lock<std::mutex> lock(mutex);
	return userText;
}


void ofApp::setUserText(const std::string& text)
{
	std::unique_lock<std::mutex> lock(mutex);
	userText = text;
}


void ofApp::setUserTextSpeech(const std::string& text)
{
	std::unique_lock<std::mutex> lock(mutex);
	userText = text;
}


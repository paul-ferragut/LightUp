#pragma once

#include "ofMain.h"
#include "mirrorType.h"
#include "threadedObject.h"

#define GRID_HEIGHT 24
#define TYPE_MAX 6

struct mType {
	mirrorType type;
	string typeString;
	ofVec2f posType;
	int sizeType;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void setupType();
		void drawType();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		bool valueInRange(int value, int min, int max);
		bool rectOverlap(ofRectangle A, ofRectangle B);

		ofVideoGrabber cam;
		vector<ofRectangle>gridRect;
		vector<bool>gridRectFilled;

		vector<int>typeSizeOptions;



		//int currentType;

	//	vector<int>typeSizeOptions;
	//	int typeSizeOptions[5] = { 72, 90, 122,180,220};

		void placeType();

		vector<ofFbo>camFBO;


		vector<ofRectangle>debugRect;

		vector<ofRectangle>debugRect2;
		mType typeM[TYPE_MAX];

		string typeStringChoice[TYPE_MAX];

		int currentType;


		ofxFontStash  font[5];
		ofFbo fboMask[4];
		ofFbo fboDraw[4];
		//	string text;

		ofShader mask;
		ofRectangle rectText;



};


#pragma once

#include "ofMain.h"
#include "mirrorType.h"

#define GRID_HEIGHT 24
#define TYPE_MAX 6


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		mirrorType type[TYPE_MAX];
		string typeString[TYPE_MAX];
		ofVec2f posType[TYPE_MAX];
		int sizeType[TYPE_MAX];

		int currentType;

		vector<int>typeSizeOptions;
	//	int typeSizeOptions[5] = { 72, 90, 122,180,220};

		void placeType();

		vector<ofFbo>camFBO;


		vector<ofRectangle>debugRect;

};

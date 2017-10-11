#pragma once

#include "ofMain.h"
#include "mirrorType.h"
#include "threadedObject.h"
#include "ofxColorGradient.h"

#include "ofxJSONRPC.h"
#include "ofxGui.h"



#include "ofxFontStash.h"


//#define DEBUG

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
		void exit();

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


		/*
		ofxFontStash  *font1;
		ofxFontStash  *font2;
		ofxFontStash  *font3;
		ofxFontStash  *font4;
		ofxFontStash  *font5;*/
		//ridiculous make an array

		void placeType(string inputType,float durationSpecial=1.0);

		vector<ofFbo>camFBO;

#ifdef DEBUG
		vector<ofRectangle>debugRect;
		vector<ofRectangle>debugRect2;
#endif // DEBUG

	
		mType typeM[TYPE_MAX];

		string typeStringChoice[TYPE_MAX];

		int currentType;


		ofxFontStash  font[5];
		ofFbo fboMask[4];
		ofFbo fboDraw[4];
		//	string text;

		ofShader mask;
		ofRectangle rectText;

		ofxPanel gui;

		// Registered methods.
		void getText(ofx::JSONRPC::MethodArgs& args);
		void setText(ofx::JSONRPC::MethodArgs& args);

		void setTextSpeech(ofx::JSONRPC::MethodArgs& args);

		// Register a no-argument notification method.
		void ping();

		// Register a no-argument notification method.
		void pong();

		/// \todo is ofSoundPlayer thread-safe?
		ofSoundPlayer pingPlayer;
		ofSoundPlayer pongPlayer;

		/// \brief The server that handles the JSONRPC requests.
		ofx::HTTP::JSONRPCServer server;


		/// \brief Get the user text in a thread-safe way.
		/// \returns The user text.
		std::string getUserText() const;

		/// \brief Set the user text in a thread-safe way.
		/// \param text the user text to set.
		void setUserText(const std::string& text);


		void setUserTextSpeech(const std::string& text);

		vector<ofColor>colorPaletteNegative;
		
		vector<ofColor>colorPalettePositive;

		ofColor prevColor[4];
		ofColor targetColor[4];
		ofColor currentColor[6];
	//	ofTrueTypeFont font;
		ofxFloatSlider durationText;
		
		ofxFloatSlider durationStayBright;
		float timerStayBright;

		ofxFloatSlider durationVerticalColorTransition;
		float timerVerticalColor;

		ofxFloatSlider sentimentDecrement;
		ofxFloatSlider sentimentIncrement;
		ofxToggle debug;
		ofxToggle useCam;
		ofxToggle bgDebug;
		//ofxColorGradient<ofColor> gradient;
		float lastSentiment;
		float currentLight;
		float averageLight;
		vector<float>historyLight;
		float targetLight;

		void updateCol();

		SysCommand thread;

		string prevText;

		float mappedBrightnessLED;
		float mappedBrightnessTypo;

		ofColor typoColor[4];
		ofColor ledColor[2];

private:
	// A custom logging channel to mirror all log messages to the web clients.
	// WebSocketLoggerChannel::SharedPtr loggerChannel;

	// This piece of text might be modified by multiple client threads.
	// Thus we must use a mutex to protect it during multi-threaded access.
	//   std::string ipsum;

	// This piece of text might be modified by multiple client threads.
	// Thus we must use a mutex to protect it during multi-threaded access.
	std::string userText;

	// We use a mutex to protect any variables that can be
	// modified by multiple clients.  In our case, userText must be protected.
	// We mark the mutex as mutable so that it can be used in const functions.
	mutable std::mutex mutex;
};


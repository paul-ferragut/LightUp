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



		ofxIntSlider rateComLed;
		ofSerial serial;

		bool censorCheck(string inputS);

		vector<string> swear = { "anal", "anus", "arse", "ass",  "asses", "assfucker", "assfukka", "asshole", "assholes", "asswhole", "ballbag", "balls",  "bastard", 
			"beastiality", "bellend", "bestial", "bestiality", "biatch", "bitch", "bitcher", "bitchers", "bitches", "bitchin", "bitching", "bloody", "blowjob", "blowjobs",
			 "bollock",  "boner", "boob", "boobs",  "breasts",  "bum", "butt", "butthole", "buttmuch", "buttplug", "clit", "clitoris", "clits", "cnut", "cock", "cockface", 
			"cockhead", "cocks","cocksucked", "cocksucker", "cocksucking", "cocksucks", "crap", "cum",  "cumming", "cums", "cumshot", "cunilingus", "cunillingus", "cunnilingus",
			"cunt", "cuntlick", "cuntlicker", "cuntlicking", "cunts","cyberfuck", "cyberfucked", "cyberfucker", "cyberfuckers", "cyberfucking", "damn", "dick", "dickhead", 
			"dildo", "dildos", "ejaculate", "ejaculated", "ejaculates", "ejaculating", "ejaculatings", "ejaculation", "fag",  "faggot", "faggs", "fagot", "fagots", "fags",
			"fanny", "fannyflaps", "fannyfucker", "fatass", "fellate", "fingerfuck", 
			"fingerfucked", "fingerfucker", "fingerfuckers", "fingerfucking", "fingerfucks", "fistfuck", "fistfucked", "fistfucker", "fistfuckers", "fistfucking",
			"fistfuckings", "fistfucks", "flange",  "fuck", "fucka", "fucked", "fucker", "fuckers", "fuckhead", "fuckheads", "fuckin", "fucking", "fuckings", 
			"fuckme", "fucks", "fuckwhit", "fuckwit", "gangbang", "gangbanged", "gangbangs", "gaylord", "homo", "horniest", "horny", "jerk-off", "jism", 
			"jizz", "knob", "knobead", "knobed", "knobend", "knobhead", "knobjocky", "knobjokey",  "labia", "lust", "lusting",
			"masochist", "masturbate", "mo-fo", "mof0", "mofo", "mothafuck", "mothafucka", "mothafuckas", "mothafuckaz", "mothafucked", "mothafucker", "mothafuckers",
			"mothafuckin", "mothafucking", "mothafuckings", "mothafucks", "mother fucker", "motherfuck", "motherfucked", "motherfucker", "motherfuckers", "motherfuckin",
			"motherfucking", "motherfuckings", "motherfuckka", "motherfucks", "muff",
			"nazi",  "nigga", "niggah", "niggas", "niggaz", "nigger", "niggers", "nob", "nob jokey", "nobhead", "nobjocky", "nobjokey", "numbnuts", "nutsack", "orgasim", 
			"orgasims", "orgasm", "orgasms","pawn", "pecker", "penis", "piss", "pissed", "pisser", "pissers", "pisses", "pissflaps", "pissin", "pissing", "pissoff",  
			"porn", "porno", "pornography", "pornos", "prick", "pricks", "pube", "pusse",  "pussies", "pussy", "pussys", "rectum", 
			"sadist", "schlong", "screwing",  "scrotum", "semen", "sex", "shag", "shagger", "shaggin", "shagging", "shemale", "shi+", "shit", "shitdick", "shite", 
			"shited", "shitey", "shitfuck", "shitfull", "shithead", "shiting", "shitings", "shits", "shitted", "shitter", "shitters", "shitting", "shittings",
			"shitty", "skank", "slut", "sluts", "smut","spunk",  "testical", "testicle", "tit", "titfuck", "tits", "tittiefucker", "titties", "tittyfuck", 
			"tittywank", "titwank", "tosser", "turd", "twat", "vagina", "viagra", "vulva", "wang", "wank", "wanker", "wanky", "whore",
			"willies", "willy", "xrated" };

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


/*

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN1 6
#define PIN2 7

#define INPUT_SIZE 35

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(420, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(120, PIN2, NEO_GRB + NEO_KHZ800);

int col[6];

void setup() {


Serial.begin(115200);        // connect to the serial port



strip1.begin();
strip1.show(); // Initialize all pixels to 'off'

strip2.begin();
strip2.show(); // Initialize all pixels to 'off'


for(int i=0;i<6;i++){
col[i]=0;
}
}

void loop () {
// read the serial port

if (Serial.available()==INPUT_SIZE) {
// Get next command from Serial (add 1 for final 0)
char input[INPUT_SIZE + 1];
byte size = Serial.readBytes(input, INPUT_SIZE);
// Add the final 0 to end the C string
input[size] = 0;

// Read each command pair
char* command = strtok(input, "&");
while (command != 0)
{
// Split the command in two values
char* separator = strchr(command, ':');
if (separator != 0)
{
// Actually split the string in 2: replace ':' with 0
*separator = 0;
int iD = atoi(command);
++separator;
int position = atoi(separator);

// Do something with servoId and position
col[iD]=position;
}
// Find the next command in input string
command = strtok(0, "&");
}

}else{
serialFlush();
}

for (uint16_t i=0; i < strip1.numPixels(); i++) {
strip1.setPixelColor(i, strip1.Color(col[0],col[1],col[2]));        //turn every third pixel off
}

for (uint16_t i=0; i < strip2.numPixels(); i++) {
strip2.setPixelColor(i, strip2.Color(col[3],col[4],col[5]));        //turn every third pixel off
}

strip1.show();
strip2.show();
delay(20);
}



void serialFlush(){
while(Serial.available() > 0) {
char t = Serial.read();
}
}

*/
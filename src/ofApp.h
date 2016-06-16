#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxInputField.h"
#include "ofxCustomButton.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        void mousePressed(ofMouseEventArgs &args);
        void mouseReleased(ofMouseEventArgs &args);

        void nthFieldChanged(int &v);
        void extensionFieldChanged(string &v);
    
        ofxIntField nthField;
        ofxTextField extensionField;
        ofxCustomButton sourceButton;
        ofxCustomButton destinationButton;
        ofxCustomButton copyButton;
    
        string status;
    
        int nth;
        string extension;
        string source;
        string destination;
        
        void chooseSource();
        void chooseDestination();
        void copy();
    
};

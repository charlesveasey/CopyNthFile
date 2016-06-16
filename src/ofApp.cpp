#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    status = "status";
    extension = "none";
    nth = 1;
    
    ofxGuiSetDefaultWidth(780);
    ofxGuiSetDefaultHeight(30);
    
    nthField.setup("Nth File", 1, 1, 10000);
    nthField.setPosition(10, 10);
    nthField.addListener(this, &ofApp::nthFieldChanged);

    extensionField.setup("Extension Filter", extension);
    extensionField.setPosition(10, 45);
    extensionField.addListener(this, &ofApp::extensionFieldChanged);
    
    sourceButton.setup("Source Folder", "");
    sourceButton.setPosition(10, 80);

    destinationButton.setup("Destination Folder", "");
    destinationButton.setPosition(10, 115);

    copyButton.setup("                                                                                      ----> COPY","");
    copyButton.setPosition(10, 150);
    copyButton.setBackgroundColor(ofColor(80,0,0));
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor(190));
    nthField.draw();
    extensionField.draw();
    sourceButton.draw();
    destinationButton.draw();
    copyButton.draw();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(status, 10, 205);
}

//--------------------------------------------------------------
void ofApp::nthFieldChanged(int &v){
    nth = v;
    status = "nth file set: " + ofToString(nth);
}

//--------------------------------------------------------------
void ofApp::extensionFieldChanged(string &v){
    extension = v;
    status = "file extension filter set: " + extension;
}

//--------------------------------------------------------------
void ofApp::mousePressed(ofMouseEventArgs &args){
    if(copyButton.mouseReleased(args)){
        copyButton.setBackgroundColor(ofColor(80,0,80));
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(ofMouseEventArgs &args){
    if(sourceButton.mouseReleased(args)){
        chooseSource();
    }
    else if(destinationButton.mouseReleased(args)){
        chooseDestination();
    }
    else if(copyButton.mouseReleased(args)){
        copy();
        copyButton.setBackgroundColor(ofColor(80,0,0));
    }
}

//--------------------------------------------------------------
void ofApp::chooseSource(){
    ofFileDialogResult result = ofSystemLoadDialog("Select source folder", true, source);
    if (result.bSuccess){
        source = result.filePath;
        sourceButton.setup("Source Folder:         " + source,"");
        status = "source set: " + source;
    }
    else
        status = "source folder invalid";
}

//--------------------------------------------------------------
void ofApp::chooseDestination(){
    ofFileDialogResult result = ofSystemLoadDialog("Select destination folder", true, destination);
    if (result.bSuccess){
        destination = result.filePath;
        destinationButton.setup("Destination Folder:    " + destination,"");
        status = "destination set: " + destination;
    }
    else
        status = "destination folder invalid";
}

//--------------------------------------------------------------
void ofApp::copy(){
    ofDirectory dir(source);
    if (extension.size() > 0 && extension != "none")
        dir.allowExt(extension);
    
    dir.listDir();
    
    if (dir.size() > 0)
        status = "working";
    else {
        status = "nothing copied";
        return;
    }
    
    int i = 0;
    int cp = 0;
    for (auto file : dir){
        if (i % nth == 0){
            file.copyTo(destination);
            cp++;
        }
        i++;
    }
    
    status = ofToString(cp) + " files copied to " + destination;
}


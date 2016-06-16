#include "ofxCustomButton.h"
#include "ofGraphics.h"
using namespace std;

ofxCustomButton::ofxCustomButton(ofParameter<string> _label, float width, float height){
    setup(_label,width,height);
}

ofxCustomButton::~ofxCustomButton(){
    label.removeListener(this,&ofxCustomButton::valueChanged);
}

ofxCustomButton* ofxCustomButton::setup(ofParameter<string> _label, float width, float height) {
    label.makeReferenceTo(_label);
    b.width  = width;
    b.height = height;
    setNeedsRedraw();
    label.addListener(this,&ofxCustomButton::valueChanged);
    return this;
}

ofxCustomButton* ofxCustomButton::setup(const std::string& labelName, string _label, float width, float height) {
    label.set(labelName,_label);
    return setup(label,width,height);
}

void ofxCustomButton::generateDraw(){
    bg.clear();
    
    bg.setFillColor(thisBackgroundColor);
    bg.setFilled(true);
    bg.rectangle(b);
    
    string name;
    if(!getName().empty()){
        name = getName();
    }
    
    textMesh = getTextMesh(name + (string)label, b.x + textPadding, b.y + b.height / 2 + 4);
}

void ofxCustomButton::render() {
    ofColor c = ofGetStyle().color;
    
    bg.draw();
    
    ofBlendMode blendMode = ofGetStyle().blendingMode;
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableAlphaBlending();
    }
    ofSetColor(textColor);
    
    bindFontTexture();
    textMesh.draw();
    unbindFontTexture();
    
    ofSetColor(c);
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableBlendMode(blendMode);
    }
}

ofAbstractParameter & ofxCustomButton::getParameter(){
    return label;
}

void ofxCustomButton::valueChanged(string & value){
    setNeedsRedraw();
}

bool ofxCustomButton::mousePressed(ofMouseEventArgs &args){
    if(hitTest(args))
        return true;
    return false;
}

bool ofxCustomButton::mouseReleased(ofMouseEventArgs &args){
    if(hitTest(args))
        return true;
    return false;
}

bool ofxCustomButton::hitTest(ofMouseEventArgs &args){
    int x = args.x;
    int y = args.y;
    ofPoint p1(getPosition().x, getPosition().y);
    ofPoint p2(getWidth(), getHeight());
    p2.x += p1.x;
    p2.y += p1.y;
    if(x>p1.x && x<p2.x && y>p1.y && y<p2.y)
        return true;
    return false;
}
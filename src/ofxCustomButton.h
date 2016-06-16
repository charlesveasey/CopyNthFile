#pragma once

#include "ofxBaseGui.h"
#include "ofParameter.h"

class ofxCustomButton: public ofxBaseGui {
public:
    ofxCustomButton(){}
    ofxCustomButton(ofParameter<std::string> _label, float width = defaultWidth, float height = defaultHeight);
    virtual ~ofxCustomButton();
    
    ofxCustomButton * setup(ofParameter<std::string> _label, float width = defaultWidth, float height = defaultHeight);
    ofxCustomButton * setup(const std::string& labelName, std::string label, float width = defaultWidth, float height = defaultHeight);
    
    // Abstract methods we must implement, but have no need for!
    virtual bool mouseMoved(ofMouseEventArgs & args){return false;}
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args){return false;}
    virtual bool mouseReleased(ofMouseEventArgs & args);
    virtual bool mouseScrolled(ofMouseEventArgs & args){return false;}
    
    virtual void saveTo(ofBaseSerializer& serializer){};
    virtual void loadFrom(ofBaseSerializer& serializer){};
    
    
    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method){
        label.addListener(listener,method);
    }
    
    template<class ListenerClass, typename ListenerMethod>
    void removeListener(ListenerClass * listener, ListenerMethod method){
        label.removeListener(listener,method);
    }
    
    
    std::string operator=(std::string v) { label = v; return v; }
    operator const std::string & ()       { return label; }
    
    ofAbstractParameter & getParameter();
    
protected:
    void render();
    ofParameter<std::string> label;
    void generateDraw();
    void valueChanged(std::string & value);
    bool setValue(float mx, float my, bool bCheckBounds){return false;}
    ofPath bg;
    ofVboMesh textMesh;
    bool hitTest(ofMouseEventArgs &args);
};

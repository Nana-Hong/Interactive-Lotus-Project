#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "boid.h"
#include "Ball.hpp"
#include "ofxCvColorImage.h"
#include "ofxCvGrayscaleImage.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{
    Boid theBoid;
    Ball theBall;

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
    
    // For drawing
    float waveform[4096]; //make this bigger, just in case
    int waveIndex;

    ofSoundStream soundStream;

    /* ofxMaxi*/
    void audioIn(ofSoundBuffer& input) override;
    void audioOut(ofSoundBuffer& output) override;
    maxiOsc oscillator1;
    
  vector<ofBoxPrimitive> boxes;
  ofEasyCam cam;
  int spaceRange ;
  
  ofxPanel gui;
  ofParameter <ofVec3f> uiLightPosition;
  ofParameter <ofVec3f> uiLightColor;

  ofxCvColorImage colorImage;
  ofxCvGrayscaleImage grayImage;
  ofxAssimpModelLoader model;
  ofxAssimpModelLoader model2;
  ofImage Image;
  ofTexture texture;
  ofMesh mesh;
  ofMaterial material;
  ofSpherePrimitive sphere;

  ofLight light;
  ofLight light2;

  

  int flowlevel = 3;
    ofTrueTypeFont font;
    ofSerial serial;
    
    string sensorValue;
    string sensorValue2;
    int byteData;
    int byteData2;
    string msg;
    int qq=50;
    int ww=50;
    int ee=50;
    int sound1;
    int sound2;
    int rotation;


};

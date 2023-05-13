//
//  Ball.hpp
//  A Loop
//
//  Created by Na Hong on 2023/3/24.
//

#ifndef Ball_hpp
#define Ball_hpp
#include "ofMain.h"
#include "ofxCvColorImage.h"
#include "ofxCvGrayscaleImage.h"
#include "ofxCvContourFinder.h"
#include <stdio.h>

class Ball
{
    /* Play with these constants to tweak how mouse pointer is drawn. */
    const float DRAW_RADIUS =10;
    const float DRAW_STROKE = 5;
    const ofColor DEFAULT_COLOR = ofColor::lightSlateGrey;
    const ofColor TOUCHING_COLOR = ofColor::cornflowerBlue;

    /* Private Properties */
    ofVec2f location;

public:
    void setup();
    void update();
    void draw();
    void draw(ofVec2f otherLocation);
    void keyPressed(int key);
    ofVec2f getLocation();
    //ofxCvColorImage colorImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvContourFinder contourFinder;
    ofImage colorImage;
    
};

#endif /* Ball_hpp */

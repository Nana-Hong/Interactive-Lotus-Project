//
//  Ball.cpp
//  A Loop
//
//  Created by Na Hong on 2023/3/24.
//

#include "Ball.hpp"


void Ball::setup(){
    colorImage.load("jingli.png");
    grayImage = colorImage;
    
    contourFinder.findContours(grayImage, 50, (ofGetWidth()*ofGetHeight())/3, 10, false);

}


void Ball::update() {
    grayImage.threshold(100);
    grayImage.blur(5);
    grayImage.invert();
    
    if (ofGetKeyPressed(OF_KEY_UP)) {
            location.y -= 5;
        }
        if (ofGetKeyPressed(OF_KEY_DOWN)) {
            location.y += 5;
        }
        if (ofGetKeyPressed(OF_KEY_LEFT)) {
            location.x -= 5;
        }
        if (ofGetKeyPressed(OF_KEY_RIGHT)) {
            location.x += 5;
        }

}



void Ball::draw(ofVec2f otherLocation)
{
    // How far is the other?
    float distanceToOther = location.distance(otherLocation);

    // Draw pseudo-stroke in black
    ofSetColor(ofColor::black);
    ofDrawCircle(location.x, location.y, DRAW_RADIUS + DRAW_STROKE);

    // The fill changes if other location is in our 2x radius hit zone.
    if (distanceToOther <= DRAW_RADIUS * 2) {
        ofSetColor(TOUCHING_COLOR);
    }
    else {
        ofSetColor(DEFAULT_COLOR);
    }

    // Draw circle with selected fill color.
    ofDrawCircle(location.x, location.y, DRAW_RADIUS);
}

/* If you don't care about collision colour change here's a simpler draw(). */

void Ball::draw() {
    
    
    ofSetColor(249, 40, 15);
    ofSetLineWidth(2);
    for (int i = 0; i < contourFinder.nBlobs; i++) {
        contourFinder.blobs[i].draw(0, 0);
    }
    //ofSetColor(ofColor::black);
    //ofDrawCircle(location.x, location.y, DRAW_RADIUS + DRAW_STROKE);
    //ofSetColor(DEFAULT_COLOR);
    //ofDrawCircle(location.x, location.y, DRAW_RADIUS);
}

/* Public Getter - Mouse Location */

void Ball::keyPressed(int key){

}

ofVec2f Ball::getLocation() {
    return location;
}


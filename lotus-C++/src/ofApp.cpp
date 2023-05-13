#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    font.load("monospace", 24);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // arduino users check in arduino app....
    int baud = 9600;
    serial.setup("/dev/cu.usbmodem14301", baud);
    
    
    ofHideCursor();               // Hide the OS mouse pointer.
    //ofBackground(ofColor::white); // Set a white background.

    // Setup the Boid. The Ball is built in the header file.
    theBoid.setup(
        ofGetHeight() / 2,   // middle x position
        ofGetWidth() / 2,    // middle y position
        ofColor::darkorange, // fill color
        theBall             // the Ball
    );

    
    //3D
    int maxBoxes =400;
         spaceRange = 300;
         ofEnableDepthTest();
         ofSetBackgroundColor(0);
         light2.setPosition(0, 0, -10);
         light2.enable();
         
         for (int i = 0; i < maxBoxes; i ++){
             ofBoxPrimitive newBox;
             newBox.set(5, 5, 5);
             newBox.setPosition( ofRandom(-spaceRange, spaceRange),
                                ofRandom(-spaceRange, spaceRange),
                                ofRandom(-spaceRange, spaceRange));
             for (int side =0; side < 6; side ++){
                 newBox.setSideColor( side,  ofColor::fromHsb(ofRandom(255),  255,  255));
             }
             boxes.push_back(newBox);
         }
    
  //water lotus
  gui.setup();
  gui.add(uiLightPosition.set("light position",
                              ofVec3f(0),
                              ofVec3f(-300),
                              ofVec3f(300)));
  gui.add(uiLightColor.set("light color", ofVec3f(0), ofVec3f(0), ofVec3f(255)));

  cam.setDistance(500);

   model.loadModel("torus.obj");
   model2.loadModel("LotusFlower.obj");
    
    
    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;
    
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
   

}

//--------------------------------------------------------------
void ofApp::update(){
    // Update the mouse and the boid.
    theBall.update();
    theBoid.update();
    if (ofGetKeyPressed('a')) {
            qq -= 5;
        }
    if (ofGetKeyPressed('s')) {
            qq += 5;
        }
    if (ofGetKeyPressed('b')) {
            ww -= 5;
        }
    if (ofGetKeyPressed('n')) {
            ww += 5;
        }
    if (ofGetKeyPressed('c')) {
            ee -= 5;
        }
    if (ofGetKeyPressed('v')) {
            ee += 5;
        }
    
    boxes[ofRandom( boxes.size()) ].setPosition( ofRandom(-spaceRange, spaceRange),
                           ofRandom(-spaceRange, spaceRange),
                           ofRandom(-spaceRange, spaceRange));
    
  //light.setPosition(uiLightPosition->x, uiLightPosition->y, uiLightPosition->z);
    light.setPosition(qq, ww, ee);
  light.setAmbientColor(ofColor(uiLightColor->x, uiLightColor->y, uiLightColor->z));
    
    
    // Arduino
    //Simple if statement to inform user if Arduino is sending serial messages.
    if (serial.available() < 0) {
        sensorValue = "Arduino Error";
        sensorValue2 = "Arduino Error";
    }
    else {
        //While statement looping through serial messages when serial is being provided.
        while (serial.available() > 0) {
            //byte data is being writen into byteData as int.
            byteData = serial.readByte();
            byteData2 = serial.readByte();
        
            //byteData is converted into a string for drawing later.
            sensorValue = "value: " + ofToString(byteData);
            sensorValue2 = "value: " + ofToString(byteData2);
        }
    }
    cout << sensorValue << endl; // output the sensorValue
    cout << sensorValue2 << endl; // output the sensorValue2
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    
    flowlevel = byteData/10;
    font.load("Nice Sugar.ttf", 15);
    msg = "press key a, b or c to test serial:\n";
    font.drawString(msg, 30, 670);
    font.drawString("sensorValue: " + sensorValue, 30, 700);
    font.drawString("sensorValue2: " + sensorValue2, 30, 730);
    
    
  ofEnableDepthTest();
    float time = ofGetSystemTimeMillis()/100.0;
  light.enable();
  ofPushMatrix();
    
  cam.begin();
    // Draw the ball and the boid.
    theBall.draw(theBoid.getLocation());
    theBoid.draw();
    
    // lotus draw
    model2.setScale(0.3, 0.3, 0.3);
    model2.drawWireframe();
    
    // box draw
    for (int k = 0; k <boxes.size(); k++){
        boxes[k].draw();
    }
    
    // water draw
    for (int i = 0; i < 60; i++) {
    ofScale(0.8);
    ofRotateXDeg(sin(i + ofGetElapsedTimef()) * flowlevel);
    model.drawVertices();
    }
    
  
  cam.end();
  ofPopMatrix();
  light.disable();
  ofDisableDepthTest();
  
  gui.draw();
    /////////////// waveform
    ofTranslate(0, 0);
    ofSetColor(0,0,0,0);
    ofFill();
    ofSetLineWidth(3);
    ofDrawLine(0, 0,1, waveform[1] * ofGetHeight()/2.); //first line
    for(int i = 1; i < (ofGetWidth() - 1); ++i) {
        ofDrawLine(i, waveform[i] * ofGetHeight()/2., i + 1, waveform[i+1] * ofGetHeight()/2.);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  uiLightPosition.set(ofVec3f(0));
    //if (key == '1') {
      //      flowlevel += 1;
      //  }
   // if (key == '2') {
     //       flowlevel -= 1;
     //   }
    switch (key) {
        case 'a':
            serial.writeByte('a');
            cout << "flash green LED" << endl;;
            break;
            
        case 'b':
            serial.writeByte('b');
            cout << "flash red LED" << endl;
            break;
            
        case 'c':
            serial.writeByte('c');
            cout << "flash white LED" << endl;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
    
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    sound1 = byteData;
    sound2 = byteData2*3;
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i){
        double osc1 = oscillator1.triangle(sound1)*(sound2/float(ofGetHeight()));
        output[i * outChannels] = osc1 * 0.5;
        output[i * outChannels + 1] = output[i * outChannels];
        
        //Hold the values so the draw method can draw them
        waveform[waveIndex] =  output[i * outChannels];
        if (waveIndex < (ofGetWidth() - 1)) {
            ++waveIndex;
        } else {
            waveIndex = 0;
        }
    }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>


//-----------------------------------------------------------------------------
// Preprocessor definitions
//-----------------------------------------------------------------------------
#define MY_SRATE         44100            // sample rate
#define MY_CHANNELS      2                // number of channels
#define MY_BUFFERHISTORY 50               // number of buffers to save
#define MY_BUFFERSIZE    512              // number of frames in a buffer
#define MY_NBUFFERS      2                // number of buffers latency
#define MY_PIE           3.14159265358979 // for convenience

using namespace boost;

//-----------------------------------------------------------------------------
// Our Bokeh class
//-----------------------------------------------------------------------------
class Bokeh {
public:
    // Constructor and destructor -- do nothing
    Bokeh() {}
    ~Bokeh() {}

    void setup(){
        bokeh_image.load(ofToDataPath("Bokeh.png")); // Load the image
        x = ofRandomWidth();                         // Get random x position
        y = ofRandomHeight();                        // Get random y position
        width = int(ofRandom(20, 500));              // Get random width(height)
        bokeh_color.r = ofRandom(0, 255);            // Get random color (r)
        bokeh_color.g = ofRandom(0, 255);            // Get random color (g)
        bokeh_color.b = ofRandom(0, 255);            // Get random color (b)
    }

    void update(float alphaValue) {
        // Update the Bokeh's alpha value, so it can be responsive to input
        // (in our case, the magnitude of an FFT bin.
        bokeh_color.a = alphaValue * 255;

        // Resize the image. NOTE: we're doing this in the update function in
        // case we want to resize it later.
        bokeh_image.resize(width, width);
    }

    void draw() {
        // Set the current color
        ofSetColor(bokeh_color);

        // Draw the image at the right location
        bokeh_image.draw(y, x);
    }

private:
    // Member variables
    ofImage bokeh_image;     // Holds our "Bokeh" image data
    ofColor bokeh_color;     // Keep track of this bokeh's color
    int x, y, width, height; // Position member variables
};

//-----------------------------------------------------------------------------
// The application class
//-----------------------------------------------------------------------------
class ofApp : public ofBaseApp{

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

    // Get audio input samples
    void audioIn(float * input, int bufferSize, int nChannels);
    
    asio::io_service io;
    std::unique_ptr<asio::serial_port> port;
    bool portOpened = false;

private:
    // Our sound stream object
    ofSoundStream soundStream;

    // Vectors for our left- and right-channel waveforms
    vector<float> left, right;

    // Our FFT object. NOTE: requires that you have downloaded the ofxFft addon
    // and included it in your project. You can download from
    // https://github.com/kylemcdonald/ofxFft and then unzip it into
    // openFrameworks/addons/ofxFft/
    ofxFft* fft;

    // Number of Bokehs in this app
    const static int nBokeh = MY_BUFFERSIZE/4;
    // Our Bokeh instances
    Bokeh bokeh[nBokeh];
    ofColor myColor;
    int bVal = 125;
};


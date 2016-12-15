#include "ofApp.h"



void write(string str, std::unique_ptr<asio::serial_port>& port) {
    boost::asio::write(*port, asio::buffer(str.c_str(), str.length()));
}

int times = 0;

void send(int r, int g, int b, std::unique_ptr<asio::serial_port>& port) {
    if (times % 2 == 0) {
        std::stringstream add_string;
        add_string << r << " " << g << " " << b << "\n";
        cout<< "add_string: " << add_string.str() << std::endl;
        const char * temp = add_string.str().c_str();
        try {
            write(add_string.str(), port);
        } catch( const boost::system::system_error& ex ) {
        }
    }
    times += 1;
}
//--------------------------------------------------------------
void ofApp::setup(){
    port = std::make_unique<asio::serial_port>(io);
    port->open("/dev/cu.usbmodem1590751");
    port->set_option(asio::serial_port_base::baud_rate(115200));
    port->set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::type::none));
    port->set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::type::none));
    port->set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::type::one));
    

    // Setup each of out Bokeh objects
    for(int i=0; i<nBokeh; i++){
        bokeh[i].setup();
    }

    // Enable additive blending, which makes our overlapping Bokehs look nice
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // Setup the sound stream
    soundStream.setup(this, 0, MY_CHANNELS, MY_SRATE, MY_BUFFERSIZE, MY_NBUFFERS);

    // Resize and initialize left and right (audio) buffers...
    left.resize( MY_BUFFERSIZE, 0 );
    right.resize( MY_BUFFERSIZE, 0 );

    // Setup the fft
    fft = ofxFft::create(MY_BUFFERSIZE, OF_FFT_WINDOW_HAMMING);
}

//--------------------------------------------------------------
void ofApp::update(){

    // Normalize the left channel waveform
    float maxValue = 0;
    for(int i = 0; i < left.size(); i++) {
        if(abs(left[i]) > maxValue) { maxValue = abs(left[i]); }
    }
    for(int i = 0; i < left.size(); i++) { left[i] /= maxValue; }

    // Take the FFT of the left channel
    fft->setSignal(&left[0]);

    // Get the magnitudes and copy them to audioBins
    float* fftData = fft->getAmplitude();

    // Now normalize the FFT magnitude values
    maxValue = 0;
    int maxAmpFreq = 0;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(fftData[i]) > maxValue) {
            maxValue = abs(fftData[i]);
            maxAmpFreq = i;
        }
    }
    int factor = maxValue*500;
    if (factor > 255) {
        factor = 255;
        bVal += 3;
    } else if (factor < 0 ) {
        factor = 0;
    } else {
        bVal -= 3;
    }
    if (bVal > 255) {
        bVal = 255;
    } else if (bVal < 0) {
        bVal = 0;
    }
    if (maxAmpFreq > 25) {
        maxAmpFreq = 25;
    } else if (maxAmpFreq < 0) {
        maxAmpFreq = 0;
    }
//    cout << "Bin size = " << fft->getBinSize() << endl;
//    cout << (int)(maxValue*255) << endl;
//    cout << "freq = " << maxAmpFreq << endl;
//    myColor.setHsb(maxAmpFreq * 14, (int)(maxValue*250), 255);
    myColor.setHsb(maxAmpFreq * 14, 255, 255);
    if (maxValue > 0.4) {
        send(myColor.r, myColor.g, myColor.b, port);
    }
    
    
//    send(factor, 255-factor, bVal, port);
    for(int i = 0; i < fft->getBinSize(); i++) { fftData[i] /= maxValue; }

    // Update the bokeh with its amplitude value (taken from an FFT bin)
    for(int i=0; i<nBokeh; i++){
        bokeh[i].update( fftData[int( i * fft->getBinSize() / nBokeh )] );
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0); // Black background

    for(int i=0; i<nBokeh; i++){
        bokeh[i].draw();
    }
}

//--------------------------------------------------------------
// audioIn() -- deal with incoming audio buffer
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // Write incoming audio to buffer. Note: samples are interleaved.
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2];
        right[i]	= input[i*2+1];
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

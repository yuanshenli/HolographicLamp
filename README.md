# `HolographicLamp`
======

### [Shenli Yuan](shenliy@stanford.edu) 

This project is developed using [openFrameworks](http://openframeworks.cc/). It's based on the BokehExample code written by Romain Michon. 

This holographic lamp as three different modes: Music,RGB and Rainbow.

The Music mode was designed to take audio input and show different color according to the frequency of the signal with the highest amplitude. I implemented a Fast Fourier transform (FFT) to extract all the frequencies of audio input and map the major frequency to the hue of HSB color of the LEDs. 
In RGB mode, the color of lamp can be changed by three knobs (R, G and B, respectively). 
In Rainbow mode, the color of LED will be changed gradually with a rainbow pattern.

The wood box at bottom is made by laser cutting as well as the lamp, which is made of clear acrylic sheet. The micro controller used in the project is a [Teensy 3.2](https://www.pjrc.com/store/teensy32.html). The LEDs used is a [NeoPixel stick](https://www.adafruit.com/products/1426) from Adafruit. The FFT implemented in this project is based on [ofxFft](https://github.com/kylemcdonald/ofxFft) library. 
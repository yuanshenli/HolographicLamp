# `HolographicLamp`
======

### [Shenli Yuan](shenliy@stanford.edu) 

This project is developed using openFrameworks. It's based on the BokehExample code written by Romain Michon. 

This holographic lamp as three different modes: Music,RGB and Rainbow.

The Music mode was designed to take audio input and show different color according to the frequency of highest amplitude. I implemented a Fast Fourier transform (FFT) to extract all the frequencies of audio input and map the major frequency to the hue of HSB color of the LEDs. 
In RGB mode, the color of lamp can be changed by three knobs (R, G and B, respectively). 
In Rainbow mode, the color of LED will be changed gradually with a rainbow pattern.
#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void audioOut(float * output, int bufferSize, int nChannels);
	void drawWaveform();
	void keyPressed(int key);
	void random();

	int sampleRate, bufferSize;

	maxiOsc carrier, mod;
	maxiOsc myOsc;

	maxiFilter lowpass;

	ofxPanel gui;
	ofParameter<float> carrierFreq, modFreq, modIndex, gain;
	ofParameter<float> cutoff, resonance, myOscFreq, myOscIndex;

	double oscOUT, modOUT, mix;
	double filterOUT, myOscOUT;

	// used for drawing waveform
	float soundBuffer[512], pauseBuffer[512];

	bool pause;
};
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(100);
	sampleRate = 44100;
	bufferSize = 512;

	gui.setup();
	// add ofParameters to "gui" panel
	gui.add(carrierFreq.set("carrier frequency", 440, 20, 1000));
	gui.add(modFreq.set("mod frequency", 100, 0, 500));
	gui.add(modIndex.set("mod index", 100, 0, 500));
	gui.add(gain.set("gain", 0.5, 0, 1));


	gui.add(cutoff.set("cutoff", 400, 1, 8000));
	gui.add(resonance.set("resonance", 50, 0, 100));

	gui.add(myOscFreq.set("my osc frequency", 100, 0, 500));
	gui.add(myOscIndex.set("my osc index", 100, 0, 500));

	// switch on the DAC - needs to happen at the end of setup
	ofSoundStreamSetup(2, 2, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();
	drawWaveform();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {

		// modulator
		modOUT = mod.square(modFreq) * modIndex;

		myOscOUT = mod.saw(myOscFreq) * myOscIndex;
		// carrier
		oscOUT = carrier.sinewave(carrierFreq + modOUT + myOscOUT);

		filterOUT = lowpass.lores(oscOUT, cutoff, resonance);

		mix = filterOUT * gain;

		output[i*nChannels] = mix; // left channel
		output[i*nChannels + 1] = mix; // right channel

		soundBuffer[i] = mix;
	}
}

//--------------------------------------------------------------
void ofApp::drawWaveform() {
	ofNoFill();
	ofSetColor(50);
	ofSetLineWidth(5);
	ofBeginShape();
	for (int i = 0; i < bufferSize; i++) {
		float x = ofMap(i, 0, bufferSize, 0, ofGetWidth());
		if (pause == false) {
			ofVertex(x, ofGetHeight()*.5 + soundBuffer[i] * 200);
			pauseBuffer[i] = soundBuffer[i];
		}
		else
			ofVertex(x, ofGetHeight()*.5 + pauseBuffer[i] * 200);
	}
	ofEndShape();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 32) pause = !pause;

	if (key == 114) random();
}


//--------------------------------------------------------------
void ofApp::random() {

	carrierFreq.set(ofRandom(carrierFreq.getMin(), carrierFreq.getMax()));
	modFreq.set(ofRandom(modFreq.getMin(), modFreq.getMax()));
	modIndex.set(ofRandom(modIndex.getMin(), modIndex.getMax()));
	cutoff.set(ofRandom(cutoff.getMin(), cutoff.getMax()));
	resonance.set(ofRandom(resonance.getMin(), resonance.getMax()));
	myOscFreq.set(ofRandom(myOscFreq.getMin(), myOscFreq.getMax()));
	myOscIndex.set(ofRandom(myOscIndex.getMin(), myOscIndex.getMax()));
}

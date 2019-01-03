#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(5);

	this->fbo1.allocate(ofGetWidth(), ofGetHeight());
	this->fbo2.allocate(ofGetWidth(), ofGetHeight());
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	ofSetColor(39);
	this->fbo1.begin();
	ofClear(0);
	
	int length = 30;
	int x_span = 120;
	int y_span = 120;
	ofColor color;
	for (int x = 0; x < ofGetWidth(); x += x_span) {

		for (int y = 0; y < ofGetHeight(); y += y_span) {

			color.setHsb(ofRandom(255), 230, 200);
			ofSetColor(color);

			float x_seed = ofRandom(100);
			float y_seed = ofRandom(100);
			ofPoint point;
			ofPoint prev_point = ofPoint();
			for (int l = 0; l < length; l++) {

				point = ofPoint(ofMap(ofNoise(x_seed, (ofGetFrameNum() + l) * 0.015), 0, 1, x, x + x_span), ofMap(ofNoise(y_seed, (ofGetFrameNum() + l) * 0.015), 0, 1, y, y + y_span));
				if (l != 0) { ofDrawLine(prev_point, point); }
				prev_point = point;
			}

			ofDrawCircle(point, 10);
		}
	}

	this->fbo1.end();

	ofSetColor(39);
	this->fbo2.begin();
	ofClear(0);

	for (int y = 0; y < ofGetHeight(); y += 60) {

		int x_start = y % 120;
		for (int x = x_start; x < ofGetWidth(); x += 120) {

			ofDrawRectangle(x, y, 60, 60);
		}
	}


	this->fbo2.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);
	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex1", this->fbo1.getTexture(), 1);
	this->shader.setUniformTexture("tex2", this->fbo2.getTexture(), 2);

	ofDrawRectangle(glm::vec2(0, 0), ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	int len = 300;
	int width = 50;
	ofColor color;
	for (int y = -300; y <= 300; y += width) {

		int start_param = ofMap(ofNoise(y * 0.008, ofGetFrameNum() * 0.0035), 0, 1, 0, 720);
		int end_param = start_param + 70;
		color.setHsb(ofMap(y, -300, 300, 0, 255), 230, 255);
		int line_start_index = this->line.getNumVertices();

		for (int param = start_param; param <= end_param; param++) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(this->make_point(len, param), width *  0.5 + y));
			vertices.push_back(glm::vec3(this->make_point(len, param), width * -0.5 + y));

			this->face.addVertices(vertices);
			this->line.addVertices(vertices);

			this->face.addColor(color);
			this->face.addColor(color);

			this->line.addColor(ofColor(255));
			this->line.addColor(ofColor(255));

			if (param > start_param) {

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 4);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 3);
				this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 4);
				
			}
		}

		this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
		this->line.addIndex(line_start_index); this->line.addIndex(line_start_index + 1);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.333333333333);

	this->face.draw();
	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len, len), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len, -len), len * 0.5);
	}
	else {

		return glm::vec2(-len, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
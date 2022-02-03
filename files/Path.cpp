#include "Path.h"

using namespace sf;
using namespace std;


Path::Path(float time, float speed, Bezier::Bezier<2> curve) {
	this->speed = speed / (curve.length() / 100);
	this->time = time;
	this->length = curve.length();

	Bezier::Point curvePoint;
	for (float m = 0; m < 1; m += 0.01) {
		curvePoint = curve.valueAt(m);
		this->pathPoints.push_back(Vector2f(curvePoint.x, curvePoint.y));
	}
}
Path::Path(float time, float speed, Bezier::Bezier<3> curve) {
	this->speed = speed / (curve.length() / 100);
	this->time = time;
	this->length = curve.length();

	Bezier::Point curvePoint;
	for (float m = 0; m < 1; m += 0.01) {
		curvePoint = curve.valueAt(m);
		this->pathPoints.push_back(Vector2f(curvePoint.x, curvePoint.y));
	}
}
Path::Path(float time, float speed, Bezier::Bezier<4> curve) {
	this->speed = speed / (curve.length() / 100);
	this->time = time;
	this->length = curve.length();

	Bezier::Point curvePoint;
	for (float m = 0; m < 1; m += 0.01) {
		curvePoint = curve.valueAt(m);
		this->pathPoints.push_back(Vector2f(curvePoint.x, curvePoint.y));
	}
}
Path::Path(float time, float speed, Bezier::Bezier<5> curve) {
	this->speed = speed / (curve.length() / 100);
	this->time = time;
	this->length = curve.length();

	Bezier::Point curvePoint;
	for (float m = 0; m < 1; m += 0.01) {
		curvePoint = curve.valueAt(m);
		this->pathPoints.push_back(Vector2f(curvePoint.x, curvePoint.y));
	}
}
Path::Path(float time, float speed, Bezier::Bezier<6> curve) {
	this->speed = speed / (curve.length() / 100);
this->time = time;
	this->length = curve.length();

	Bezier::Point curvePoint;
	for (float m = 0; m < 1; m += 0.01) {
		curvePoint = curve.valueAt(m);
		this->pathPoints.push_back(Vector2f(curvePoint.x, curvePoint.y));
	}
}


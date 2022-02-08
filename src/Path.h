#pragma once
#include "Header.h"
#include "Character.h"
#include "RessourceManager.h"
#include "Bezier.h"


using namespace sf;
using namespace std;



class Path
{
private:

public:
	float time;
	float speed;
	float length;
	vector<Vector2f> pathPoints;

	Path(float time, float speed, Bezier::Bezier<2> curve);
	Path(float time, float speed, Bezier::Bezier<3> curve);
	Path(float time, float speed, Bezier::Bezier<4> curve);
	Path(float time, float speed, Bezier::Bezier<5> curve);
	Path(float time, float speed, Bezier::Bezier<6> curve);
};

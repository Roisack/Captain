#ifndef __SUN_HPP_
#define __SUN_HPP_

#include "vector3.hpp"

class Sun
{
private:
	int mass;
	int temperature;
	int radius;
	Vector3 position;
	double angle;
	float angle2;
	Vector3 colour;
public:
	Sun();
	Sun(int mass, int temperature, int radius, int posX, int posY);
	~Sun();
	
	void render();
};

#endif

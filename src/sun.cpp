#include "sun.hpp"

Sun::Sun()
{
}

Sun::Sun(int m, int t, int posX, int posY)
{
	mass = m;
	temperature = t;
	position.x = posX;
	position.y = posY;
	
	std::cout << "=======" << std::endl;
	std::cout << "Created a new sun with following properties:" << std::endl;
	std::cout << "- mass: " << mass << std::endl;
	std::cout << "- temperature: " << temperature << std::endl;
	std::cout << "- position X: " << position.x << std::endl;
	std::cout << "- position Y: " << position.y << std::endl;
	std::cout << "=======" << std::endl;
}

Sun::~Sun()
{
}

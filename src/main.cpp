/*
Captain

Yet another game project
*/

#include "programManager.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	progmgr.work();
	progmgr.stop();

	std::cout << "Program exit point" << std::endl;
	return 0;
}

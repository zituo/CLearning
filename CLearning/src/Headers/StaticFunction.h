#pragma once
#include <iostream>

class Entity
{
	int x, y;

	void func1()
	{
		std::cout << x << "," << y << std::endl;
	}

	/*static void func2()
	{
		std::cout << x << "," << y << std::endl;
	}*/
};
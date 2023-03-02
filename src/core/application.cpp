#include "pch.h"
#include "application.h"

namespace lava
{
	application::application()
	{
		std::cout << "application::application()" << std::endl;
	}

	application::~application()
	{
		std::cout << "application::~application()" << std::endl;
	}

	void application::run()
	{
		std::cout << "application::run()" << std::endl;
	}
}

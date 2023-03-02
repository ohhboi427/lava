#include "pch.h"
#include "application.h"

#include "logger.h"

namespace lava
{
	application::application()
	{
		m_logger = logger::create("lava", "%^%T [%l]: %v%$");
	}

	application::~application()
	{
		delete m_logger;
	}

	void application::run()
	{
		
	}
}

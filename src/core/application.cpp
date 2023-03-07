#include "pch.h"
#include "application.h"

#include "logger.h"
#include "../resource/resource_manager.h"
#include "../resource/resource_text_file.h"

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

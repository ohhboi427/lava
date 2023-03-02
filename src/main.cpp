#include "pch.h"
#include "core/application.h"

int main(int argc, char* argv[])
{
	lava::application* app = new lava::application();

	app->run();

	delete app;
}

workspace "lava"
	architecture "x86_64"
	configurations { "Debug", "Release" }

project "lava"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	files {
		"src/**.cpp",
		"src/**.h",
	}

	includedirs {
		"src",
		"vendor/spdlog/include",
		"vendor/json/include",
		"vendor/entt/include",
		"vendor/glad/include",
		"vendor/glfw/include",
		"vendor/glm/include",
	}
	
	libdirs {
		"vendor/glad/lib",
		"vendor/glfw/lib",
	}

	links {
		"opengl32.lib",
		"glad.lib",
		"glfw3.lib",
	}

	defines {
		"SPDLOG_USE_STD_FORMAT",
		"GLFW_INCLUDE_NONE",
	}

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	targetdir "bin"
	objdir    "obj/%{cfg.buildcfg}"

	filter "configurations:Debug"
		ignoredefaultlibraries { "MSVCRT" }
		targetname "%{prj.name}d"
		optimize "off"
		symbols "on"
		defines {
			"LAVA_DEBUG",
		}

	filter "configurations:Release"
		optimize "on"
		symbols "off"
		defines {
			"LAVA_RELEASE",
		}

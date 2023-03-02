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

	filter "configurations:Release"
		optimize "on"
		symbols "off"

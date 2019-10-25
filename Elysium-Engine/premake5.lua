workspace "Elysium-Engine"
	architecture "x86"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Elysium"
	location "Elysium"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "empch.h"
	pchsource "Elysium/src/empch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS" -- for all the old C header warnings
	}

	includedirs
	{
		"%{prj.name}/src"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"

		defines 
		{
			"EM_DEBUG",
			"EM_ENABLE_ASSERTS",
			"EM_ENABLE_LOGS",
			"EM_ENABLE_EXCEPTIONS"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EM_RELEASE"
		runtime "Release"
		optimize "on"

project "Elysium-Tests"
		location "Elysium-Tests"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++11"
		staticruntime "on"

		nuget "Microsoft.googletest.v140.windesktop.msvcstl.static.rt-static:1.8.1"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "pch.h"
		pchsource "Elysium-Tests/src/pch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		defines
		{
			"WIN32",
			"_CONSOLE"
		}

		includedirs
		{
			"%{prj.name}/src",
			"Elysium/src",
			"packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-static.1.8.1/build/native/include"
		}

		links
		{
			"Elysium"
		}
		
		filter "configurations:Debug"
			buildoptions "/MTd"
			defines 
			{
				"_DEBUG"
			}
			links
			{
				"packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-static.1.8.1/lib/native/v140/windesktop/msvcstl/static/rt-static/x86/Debug/gtest_maind.lib"
			}

		filter "configurations:Release"
		buildoptions "/MT"
			defines 
			{
				"NDEBUG"
			}
			links
			{
				"packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-static.1.8.1/lib/native/v140/windesktop/msvcstl/static/rt-static/x86/Release/gtest_main.lib"
			}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++11"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Elysium/src"
	}

	links
	{
		"Elysium"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EM_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "EM_RELEASE"
		runtime "Release"
		optimize "on"
		inlining "Auto"

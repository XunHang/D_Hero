workspace "D_Hero_Prj"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

OUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "D_Hero_Prj"
	location "D_Hero_Prj"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. OUT_DIR .. "./%{prj.name}")
	objdir ("bin-int/" .. OUT_DIR .. "./%{prj.name}")

	pchheader "dhpch.h"
	pchsource "D_Hero_Prj/src/dhpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/ThirdParty/spdlog/include"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DH_PLATFORM_WINDOWS",
			"DH_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OUT_DIR .. "/SandBox")
		}

	filter "configurations:Debug"
		defines "DH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DH_DIST"
		optimize "On"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. OUT_DIR .. "./%{prj.name}")
	objdir ("bin-int/" .. OUT_DIR .. "./%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"D_Hero_Prj/src",
		"D_Hero_Prj/ThirdParty/spdlog/include",
	}

	links {
		"D_Hero_Prj"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DH_DIST"
		optimize "On"
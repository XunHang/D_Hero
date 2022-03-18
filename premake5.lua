workspace "D_Hero_Prj"

	architecture "x86_64"

	startproject "SandBox" 

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

OUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
IncludeDir["GLFW"] = "D_Hero_Prj/ThirdParty/GLFW/include"
IncludeDir["GLAD"] = "D_Hero_Prj/ThirdParty/GLAD/include"
IncludeDir["imgui"] = "D_Hero_Prj/ThirdParty/imgui"

include "/D_Hero_Prj/ThirdParty/"

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
        "%{prj.name}/ThirdParty/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.imgui}"
    }

    links {
        "GLFW",
		"GLAD",
		"imgui",
        "opengl32.lib"
    }

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DH_PLATFORM_WINDOWS",
			"DH_BUILD_DLL",
			"GLFW_INCLUDE_NONE",  -- glfw 不再包含 gl 有关头文件
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OUT_DIR .. "/SandBox")
		}

	-- /MD : 解决 spdLog 在应用与引擎中都开辟空间引发的崩溃问题
	filter "configurations:Debug"
		defines "DH_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "DH_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "DH_DIST"
		buildoptions "/MD"
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

	-- /MD : 解决 spdLog 在应用与引擎中都开辟空间引发的崩溃问题
	filter "configurations:Debug"
		defines "DH_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "DH_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "DH_DIST"
		buildoptions "/MD"
		optimize "On"
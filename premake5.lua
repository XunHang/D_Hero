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
IncludeDir["glm"] = "D_Hero_Prj/ThirdParty/glm"

include "/D_Hero_Prj/ThirdParty/"

project "D_Hero_Prj"
	location "D_Hero_Prj"
--	kind "SharedLib"  -- 动态链接库
	kind "StaticLib"  -- 静态链接库
	staticruntime "On"
	language "C++"
	
	targetdir ("bin/" .. OUT_DIR .. "./%{prj.name}")
	objdir ("bin-int/" .. OUT_DIR .. "./%{prj.name}")

	pchheader "dhpch.h"
	pchsource "D_Hero_Prj/src/dhpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{IncludeDir.glm}/glm/**.hpp",
		"%{IncludeDir.glm}/glm/**.inl"
	}

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/ThirdParty/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}"
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
			"DH_STATIC_VERSION",
			--"DH_BUILD_DLL",		-- 控制是否编译为 dll
			"GLFW_INCLUDE_NONE",	-- glfw 不再包含 gl 有关头文件,
			"_CRT_SECURE_NO_WARNINGS"--去除 unsafe warning
		}

--		postbuildcommands {
--			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OUT_DIR .. "/SandBox")
--		}

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
	staticruntime "On"
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
        "%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links {
		"D_Hero_Prj"
	}

	defines {
		"DH_STATIC_VERSION",
	}

	filter "system:windows"
		cppdialect "c++17"
		systemversion "latest"

		defines {
			"DH_PLATFORM_WINDOWS",
		}

	-- /MD : 解决 spdLog 在应用与引擎中都开辟空间引发的崩溃问题
	filter "configurations:Debug"
		defines "DH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DH_DIST"
		optimize "On"
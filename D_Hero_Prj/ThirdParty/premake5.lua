project "GLAD"
	kind "StaticLib" --项目类型为静态库
	language "C" --语言为C

	targetdir ("bin/" .. OUT_DIR .. "/%{prj.name}") --生成目录
	objdir ("bin-int/" .. OUT_DIR .. "/%{prj.name}") --中间文件目录

	files { --项目的源文件
		"GLAD/include/glad/glad.h",
		"GLAD/include/KHR/khrplatform.h",
		"GLAD/src/glad.c"
	}

	includedirs { --项目包含的目录
		"GLAD/include"
	}
	
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug" --Debug模式的配置
		runtime "Debug" --运行时
		symbols "on" --开启pdb文件

	filter "configurations:Release" --Release模式
		runtime "Release" 
		optimize "on" --开启优化

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. OUT_DIR .. "/%{prj.name}")
	objdir ("bin-int/" .. OUT_DIR .. "/%{prj.name}")

	files {
		"GLFW/include/GLFW/glfw3.h",
		"GLFW/include/GLFW/glfw3native.h",
		"GLFW/src/glfw_config.h",
		"GLFW/src/context.c",
		"GLFW/src/init.c",
		"GLFW/src/input.c",
		"GLFW/src/monitor.c",
		"GLFW/src/vulkan.c",
		"GLFW/src/window.c",

		"GLFW/src/internal.h",
		"GLFW/src/mappings.h",
		"GLFW/src/platform.h",

		"GLFW/src/platform.c",
		"GLFW/src/egl_context.c",
		"GLFW/src/osmesa_context.c",
		"GLFW/src/null_platform.h",
		"GLFW/src/null_joystick.h",
		"GLFW/src/null_init.c",

		"GLFW/src/null_monitor.c",
		"GLFW/src/null_window.c",
		"GLFW/src/null_joystick.c",

	}
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"GLFW/src/x11_init.c",
			"GLFW/src/x11_monitor.c",
			"GLFW/src/x11_window.c",
			"GLFW/src/xkb_unicode.c",
			"GLFW/src/posix_time.c",
			"GLFW/src/posix_thread.c",
			"GLFW/src/glx_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c",
			"GLFW/src/linux_joystick.c"
		}

		defines	{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files {
			"GLFW/src/win32_init.c",
			"GLFW/src/win32_module.c",
			"GLFW/src/win32_joystick.c",
			"GLFW/src/win32_monitor.c",
			"GLFW/src/win32_time.h",
			"GLFW/src/win32_time.c",
			"GLFW/src/win32_thread.h",
			"GLFW/src/win32_thread.c",
			"GLFW/src/win32_window.c",
			"GLFW/src/wgl_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c"
		}

		defines { 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"


project "imgui"
	kind "StaticLib" --项目类型为静态库
	language "C++" --语言为C

	targetdir ("bin/" .. OUT_DIR .. "/%{prj.name}") --生成目录
	objdir ("bin-int/" .. OUT_DIR .. "/%{prj.name}") --中间文件目录

	files { --项目的源文件
		"imgui/imconfig.h",
		"imgui/imgui.cpp",
		"imgui/imgui.h",
		"imgui/imgui_demo.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_tables.cpp",
		"imgui/imgui_widgets.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
	}
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug" --Debug模式的配置
		runtime "Debug" --运行时
		symbols "on" --开启pdb文件

	filter "configurations:Release" --Release模式
		runtime "Release" 
		optimize "on" --开启优化

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"
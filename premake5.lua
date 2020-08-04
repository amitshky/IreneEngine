workspace "My_OpenGL"
	
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directives relative to the root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "My_OpenGL/vendor/GLFW/include"
IncludeDir["Glad"] = "My_OpenGL/vendor/Glad/include"
IncludeDir["ImGui"] = "My_OpenGL/vendor/imgui"
IncludeDir["glm"] = "My_OpenGL/vendor/glm"
IncludeDir["stb_image"] = "My_OpenGL/vendor/stb_image"
IncludeDir["assimp"] = "My_OpenGL/vendor/assimp/include"

group "Dependencies"
	include "My_OpenGL/vendor/GLFW"
	include "My_OpenGL/vendor/Glad"
	include "My_OpenGL/vendor/imgui"

group ""

project "My_OpenGL"
	location "My_OpenGL"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "My_OpenGL/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	libdirs
	{
		"$(SolutionDir)My_OpenGL/vendor/assimp/lib"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"assimp-vc142-mtd.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS",
			"BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "RELEASE"
			runtime "Release"
			optimize "on"
			
		filter "configurations:Dist"
			defines "DIST"
			runtime "Release"
			optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	excludes "%{prj.name}/src/Example.cpp"

	includedirs
	{
		"My_OpenGL/src",
		"My_OpenGL/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.assimp}",
		"My_OpenGL/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"My_OpenGL"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "RELEASE"
			runtime "Release"
			optimize "on"
			
		filter "configurations:Dist"
			defines "DIST"
			runtime "Release"
			optimize "on"
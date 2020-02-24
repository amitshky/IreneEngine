workspace "My_OpenGL2"
	
	architecture "x64"
	startproject "My_OpenGL2"

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
IncludeDir["GLFW"] = "My_OpenGL2/vendor/GLFW/include"
IncludeDir["Glad"] = "My_OpenGL2/vendor/Glad/include"
IncludeDir["ImGui"] = "My_OpenGL2/vendor/imgui"
IncludeDir["glm"] = "My_OpenGL2/vendor/glm"
IncludeDir["stb_image"] = "My_OpenGL2/vendor/stb_image"
IncludeDir["assimp"] = "My_OpenGL2/vendor/assimp/include"

group "Dependencies"
	include "My_OpenGL2/vendor/GLFW"
	include "My_OpenGL2/vendor/Glad"
	include "My_OpenGL2/vendor/imgui"

group ""

project "My_OpenGL2"
	location "My_OpenGL2"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "My_OpenGL2/src/pch.cpp"

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
		"$(SolutionDir)My_OpenGL2/vendor/assimp/lib"
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

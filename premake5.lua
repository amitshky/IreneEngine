workspace "Irene"
	
	architecture "x64"
	startproject "IreneEditor"

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
IncludeDir["GLFW"] = "Irene/vendor/GLFW/include"
IncludeDir["Glad"] = "Irene/vendor/Glad/include"
IncludeDir["ImGui"] = "Irene/vendor/imgui"
IncludeDir["glm"] = "Irene/vendor/glm"
IncludeDir["stb_image"] = "Irene/vendor/stb_image"
IncludeDir["assimp"] = "Irene/vendor/assimp/include"
IncludeDir["Entt"] = "Irene/vendor/Entt/include"

group "Dependencies"
	include "Irene/vendor/GLFW"
	include "Irene/vendor/Glad"
	include "Irene/vendor/imgui"

group ""

project "Irene"
	location "Irene"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Irene/src/pch.cpp"

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
		"$(SolutionDir)Irene/vendor/assimp/lib"
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
		"%{IncludeDir.assimp}",
		"%{IncludeDir.Entt}"
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
		"Irene/src",
		"Irene/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.assimp}",
		"Irene/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Entt}"
	}

	links
	{
		"Irene"
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


project "IreneEditor"
	location "IreneEditor"
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
		"Irene/src",
		"Irene/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.assimp}",
		"Irene/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Entt}"
	}

	links
	{
		"Irene"
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
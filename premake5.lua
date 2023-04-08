workspace "sh2SaveTools"
    architecture "x86"
    startproject "SaveEditorGUI"
    configurations { "Debug", "Release" }

    outputdir = "%{cfg.system}-%{cfg.buildcfg}"

    configurations
	{
		"Debug",
		"Release",
	}

    flags
	{
		"MultiProcessorCompile"
	}

group "3rdparty"
	include "3rdparty/imgui"
	include "3rdparty/GLFW"
	include "3rdparty/Glad"
group ""
include "Save-Decryptor"
include "TestProgram"
include "SaveEditorGUI"
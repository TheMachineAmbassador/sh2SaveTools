workspace "sh2SaveTools"
    architecture "x86"
    startproject "TestProgram"
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
group ""
include "Save-Decryptor"
include "TestProgram"
include "ConsoleApp"
include "SaveEditorGUI"
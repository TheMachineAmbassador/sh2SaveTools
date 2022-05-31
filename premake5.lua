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

include "Save-Decryptor"
include "TestProgram"
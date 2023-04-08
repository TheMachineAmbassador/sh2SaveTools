project "SaveEditorGUI"
   kind "WindowedApp"
   language "C++"
   staticruntime "off"
   
   targetdir ("%{wks.location}/bin/" .. outputdir)
   objdir ("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

   files
   {
       "src/**.h",
       "src/**.cpp",
       "src/**.hpp"
   }

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

   includedirs
   {
	   "%{wks.location}/3rdparty/imgui",
	   "%{wks.location}/3rdparty/GLFW/include",
	   "%{wks.location}/Save-Decryptor/src",
      "%{wks.location}/TestProgram/src",
      "%{wks.location}/3rdparty/Glad/include"
   }
   links
   {
      "Save-Decryptor",
      "TestProgram",
      "GLFW",
      "Glad",
      "ImGui",
      "opengl32.lib",
   }
   filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
   
   filter "system:linux"
   	cppdialect "C++17"

   filter { "configurations:Debug" }
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"

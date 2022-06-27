project "SaveEditorGUI"
   kind "WindowedApp"
   language "C++"
   
   targetdir ("%{wks.location}/bin/" .. outputdir)
   objdir ("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

   files
   {
       "src/**.h",
       "src/**.cpp",
       "src/**.hpp"
   }

   includedirs
   {
	"%{wks.location}/3rdparty/imgui",
	"%{wks.location}/3rdparty/glfw/include",
	"%{wks.location}/Save-Decryptor/src",
        "%{wks.location}/TestProgram/src",
   }

   libdirs
   {
       "%{wks.location}/3rdparty/glfw/lib-vc2022",
   }
   links
   {
      "Save-Decryptor",
      "TestProgram",
      "ImGui",
      "glfw3_mt.lib",
      "opengl32.lib"
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

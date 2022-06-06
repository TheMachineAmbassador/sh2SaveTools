project "ConsoleApp"
   kind "ConsoleApp"
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
	"%{wks.location}/Save-Decryptor/src",
        "%{wks.location}/TestProgram/src",
   }

   links
   {
      "Save-Decryptor",
      "TestProgram"
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

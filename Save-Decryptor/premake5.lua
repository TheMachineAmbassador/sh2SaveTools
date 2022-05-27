project "Save-Decryptor"
   kind "StaticLib"
   language "C++"
   
   targetdir ("%{wks.location}/bin/" .. outputdir)
   objdir ("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

   files
   {
       "src/**.h",
       "src/**.cpp"
   }

   includedirs
   {
       "src"
   }

   filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

   filter { "configurations:Debug" }
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"

project "Game"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files
    {
        "src/**.h",
        "src/**.cpp",
        "src/**.hpp",
        "src/**.inl",
    }

   includedirs
   {
      "src/**",

	  -- Include Engine
	  "../SMEngine/src",
      "../SMEngine/src/Components",
      "../SMEngine/src/Datastructures",
      "../SMEngine/src/EmbeddedLibs",
      SDL2Dir .. "/include",
      SDL2_imageDir .. "/include",
      "../Common/src",
   }

   links
   {
        "Common",
        "SMEngine",
        "SDL2",
        "SDL2_image",
   }

   libdirs
   {
        SDL2Dir .. "/lib/" .. arch,
        SDL2_imageDir .. "/lib/" .. arch,
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
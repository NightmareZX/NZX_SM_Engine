-- premake5.lua
workspace "SMGame"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Game"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

arch = "x64"
SDL2Dir = "../Libraries/SDL2/%{cfg.system}"
SDL2_imageDir = "../Libraries/SDL2_image/%{cfg.system}"
--TinyXML2 is embedded into the engine

include "Common/Build-Common.lua"

include "SMEngine/Build-SMEngine.lua"

include "Game/Build-Game.lua"
-- include "Editor/Build-Editor.lua"
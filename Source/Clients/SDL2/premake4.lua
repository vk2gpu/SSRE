project "SSREClient_SDL2"
	kind "WindowedApp"
	language "C"
	files { "./**.h", "./**.c" }
	includedirs { "./", "../../Library/" }

	-- External includes.
	includedirs { "../../../External/SDL2-2.0.1/include" }

	configuration "windows"
   		links {
            -- SDL2 libs.
            "../../../External/SDL2-2.0.1/lib/x86/SDL2main",
            "../../../External/SDL2-2.0.1/lib/x86/SDL2",

   			-- Windows libs.
   			"user32",
   			"gdi32",
            "winmm",
            "version",
            "imm32",

            -- Our libs.
   			"SSRELibrary",
   		}

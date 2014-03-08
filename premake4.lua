local action = _ACTION or ""

-- Setup the main solution.
solution "SSRE"
	location ( "Build/" .. action )
	configurations { "Debug", "Release", "Production" }

	configuration "vs*"
		defines { "STATICLIB", "_CRT_SECURE_NO_WARNINGS", "_STATIC_CPPLIB", "_HAS_EXCEPTIONS=0" }	
		linkoptions  { "/ENTRY:\"main\"", "/nodefaultlib:libcmt.lib", "/nodefaultlib:libcmtd.lib" }

	configuration "Debug"
		targetdir ( "Build/" .. action .. "/bin/Debug" )
		defines { "STATICLIB", "WINDOWS", "_WIN32", "WIN32", "DEBUG" }
		flags { "StaticRuntime", "EnableSSE", "EnableSSE2", "FloatFast", "NativeWChar", "NoPCH", "NoRTTI", "NoExceptions", "Symbols" }

	configuration "Release"
		targetdir ( "Build/" .. action .. "/bin/Release" )
		defines { "STATICLIB", "WINDOWS", "_WIN32", "WIN32", "NDEBUG", "RELEASE" }
		flags { "StaticRuntime", "EnableSSE", "EnableSSE2", "FloatFast", "NativeWChar", "NoPCH", "NoRTTI", "NoExceptions", "Symbols", "Optimize" }

	configuration "Production"
		targetdir ( "Build/" .. action .. "/bin/Production" )
		defines { "STATICLIB", "WINDOWS", "_WIN32", "WIN32", "NDEBUG", "PRODUCTION" }
		flags { "StaticRuntime", "EnableSSE", "EnableSSE2", "FloatFast", "NativeWChar", "NoPCH", "NoRTTI", "NoExceptions", "NoFramePointer", "Optimize" }

	-- Build externals.
	-- dofile ("External/premake4.lua")

	-- Build source.
	dofile ("Source/premake4.lua")
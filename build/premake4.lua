solution "Block"
	
	configurations 	{ "Debug", "Release" }
	includedirs	{ "../src" }

	if os.get() == "macosx" then
		includedirs 	{ "/opt/local/include", "/usr/local/include" }
		libdirs		{ "/opt/local/lib", "/usr/local/lib" }
	end

	buildoptions	{ "`pkg-config --cflags MagickWand`", "-g" }
	linkoptions	{ "`pkg-config --libs MagickWand`" }
	targetdir	"../bin"

	project "CreatorLibrary"
		kind		"StaticLib"
		language 	"C"
		files 		{ 
			"../src/options/creator*.h",
			"../src/options/creator*.c",
			"../src/image/**.h",
			"../src/image/**.c",
			"../src/io/**.h",
			"../src/io/**.c",
			"../src/creator.h",
			"../src/creator.c"
		}

		buildoptions	{ "-std=c99" }
		
		vpaths		{ 
			[""] = "../../src"
		}

		vpaths		{ 
			[""] = "../src/"
		}

	project "Creator"
		kind		"ConsoleApp"
		language 	"C"
		files 		{ 
			"../src/block_creator.c"
		}

		buildoptions	{ "-std=c99" }
		
		vpaths		{ 
			[""] = "../../src"
		}

		vpaths		{ 
			[""] = "../src/"
		}

		targetname	"block-creator"

		links 	{ "CreatorLibrary" }

	project "CreatorLibraryShared"
		kind		"SharedLib"
		language 	"C"
		files 		{ 
			"../src/options/creator*.h",
			"../src/options/creator*.c",
			"../src/image/**.h",
			"../src/image/**.c",
			"../src/io/**.h",
			"../src/io/**.c",
			"../src/creator.h",
			"../src/creator.c"
		}

		buildoptions	{ "-std=c99" }
		
		vpaths		{ 
			[""] = "../../src"
		}

		vpaths		{ 
			[""] = "../src/"
		}
		targetname	"creator"

	project "BuilderLibrary"
		kind		"StaticLib"
		language 	"C"
		files 		{ 
			"../src/options/builder*.h",
			"../src/options/builder*.c",
			"../src/image/**.h",
			"../src/image/**.c",
			"../src/io/**.h",
			"../src/io/**.c"
		}

		buildoptions	{ "-std=c99" }
		
		vpaths		{ 
			[""] = "../../src"
		}

		vpaths		{ 
			[""] = "../src/"
		}

	project "Builder"
		kind		"ConsoleApp"
		language 	"C"
		files 		{ 
			"../src/builder.c"
		}
		
		vpaths		{ 
			[""] = "../../src"
		}

		vpaths		{ 
			[""] = "../src/"
		}

		buildoptions	{ "-std=c99" }

		targetname 	"block-builder"

		links 	{ "BuilderLibrary" }

	project "UnitTests"
		kind		"ConsoleApp"
		language 	"C++"
		includedirs	{ "../tests", "../deps/Catch/include" }

		buildoptions 	{ "-Wno-deprecated-writable-strings" }

		if os.get() == "linux" then
			buildoptions 	{ "-std=c++11" }
		else
			buildoptions 	{ "-stdlib=libc++", "-std=c++11" }
		end
		files 		{ 
			"../tests/**.cpp",
			"../tests/**.h"
		}

		postbuildcommands {
			"cd ../bin && ./UnitTests"
		}
		
		links 		{ "CreatorLibrary", "BuilderLibrary" }
		linkoptions	{ "`pkg-config --libs MagickWand`" }
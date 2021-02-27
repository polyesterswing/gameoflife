LibraryDir = lib
IncludeDir = includes

Defines = -DGLEW_STATIC
CFLAGS = -Wall -g
LDFLAGS = -lglfw3 -lopengl32 -lgdi32

Target = main.exe

SRC = $(wildcard src/*.cpp) $(wildcard src/vendor/**/*)

$(Target): $(SRC)
	g++ $(CFLAGS) -L$(LibraryDir) -I$(IncludeDir) $(SRC) -o bin/$(Target) $(Defines) $(LDFLAGS)

run: $(Target)
	cd bin && main

LibraryDir = lib
IncludeDir = includes

Defines = -DGLEW_STATIC
CFLAGS = -Wall -g -03
#LDFLAGS = -lglfw3 -lopengl32 -lgdi32
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

Target = main.exe

SRC = $(wildcard src/*.cpp) $(wildcard src/vendor/**/*)

$(Target): $(SRC)
	g++ $(CFLAGS) -L$(LibraryDir) -I$(IncludeDir) $(SRC) -o bin/$(Target) $(Defines) $(LDFLAGS)

run: $(Target)
	cd bin && $(Target)

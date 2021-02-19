LibraryDir = lib
IncludeDir = includes

Target = main.exe

$(Target): src/*.cpp
	g++ -Wall -g -L$(LibraryDir) -I$(IncludeDir) src/*.cpp src/vendor/glew/* -o bin/main.exe -DGLEW_STATIC -lglfw3 -lopengl32 -lgdi32

run: $(Target)
	cd bin && main

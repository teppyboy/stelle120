# Release by default.
release: stelle120.exe

stelle120.exe: src/stelle120.cpp
	x86_64-w64-mingw32-g++ -g src/stelle120.cpp -static -static-libgcc -static-libstdc++ -O3 -o stelle120.exe
	strip stelle120.exe

stelle120.debug.exe: src/stelle120.cpp
	x86_64-w64-mingw32-g++ -g src/stelle120.cpp -static -static-libgcc -static-libstdc++ -o stelle120.debug.exe

all: stelle120.exe stelle120.debug.exe

debug: stelle120.debug.exe

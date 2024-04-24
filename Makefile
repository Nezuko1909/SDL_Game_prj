all:
	g++ -std=c++17 -static-libgcc -static-libstdc++ -Isrc/include -Lsrc/lib main.cpp baseFunc.cpp BaseObject.cpp gmap.cpp character.cpp imp_timer.cpp enemy.cpp heal_point.cpp text.cpp gui.cpp sound.cpp -o scb2d -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

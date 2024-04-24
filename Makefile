all:
	g++ -Isrc/include -Lsrc/lib -o scb2d main.cpp baseFunc.cpp BaseObject.cpp gmap.cpp character.cpp imp_timer.cpp enemy.cpp heal_point.cpp text.cpp gui.cpp sound.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	./scb2d
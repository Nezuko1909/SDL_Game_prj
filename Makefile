all:
	g++ -Isrc/include -Lsrc/lib -o main main.cpp baseFunc.cpp BaseObject.cpp gmap.cpp character.cpp imp_timer.cpp enemy.cpp heal_point.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	
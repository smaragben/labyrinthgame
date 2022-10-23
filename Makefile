all: labyrinth
labyrinth: labyrinth.cpp engine.cpp engine.h ncurseslib.h moving.cpp potter.cpp moving.h potter.h game.cpp game.h HiScore.cpp HiScore.h traal.h traal.cpp gnome.h gnome.cpp search.h search.cpp
	g++ labyrinth.cpp engine.cpp game.cpp moving.cpp potter.cpp HiScore.cpp traal.cpp gnome.cpp search.cpp -o labyrinth -lncurses

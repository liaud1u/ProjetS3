SRC= projet.c 
BIN=projet

$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` \
	-I $$HOME/Install/include \
	-L $$HOME/Install/lib \
	-o $(BIN) \
	-lm -lSDL_mixer

clean:
	rm -f $(BIN)
SRC= projet.cpp 
BIN=projet

$(BIN): $(SRC)
	g++ -Wall -g $(SRC) -std=c++98 `sdl-config --cflags --libs` \
	-I $$HOME/Install/include \
	-L $$HOME/Install/lib \
	-o $(BIN) \
	-lm
	
clean:
	rm -f $(BIN)

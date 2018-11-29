SRC= *.cpp 
BIN=projet

$(BIN): $(SRC)
	g++ -Wall -g $(SRC) -std=c++98 -lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -o $(BIN) 
	
clean:
	rm -f $(BIN)

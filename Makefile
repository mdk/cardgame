HEADERS = Src/Card.h Src/CardCollection.h Src/Game.h Src/NumericCard.h Src/player.h

all: cardgame.wasm cardgame

cardgame.wasm: $(HEADERS) Src/WASM.cpp
	emcc -std=c++20 --bind -o cardgame.js Src/WASM.cpp

cardgame: $(HEADERS) src/Cardgame.cpp
	g++ -std=c++20 -o cardgame Src/CardGame.cpp

clean:
	rm -f cardgame
	rm -f cardgame.wasm
	rm -f cardgame.js
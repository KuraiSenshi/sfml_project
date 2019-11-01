g++ -c server.cpp
g++ -c server_main.cpp
g++ -c server_game.cpp
g++ server.o server_main.o server_game.o -o server_app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
./server_app
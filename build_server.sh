g++ -c server.cpp
g++ -c server_main.cpp
g++ -c server_game.cpp
g++ -c laser.cpp
g++ -c meteor.cpp
g++ server.o server_main.o server_game.o laser.o meteor.o -o server_app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
./server_app
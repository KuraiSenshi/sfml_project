g++ -c server_main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
./sfml-app
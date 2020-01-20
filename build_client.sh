g++ -c client_main.cpp
g++ -c client.cpp
g++ -c player.cpp
g++ -c laser.cpp
g++ -c meteor.cpp
g++ client_main.o client.o player.o laser.o meteor.o -o client_app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
./client_app

g++ -c client_main.cpp
g++ client_main.o -o client_app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
./client_app
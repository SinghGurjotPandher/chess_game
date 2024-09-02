#include <SFML/Network.hpp>
#include <vector>

#include <iostream>

int main() {

    sf::TcpListener listener;
    listener.listen(2000);

    sf::SocketSelector selector;
    selector.add(listener);

    std::vector<sf::TcpSocket*> player1;
    std::vector<sf::TcpSocket*> player2;

    while (true) {
        if (selector.wait()) {
            // Add a new player
            if (selector.isReady(listener)) {
                sf::TcpSocket* player = new sf::TcpSocket;
                if (listener.accept(*player) == sf::Socket::Done) {
                    selector.add(*player);
                    int determine_player = player1.size() + player2.size();

                    sf::Packet player_info;
                    if (determine_player % 2 == 0) {
                        player_info << "PLAYER 1";
                        player1.push_back(player);
                    }
                    else {
                        player_info << "PLAYER 2";
                        player2.push_back(player);
                    }
                    player->send(player_info);
                }
            }

            // Check if any of the players have sent something

            // Player 1
            for (int i = 0; i < player1.size(); ++i) {
                if (selector.isReady(*player1[i])) {
                    sf::Packet chess_move;
                    if (player1[i]->receive(chess_move) == sf::Socket::Done) {
                        player2[i]->send(chess_move);
                    }
                }
            }

            // Player 2
            for (int i = 0; i < player2.size(); ++i) {
                if (selector.isReady(*player2[i])) {
                    sf::Packet chess_move;
                    if (player2[i]->receive(chess_move) == sf::Socket::Done) {
                        player1[i]->send(chess_move);
                    }
                }
            }
        }
    }
}
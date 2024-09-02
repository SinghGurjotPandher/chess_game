#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "engine.h"
#include "views.h"

constexpr int WINDOW_SIZE = 700;
int winnerAnnounced = 0;
const std::string TITLE = "Chess Game";

constexpr int other_player = 1;
constexpr int person_player = 2;

sf::TcpSocket socket;
sf::IpAddress ip = sf::IpAddress::getLocalAddress();

void connect(int port) {
    socket.connect(ip, port);
}

void assignPlayerView(ManageView& view, int player) {
    view.assigned_player = player;
    if (player == 2) {
        view.myPieceColor = sf::Color(255,255,255);
        view.opponentPieceColor = sf::Color(96,96,96);
    }
    else {
        view.myPieceColor = sf::Color(96,96,96);
        view.opponentPieceColor = sf::Color(255,255,255);
    }
}

int main() {
    connect(2000);

    sf::Packet player_info;
    std::string set_player;
    if (socket.receive(player_info) == sf::Socket::Done) {
        player_info >> set_player;
        std:: cout << "Joining as " << set_player << std::endl;
    }

    sf::RenderWindow window(
    sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE+100),
    TITLE,
    sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    window.display();

    ManageBoardEngine board;// by defalt this will assign you to player 2
    ManageView view{window, board};
    assignPlayerView(view, 2);

    int count_first = 0;
    while (window.isOpen()) {
        if (winnerAnnounced != 0) {
            view.drawWinner(winnerAnnounced);
            window.display();
        }
        else {
            view.fillBoardTexture();
            view.drawCurrentPiecesState();
        }

        sf::Event event;
        while (window.pollEvent(event)) {

            // for handling the case of accepting the turn of player 1 as player 2
            if (winnerAnnounced == 0) {
                if (set_player == "PLAYER 1" and count_first == 0) {
                    // update to player 1's board pieces because we now know that we are player 1
                    board.populateBoard(1);
                    assignPlayerView(view, 1);

                    view.drawMessage("Wait for player to join & move piece");
                    view.fillBoardTexture();
                    view.drawCurrentPiecesState();

                    sf::Packet data;
                    std::string received;
                    if (socket.receive(data) == sf::Socket::Done) {
                        data >> received;
                    }
                    view.processAddRemoveServerMessage(received, 1, 2);
                    ++count_first;
                }
                else {
                    view.drawMessage("Your turn...");
                    window.display();
                }
            }

            switch (event.type)
            {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }

                case sf::Event::MouseButtonPressed: {
                    if (winnerAnnounced == 0) {
                        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window); // add validation here
                        Bitboard_Point bitboard_point = view.pixels_to_bitboard_point(currentMousePos.x, currentMousePos.y);
                        view.mouseButtonPress(bitboard_point, person_player, socket, winnerAnnounced);

                        // the other player did not announce winner -- so we might have it
                        if (winnerAnnounced == 0) {
                            if (board.isCheckmate()) {
                                winnerAnnounced = 1;
                                sf::Packet lost;
                                lost << "LOST";
                                socket.send(lost);
                            }
                            else if (board.isStalemate()) {
                                winnerAnnounced = 3;
                                sf::Packet lost;
                                lost << "DRAW";
                                socket.send(lost);
                            }
                        }
                    }
                    break;
                }

                default: {
                    break;
                }
            }
        }
    }
    return 0;
}
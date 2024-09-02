#ifndef VIEWS_H
#define VIEWS_H

#include "engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

struct Bitboard_Point {
    int row;
    int column;
};

struct Pixel_Point {
    int x;
    int y;
};

struct Selection {
    int player;
    std::string element;
    Bitboard_Point point;
    bool isActive;

    explicit Selection(int player = 2,
        std::string element = "None",
        Bitboard_Point point = Bitboard_Point{-1,-1},
        bool isActive = false)
        :player(player), element(std::move(element)), point(point), isActive(isActive) { }
};

class ManageView {
    sf::RenderWindow& window;
    ManageBoardEngine& board;
    constexpr static int WINDOW_SIZE = 700;
    constexpr static int PLAYERS = 2;
    const std::string TITLE = "Chess Game";
    constexpr static float CHESS_SIZE = 8;
    const sf::Color light_blue = sf::Color(192, 228, 255);
    const sf::Color blue = sf::Color(0,145,255);
    const sf::Color selected_box = sf::Color(255,153,51);
    constexpr static float BOX_SIZE = WINDOW_SIZE/CHESS_SIZE;
    sf::Texture rook_texture, knight_texture, bishop_texture, king_texture, queen_texture, pawn_texture;
    sf::Sprite rook_sprite, knight_sprite, bishop_sprite, king_sprite, queen_sprite, pawn_sprite;
    sf::SoundBuffer valid_move_buffer, invalid_move_buffer, king_checked_buffer;
    sf::Sound valid_move, invalid_move, king_checked;
    sf::Font font;
    Selection selected;
    bool kingInCheck = false;

public:
    int assigned_player;
    sf::Color myPieceColor;
    sf::Color opponentPieceColor;

    explicit ManageView(sf::RenderWindow& window, ManageBoardEngine& board);
    void fillBoardTexture();
    void drawRook(int player, sf::Vector2f pieceLocation);
    void drawKnight(int player, sf::Vector2f pieceLocation);
    void drawBishop(int player, sf::Vector2f pieceLocation);
    void drawKing(int player, sf::Vector2f pieceLocation);
    void drawQueen(int player, sf::Vector2f pieceLocation);
    void drawPawn(int player, sf::Vector2f pieceLocation);
    void drawCurrentPiecesState();
    void drawMessage(sf::String message);
    void drawPawnPromotion();
    void drawWinMessage(sf::String message, sf::Color background);
    void drawWinner(int playerWon);

    std::string handlePawnPromotion(int player, int moving_to_col, int moving_to_row);
    bool selectPiece(int player, Bitboard_Point bitboard_point);
    void movePiece(Bitboard_Point bitboard_point, sf::TcpSocket& socket, int& winnerAnnounced);
    void mouseButtonPress(Bitboard_Point bitboard_point, int player, sf::TcpSocket& socket, int& winnerAnnounced);
    void addRemoveBoardPieces(std::string operation, std::string piece, int row, int column, int player, int removing_player);
    void processAddRemoveServerMessage(std::string serverMessage, int player, int removing_player);

    static Bitboard_Point pixels_to_bitboard_point(int pixel_x, int pixel_y);
};

#endif //VIEWS_H
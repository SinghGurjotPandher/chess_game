#ifndef ENGINE_H
#define ENGINE_H
#include <functional>
#include <iostream>

struct Legal_Move {
    std::string piece;
    int start_row;
    int start_column;
    int end_row;
    int end_column;
};

struct Temp_Game_State { // used for storing game state and then using it to reset in wayOutCheck() where I need to simulate changes
    long long int c_p1Rooks, c_p1Knights, c_p1Bishops, c_p1King, c_p1Queen, c_p1Pawns;
    long long int c_p2Rooks, c_p2Knights, c_p2Bishops, c_p2King, c_p2Queen, c_p2Pawns;
    long long int c_p1SpecialPawns;
};

class ManageBoardEngine {
    constexpr static int SIZE = 8;
    constexpr static int PLAYERS = 2;
    // Bitboards
    long long int p1Rooks, p1Knights, p1Bishops, p1King, p1Queen, p1Pawns;
    long long int p2Rooks, p2Knights, p2Bishops, p2King, p2Queen, p2Pawns;
    long long int p1SpecialPawns;
    // opponent and player values are only changed when simulating changes from other player's perspective for
    // isKingCheck()
    int opponent = 1;
    int player = 2;

public:
    explicit ManageBoardEngine();
    void resetBoard();
    void populateBoard(int assigned_player);

    // for castling (which is only allowed if move countes for king and rook are 0.
    int rookMoveCountP2 = 0;
    int kingMoveCountP2 = 0;
    bool shortSideCastle = false; // updated when player is assigned in main.cpp
    bool longSideCastle = false; // updated when player is assigned in main.cpp

    void setRook(int player, int row, int column);
    void setKnight(int player, int row, int column);
    void setBishop(int player, int row, int column);
    void setKing(int player, int row, int column);
    void setQueen(int player, int row, int column);
    void setPawn(int player, int row, int column);
    void setSpecialPawn(int row, int column); // only for p1 player

    void removeRook(int player, int row, int column);
    void removeKnight(int player, int row, int column);
    void removeBishop(int player, int row, int column);
    void removeKing(int player, int row, int column);
    void removeQueen(int player, int row, int column);
    void removePawn(int player, int row, int column);
    void removeSpecialPawn(int row, int column); // only for p1 player

    bool rookExists(int player, int row, int column) const;
    bool knightExists(int player, int row, int column) const;
    bool bishopExists(int player, int row, int column) const;
    bool kingExists(int player, int row, int column) const;
    bool queenExists(int player, int row, int column) const;
    bool pawnExists(int player, int row, int column) const;
    bool specialPawnExists(int row, int column); // only for p1 player

    bool isValidVerticallyHorizontally(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidDiagonally(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidRookMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidBishopMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidQueenMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidKnightMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidPawnMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidPawnEnPassantMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);

    bool isValidCastleMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);
    bool isValidKingMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row);

    bool isKingCheck();
    void getLegalRookMoves(std::vector<Legal_Move>& legal_moves, int row, int column);
    void getLegalKnightMoves(std::vector<Legal_Move>& legal_moves, int row, int column);
    void getLegalBishopMoves(std::vector<Legal_Move>& legal_moves, int row, int column);
    void getLegalKingMoves(std::vector<Legal_Move>& legal_moves, int row, int column);
    void getLegalPawnMoves(std::vector<Legal_Move>& legal_moves, int row, int column);
    bool castleMoveValid();
    // and en passant
    std::vector<Legal_Move> getLegalMoves();

    void revertGameState(Temp_Game_State updating_to);
    bool wayOutCheck();
    bool isCheckmate();
    bool isStalemate();

    Temp_Game_State getCurrentGameState();
private:
    static int calculatePosition(int row, int column);
    static long long int createCheck(int row, int column);
};

#endif
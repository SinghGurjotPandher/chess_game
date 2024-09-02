#include "engine.h"


ManageBoardEngine::ManageBoardEngine() {
    populateBoard(2); // you might be reassigned a different player after getting message from the server
}


void ManageBoardEngine::resetBoard() {
    p1Rooks = p1Knights = p1Bishops = p1King = p1Queen = p1Pawns = p2Rooks = p2Knights = p2Bishops = p2King = p2Queen = p2Pawns = 0;
    p1SpecialPawns = 0;
}


void ManageBoardEngine::populateBoard(int assigned_player) {
    resetBoard();
    int row;
    for (int player = 1; player <= PLAYERS; ++player) {
        if (player == 1) row = SIZE-7;
        else row = SIZE;

        setRook(player, row, (SIZE-7));
        setRook(player, row, SIZE);
        setKnight(player,row,(SIZE-6));
        setKnight(player,row,(SIZE-1));
        setBishop(player,row,(SIZE-5));
        setBishop(player,row,(SIZE-2));

        // handle flipping of king and queen for player 1 vs. player 2
        if (assigned_player == 2) { // on your right
            setKing(player, row, (SIZE-4));
            setQueen(player, row, (SIZE-3));
        }

        if (assigned_player == 1) { // on your left
            setKing(player, row, (SIZE-3));
            setQueen(player, row, (SIZE-4));
        }

        for (int i = 1; i <= SIZE; ++i) {
            if (player == 1) setPawn(player,row+1,i);
            else setPawn(player,row-1,i);
        }
    }
}


int ManageBoardEngine::calculatePosition(int row, int column) {
    int addPosition = column + (row * SIZE) - SIZE - 1;
    return addPosition;
}


void ManageBoardEngine::setRook(int player, int row, int column) {
    if (player == 1) p1Rooks |= (1LL << calculatePosition(row, column));
    else p2Rooks |= (1LL << calculatePosition(row, column));
}


void ManageBoardEngine::setKnight(int player, int row, int column) {
    if (player == 1) p1Knights |= (1LL << calculatePosition(row, column));
    else p2Knights |= (1LL << calculatePosition(row, column));
}


void ManageBoardEngine::setBishop(int player, int row, int column) {
    if (player == 1) p1Bishops |= (1LL << calculatePosition(row, column));
    else p2Bishops |= (1LL << calculatePosition(row, column));
}

void ManageBoardEngine::setKing(int player, int row, int column) {
    if (player == 1) p1King |= (1LL << calculatePosition(row, column));
    else p2King |= (1LL << calculatePosition(row, column));
}


void ManageBoardEngine::setQueen(int player, int row, int column) {
    if (player == 1) p1Queen |= (1LL << calculatePosition(row, column));
    else p2Queen |= (1LL << calculatePosition(row, column));
}


void ManageBoardEngine::setPawn(int player, int row, int column) {
    if (player == 1) p1Pawns |= (1LL << calculatePosition(row, column));
    else p2Pawns |= (1LL << calculatePosition(row, column));
}


void ManageBoardEngine::setSpecialPawn(int row, int column) {
    p1SpecialPawns |= (1LL << calculatePosition(row, column));
}


void ManageBoardEngine::removeRook(int player, int row, int column) {
    if (player == 1) p1Rooks &= ~(1LL << calculatePosition(row, column));
    else p2Rooks &= ~(1LL << calculatePosition(row, column));
}


void ManageBoardEngine::removeKnight(int player, int row, int column) {
    if (player == 1) p1Knights &= ~(1LL << calculatePosition(row, column));
    else p2Knights &= ~(1LL << calculatePosition(row, column));
}


void ManageBoardEngine::removeBishop(int player, int row, int column) {
    if (player == 1) p1Bishops &= ~(1LL << calculatePosition(row, column));
    else p2Bishops &= ~(1LL << calculatePosition(row, column));
}


void ManageBoardEngine::removeKing(int player, int row, int column) {
    if (player == 1) p1King &= ~(1LL << calculatePosition(row, column));
    else p2King &= ~(1LL << calculatePosition(row, column));
}


void ManageBoardEngine::removeQueen(int player, int row, int column) {
    if (player == 1) p1Queen &= ~(1LL << calculatePosition(row, column));
    else p2Queen &= ~(1LL << calculatePosition(row, column));
}


void ManageBoardEngine::removePawn(int player, int row, int column) {
    if (player == 1) p1Pawns &= ~(1LL << calculatePosition(row, column));
    else p2Pawns &= ~(1LL << calculatePosition(row, column));
}


void ManageBoardEngine::removeSpecialPawn(int row, int column) {
    p1SpecialPawns &= ~(1LL << calculatePosition(row, column));
}


long long int ManageBoardEngine::createCheck(int row, int column) {
    long long int check = 1LL << calculatePosition(row, column);
    return check;
}


bool ManageBoardEngine::rookExists(int player, int row, int column) const {
    if (player == 1) return (createCheck(row, column) & p1Rooks) != 0;
    return (createCheck(row, column) & p2Rooks) != 0;
}


bool ManageBoardEngine::knightExists(int player, int row, int column) const {
    if (player == 1) return (createCheck(row, column) & p1Knights) != 0;
    return (createCheck(row, column) & p2Knights) != 0;
}


bool ManageBoardEngine::bishopExists(int player, int row, int column) const {
    if (player == 1) return (createCheck(row, column) & p1Bishops) != 0;
    return (createCheck(row, column) & p2Bishops) != 0;
}


bool ManageBoardEngine::kingExists(int player, int row, int column) const {
    if (player == 1) return (createCheck(row, column) & p1King) != 0;
    return (createCheck(row, column) & p2King) != 0;
}


bool ManageBoardEngine::queenExists(int player, int row, int column) const {
    if (player == 1) return (createCheck(row, column) & p1Queen) != 0;
    return (createCheck(row, column) & p2Queen) != 0;
}


bool ManageBoardEngine::pawnExists(int player, int row, int column) const {
    if (player == 1) return (createCheck(row, column) & p1Pawns) != 0;
    return (createCheck(row, column) & p2Pawns) != 0;
}


bool ManageBoardEngine::specialPawnExists(int row, int column) {
    return (createCheck(row, column) & p1SpecialPawns) != 0;
}


bool ManageBoardEngine::isValidVerticallyHorizontally(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    // only used by player 2 -- so need to handle it for different players
    long long int anyPiece = p1Rooks | p1Knights | p1Bishops | p1King | p1Queen | p1Pawns |
        p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;

    if (moving_from_col == moving_to_col && moving_to_row < moving_from_row) {
        // vertical going up
        int n = moving_from_row-1;
        while (n > moving_to_row) {
            if ((createCheck(n, moving_from_col) & anyPiece) != 0) return false;
            --n;
        }
    }
    else if (moving_from_col == moving_to_col && moving_to_row > moving_from_row) {
        // vertical going down
        int n = moving_from_row+1;
        while (n < moving_to_row) {
            if ((createCheck(n, moving_from_col) & anyPiece) != 0) return false;
            ++n;
        }
    }
    else if (moving_from_row == moving_to_row && moving_to_col < moving_from_col) {
        // horizontal right
        int n = moving_from_col-1;
        while (n > moving_to_col) {
            if ((createCheck(moving_from_row, n) & anyPiece) != 0) return false;
            --n;
        }
    }
    else if (moving_from_row == moving_to_row && moving_to_col > moving_from_col) {
        // horizontal left
        int n = moving_from_col+1;
        while (n < moving_to_col) {
            if ((createCheck(moving_from_row, n) & anyPiece) != 0) return false;
            ++n;
        }
    }
    else return false;

    return true;
}


bool ManageBoardEngine::isValidDiagonally(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    // finding slope to find invalid moves
    if (std::abs(static_cast<double>(moving_from_row - moving_to_row) / (moving_from_col - moving_to_col) ) != 1)
        return false;

    // determining if any piece comes in the away when going from moving_from to moving_to
    long long int anyPiece = p1Rooks | p1Knights | p1Bishops | p1King | p1Queen | p1Pawns |
        p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;
    int current_col = moving_from_col;
    int current_row = moving_from_row;

    while (current_col != moving_to_col && current_row != moving_to_row) {

        if ((createCheck(current_row, current_col) & anyPiece) != 0 &&
            current_col != moving_from_col &&
            current_row != moving_from_row)
            return false;

        if (current_col < moving_to_col) ++current_col;
        else --current_col;

        if (current_row < moving_to_row) ++current_row;
        else --current_row;
    }
    return true;
}


bool ManageBoardEngine::isValidRookMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    return isValidVerticallyHorizontally(moving_from_col, moving_from_row, moving_to_col, moving_to_row);
}


bool ManageBoardEngine::isValidBishopMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    return isValidDiagonally(moving_from_col, moving_from_row, moving_to_col, moving_to_row);
}


bool ManageBoardEngine::isValidQueenMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    return isValidDiagonally(moving_from_col, moving_from_row, moving_to_col, moving_to_row) ||
        isValidVerticallyHorizontally(moving_from_col, moving_from_row, moving_to_col, moving_to_row);
}


bool ManageBoardEngine::isValidKnightMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    // +/- 2 rows && +/- 1 column
    if (((moving_to_row - 2) == moving_from_row || (moving_to_row + 2) == moving_from_row) &&
        ((moving_to_col - 1) == moving_from_col || (moving_to_col + 1) == moving_from_col))
        return true;

    // +/- 2 cols && +/- 1 row
    if (((moving_to_col - 2) == moving_from_col || (moving_to_col + 2) == moving_from_col) &&
        ((moving_to_row - 1) == moving_from_row || (moving_to_row + 1) == moving_from_row))
        return true;

    return false;
}


bool ManageBoardEngine::isValidPawnMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    long long int anyPiece = p1Rooks | p1Knights | p1Bishops | p1King | p1Queen | p1Pawns |
        p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;
    bool empty = (createCheck(moving_to_row, moving_to_col) & anyPiece) == 0;

    // if straight (one or (two and first_time)) and empty -> return true
    if (moving_from_col == moving_to_col &&
        (player == 2 ? (moving_to_row == moving_from_row - 1 || (moving_to_row == moving_from_row - 2 && moving_from_row == 7)) :
            (moving_to_row == moving_from_row + 1 || (moving_to_row == moving_from_row + 2 && moving_from_row == 2)
        ) &&
        empty)) {
        return true;
    }

    long long int opponent_pieces;
    if (opponent == 1) opponent_pieces = p1Rooks | p1Knights | p1Bishops | p1King | p1Queen | p1Pawns;
    else opponent_pieces = p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;
    bool opponentPieceExists = (createCheck(moving_to_row, moving_to_col) & opponent_pieces) != 0;

    // if diagonal by 1 and opponent's piece exists -> return true  (here I had assumed that anyPiece thing
    if ( (moving_to_col == moving_from_col + 1 || moving_to_col == moving_from_col-1) &&
        (player == 2 ? moving_to_row == moving_from_row - 1 : moving_to_row == moving_from_row + 1 ) &&
        opponentPieceExists)
        return true;
    return false;
}


bool ManageBoardEngine::isValidPawnEnPassantMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    long long int anyPiece = p1Rooks | p1Knights | p1Bishops | p1King | p1Queen | p1Pawns |
        p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;
    bool empty = (createCheck(moving_to_row, moving_to_col) & anyPiece) == 0;

    if (moving_from_row == 4 and moving_to_row == 3 and (moving_to_col == moving_from_col + 1 || moving_to_col == moving_from_col - 1 ) && empty) { // this empty is for diagonal move's destination to make sure its empty because a piece isn't allowed to attack two pieces at once
        if (specialPawnExists(moving_from_row, moving_to_col)) return true;
    }
    return false;
}


bool ManageBoardEngine::isValidKingMove(int moving_from_col, int moving_from_row, int moving_to_col, int moving_to_row) {
    Temp_Game_State startGameState = getCurrentGameState();
    int colDif = std::abs(moving_to_col - moving_from_col);
    int rowDif = std::abs(moving_to_row - moving_from_row);

    if (colDif <= 1 and rowDif <= 1) {
        // check if there is a king in the surroundings since that is not allowed
        // a move that puts a king into the boundaries of opponent's king in check is never allowed
        // (this is not tested for by isKingCheck()) but a move leading to this is just invalid

        bool moving_to_row_minus = (moving_to_row-1 >= 1), moving_to_row_add = (moving_to_row+1 <= 8);
        bool moving_to_col_add = (moving_to_col+1 <= 8), moving_to_col_minus = (moving_to_col-1 >= 1);

        // no need to revertGameState because nothing was changed
        if ((kingExists(opponent, moving_to_row-1, moving_to_col) and moving_to_row_minus) ||
            (kingExists(opponent, moving_to_row-1, moving_to_col+1) and moving_to_row_minus and moving_to_col_add) ||
            (kingExists(opponent, moving_to_row-1, moving_to_col-1) and moving_to_row_minus and moving_to_col_minus) ||
            (kingExists(opponent, moving_to_row, moving_to_col+1) and moving_to_col_add) ||
            (kingExists(opponent, moving_to_row, moving_to_col-1) and moving_to_col_minus) ||
            (kingExists(opponent, moving_to_row+1, moving_to_col) and moving_to_row_add) ||
            (kingExists(opponent, moving_to_row+1, moving_to_col-1) and moving_to_row_add and moving_to_col_minus) ||
            (kingExists(opponent, moving_to_row+1, moving_to_col+1) and moving_to_row_add and moving_to_col_add)
        ) return false;

        // simulating change, therefore requires reverting to original state
        removeKing(player, moving_from_row, moving_from_col);
        setKing(player, moving_to_row, moving_to_col);
        bool kingInCheck = isKingCheck();
        revertGameState(startGameState);

        if (kingInCheck) return false;
        return true;
    }

    revertGameState(startGameState);
    return false;
}


bool ManageBoardEngine::isKingCheck() {
    int kingRow;
    int kingCol;

    // switching player roles to simulate the perspective of the other player and determine whether any of their
    // roles are putting our king in check
    opponent = 2, player = 1;

    // finding the row, col of the p2's king's current position
    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col) {
            if (kingExists(2, row, col)) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }

    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col) {
            /*
             a king is not allowed to place another king in check because that would lead to conflict in my game
            and also isn't allowed in chess since that would put our own king in check.
            this leads into infinite loop
            */

            if ((rookExists(player, row, col) && isValidRookMove(col, row, kingCol, kingRow)) ||
                (knightExists(player, row, col) && isValidKnightMove(col, row, kingCol, kingRow)) ||
                (bishopExists(player, row, col) && isValidBishopMove(col, row, kingCol, kingRow)) ||
                (queenExists(player, row, col) && isValidQueenMove(col, row, kingCol, kingRow)) ||
                (pawnExists(player, row, col) && isValidPawnMove(col, row, kingCol, kingRow))) {
                opponent = 1, player = 2;
                return true;
            }
        }
    }
    opponent = 1, player = 2;
    return false;
}


void ManageBoardEngine::getLegalRookMoves(std::vector<Legal_Move>& legal_moves, int row, int column) {
    long long int piecesP2 = p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;

    for (int to_row = 1; to_row <= 8; ++to_row) {
        if ((createCheck(to_row, column) & piecesP2) == 0 && isValidRookMove(column, row, column, to_row))
            legal_moves.push_back(Legal_Move{"Rook", row, column, to_row, column});
    }
    for (int to_col = 1; to_col <= 8; ++to_col) {
        if ((createCheck(row, to_col) & piecesP2) == 0 && isValidRookMove(column, row, to_col, row))
            legal_moves.push_back(Legal_Move{"Rook", row, column, row, to_col});
    }
}


void ManageBoardEngine::getLegalKnightMoves(std::vector<Legal_Move> &legal_moves, int row, int column) {
    long long int piecesP2 = p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;

    bool minusTwoRow = (row-2 >= 1);
    bool addTwoRow = (row+2 <= 8);

    bool minusOneRow = (row-1 >= 1);
    bool addOneRow = (row+1 <= 8);

    bool minusTwoCol = (column-2 >= 1);
    bool addTwoCol = (column+2 <= 8);

    bool minusOneCol = (column-1 >= 1);
    bool addOneCol = (column+1 <= 8);

    if (addTwoRow && minusOneCol && (createCheck(row+2, column-1) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight", row, column, row+2, column-1});
    if (addTwoRow && addOneCol && (createCheck(row+2, column+1) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight",row, column, row+2, column+1});

    if (minusTwoRow && minusOneCol && (createCheck(row-2, column-1) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight",row, column, row-2, column-1});
    if (minusTwoRow && addOneCol && (createCheck(row-2, column+1) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight",row, column, row-2, column+1});

    if (addTwoCol && minusOneRow && (createCheck(row-1, column+2) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight",row, column, row-1, column+2});
    if (addTwoCol && addOneRow && (createCheck(row+1, column+2) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight",row, column, row+1, column+2});

    if (minusTwoCol && minusOneRow && (createCheck(row-1, column-2) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight",row, column, row-1, column-2});
    if (minusTwoCol && addOneRow && (createCheck(row+1, column-2) & piecesP2) == 0) legal_moves.push_back(Legal_Move{"Knight",row, column, row+1, column-2});
}


void ManageBoardEngine::getLegalBishopMoves(std::vector<Legal_Move> &legal_moves, int row, int column) {
    long long int piecesP2 = p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;

    // ++row ++col
    for (int to_row = row, to_col = column; to_row <= 8 && to_col <= 8; ++to_row, ++to_col) {
        if (isValidBishopMove(column, row, to_col, to_row) && (createCheck(to_row, to_col) & piecesP2) == 0) {
            legal_moves.push_back(Legal_Move{"Bishop", row, column, to_row, to_col});
        }
    }

    // --row --col
    for (int to_row = row, to_col = column; to_row >= 1 && to_col >= 1; --to_row, --to_col) {
        if (isValidBishopMove(column, row, to_col, to_row) && (createCheck(to_row, to_col) & piecesP2) == 0) {
            legal_moves.push_back(Legal_Move{"Bishop",row, column, to_row, to_col});
        }
    }

    // ++row --col
    for (int to_row = row, to_col = column; to_row <= 8 && to_col >= 1; ++to_row, --to_col) {
        if (isValidBishopMove(column, row, to_col, to_row) && (createCheck(to_row, to_col) & piecesP2) == 0) {
            legal_moves.push_back(Legal_Move{"Bishop",row, column, to_row, to_col});
        }
    }

    // --row ++col
    for (int to_row = row, to_col = column; to_row >= 1 && to_col <= 8; --to_row, ++to_col) {
        if (isValidBishopMove(column, row, to_col, to_row) && (createCheck(to_row, to_col) & piecesP2) == 0) {
            legal_moves.push_back(Legal_Move{"Bishop",row, column, to_row, to_col});
        }
    }
}
// any move that leaves your king in check is not allowed... so you need to check all moves :(

void ManageBoardEngine::getLegalKingMoves(std::vector<Legal_Move> &legal_moves, int row, int column) {
    long long int piecesP1 = p1Rooks | p1Knights | p1Bishops | p1King | p1Queen | p1Pawns;

    bool minusOneRow = (row-1 >= 1);
    bool addOneRow = (row+1 <= 8);

    bool minusOneCol = (column-1 >= 1);
    bool addOneCol = (column+1 <= 8);

    if (addOneRow && addOneCol && (createCheck(row+1, column+1) & piecesP1) == 0 && isValidKingMove(column, row, column+1, row+1)) {
        legal_moves.push_back(Legal_Move{"King", row, column, row+1, column+1});
    }
    if (addOneRow && (createCheck(row+1, column) & piecesP1) == 0 && isValidKingMove(column, row, column, row+1)) {
        legal_moves.push_back(Legal_Move{"King", column, row+1, column});
    }
    if (addOneRow && (createCheck(row+1, column-1) & piecesP1) == 0 && minusOneCol && isValidKingMove(column, row, column-1, row+1)) {
        legal_moves.push_back(Legal_Move{"King", column, row+1, column-1});
    }
    if (minusOneCol && (createCheck(row, column-1) & piecesP1) == 0 && isValidKingMove(column, row, column-1, row)) {
        legal_moves.push_back(Legal_Move{"King",  column, row, column-1});
    }
    if (addOneCol && (createCheck(row, column+1) & piecesP1) == 0 && isValidKingMove(column, row, column+1, row)) {
        legal_moves.push_back(Legal_Move{"King", column, row, column+1});
    }
    if (minusOneRow && (createCheck(row-1, column-1) & piecesP1) == 0 && minusOneCol && isValidKingMove(column, row, column-1, row-1)) {
        legal_moves.push_back(Legal_Move{"King",  column, row-1, column-1});
    }
    if (minusOneRow && (createCheck(row-1, column+1) & piecesP1) == 0 && addOneCol && isValidKingMove(column, row, column+1, row-1)) {
        legal_moves.push_back(Legal_Move{"King", column, row-1, column+1});
    }
    if (minusOneRow && (createCheck(row-1, column) & piecesP1) == 0 && isValidKingMove(column, row, column, row-1)) {
        legal_moves.push_back(Legal_Move{"King",  column, row-1, column});
    }
}

void ManageBoardEngine::getLegalPawnMoves(std::vector<Legal_Move> &legal_moves, int row, int column) {
    bool minusOneRow = (row-1 >= 1);
    bool minusTwoRow = (row-1 >= 1);

    bool minusOneCol = (column-1 >= 1);
    bool addOneCol = (column+1 <= 8);

    long long int piecesP2 = p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;
    long long int piecesP1P2 = p1Rooks | p1Knights | p1Bishops | p1King | p1Queen | p1Pawns |
        p2Rooks | p2Knights | p2Bishops | p2King | p2Queen | p2Pawns;

    // move one forward
    if (minusOneRow && (createCheck(row-1, column) & piecesP1P2) == 0 && isValidPawnMove(column, row, column, row-1)) {
        legal_moves.push_back(Legal_Move{"Pawn", row, column, row-1, column});
    }

    // move two forward
    if (minusTwoRow && (createCheck(row-2, column) & piecesP1P2) == 0 && isValidPawnMove(column, row, column, row-2)) {
        legal_moves.push_back(Legal_Move{"Pawn",row, column, row-2, column});
    }

    // move one right diagonal
    if (minusOneRow && (createCheck(row-1, column-1) & piecesP2) == 0 && minusOneCol && (isValidPawnMove(column, row, column-1, row-1) ||
        isValidPawnEnPassantMove(column, row, column-1, row-1))) {
        legal_moves.push_back(Legal_Move{"Pawn",row, column, row-1, column-1});
    }

    // move one left diagonal
    if (minusOneRow && (createCheck(row-1, column+1) & piecesP2) == 0 && addOneCol && (isValidPawnMove(column, row, column+1,row-1) ||
        isValidPawnEnPassantMove(column, row, column+1, row-1))) {
        legal_moves.push_back(Legal_Move{"Pawn",row, column, row-1, column+1});
    }
}


std::vector<Legal_Move> ManageBoardEngine::getLegalMoves() {
    std::vector<Legal_Move> legal_moves;

    for (int row = 1; row <= 8; ++row) {
        for (int column = 1; column <= 8; ++column) {
            if (rookExists(player, row, column)) getLegalRookMoves(legal_moves, row, column);
            else if (knightExists(player, row, column)) getLegalKnightMoves(legal_moves, row, column);
            else if (bishopExists(player, row, column)) getLegalBishopMoves(legal_moves, row, column);
            else if (kingExists(player, row, column)) getLegalKingMoves(legal_moves, row, column);
            else if (queenExists(player, row, column)) {
                getLegalRookMoves(legal_moves, row, column);
                getLegalBishopMoves(legal_moves, row, column);
            }
            else if (pawnExists(player, row, column)) getLegalPawnMoves(legal_moves, row, column);
        }
    }
    return legal_moves;
}


void ManageBoardEngine::revertGameState(Temp_Game_State updating_to) {
    p1Rooks = updating_to.c_p1Rooks;
    p1Knights = updating_to.c_p1Knights;
    p1Bishops = updating_to.c_p1Bishops;
    p1King = updating_to.c_p1King;
    p1Queen = updating_to.c_p1Queen;
    p1Pawns = updating_to.c_p1Pawns;

    p2Rooks = updating_to.c_p2Rooks;
    p2Knights = updating_to.c_p2Knights;
    p2Bishops = updating_to.c_p2Bishops;
    p2King = updating_to.c_p2King;
    p2Queen = updating_to.c_p2Queen;
    p2Pawns = updating_to.c_p2Pawns;

    p1SpecialPawns = updating_to.c_p1SpecialPawns;
}


bool ManageBoardEngine::wayOutCheck() {
    // storing game's start state
    Temp_Game_State startGameState = getCurrentGameState();

    bool wayOutCheckPossible = false;
    std::vector<Legal_Move> legalMoves = getLegalMoves();
    std::cout << "Legal Moves Available: " << legalMoves.size() << std::endl;
    for (std::vector<Legal_Move>::iterator p = legalMoves.begin(); p != legalMoves.end(); ++p) {
        std::cout << "Piece:           " << p->piece << std::endl;
        std::cout << "  Start Column:  " << p->start_column << std::endl;
        std::cout << "  Start Row:     " << p->start_row << std::endl;
        std::cout << "  End Column:    " << p->end_column << std::endl;
        std::cout << "  End Row:       " << p->end_row << std::endl;
    }

    // try all possible moves and see if any can remove the game out of check (simulating changes)
    for (std::vector<Legal_Move>::iterator p = legalMoves.begin(); p != legalMoves.end(); ++p) {
        if (isKingCheck()) {
            if (p->piece == "Rook") {
                removeRook(player, p->start_row, p->start_column);
                setRook(player, p->end_row, p->end_column);
            }
            else if (p->piece == "Knight") {
                removeKnight(player, p->start_row, p->start_column);
                setKnight(player, p->end_row, p->end_column);
            }
            else if (p->piece == "Bishop") {
                removeBishop(player,p->start_row, p->start_column);
                setBishop(player, p->end_row, p->end_column);
            }
            else if (p->piece == "King") {
                removeKing(player, p->start_row, p->start_column);
                setKing(player, p->end_row, p->end_column);
            }
            else if (p->piece == "Queen") {
                removeQueen(player, p->start_row, p->start_column);
                setQueen(player, p->end_row, p->end_column);
            }
            else if (p->piece == "Pawn") {
                removePawn(player, p->start_row, p->start_column);
                setPawn(player, p->end_row, p->end_column);
            }

            removeRook(opponent, p->end_row, p->end_column);
            removeKnight(opponent, p->end_row, p->end_column);
            removeBishop(opponent, p->end_row, p->end_column);
            removeKing(opponent, p->end_row, p->end_column);
            removeQueen(opponent, p->end_row, p->end_column);
            removePawn(opponent, p->end_row, p->end_column);

            if (isKingCheck()) {
                revertGameState(startGameState);
            }
            else {
                wayOutCheckPossible = true;
                break;
            }
        }
        else {
            wayOutCheckPossible = true;
            break;
        }
    }
    revertGameState(startGameState);
    return wayOutCheckPossible;
}

bool ManageBoardEngine::isCheckmate() {
    if (isKingCheck() and !wayOutCheck()) return true;
    return false;
}


bool ManageBoardEngine::isStalemate() {
    if (getLegalMoves().empty() and !isKingCheck()) return true;
    return false;
}


Temp_Game_State ManageBoardEngine::getCurrentGameState() {
    return Temp_Game_State {p1Rooks, p1Knights, p1Bishops, p1King, p1Queen, p1Pawns, p2Rooks, p2Knights, p2Bishops, p2King, p2Queen, p2Pawns, p1SpecialPawns };
}
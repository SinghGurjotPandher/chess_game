#include "views.h"


ManageView::ManageView(sf::RenderWindow& window, ManageBoardEngine& board)
    :window(window), board(board) {
    rook_texture.loadFromFile("../pieces/rook.png");
    rook_sprite.setTexture(rook_texture);
    knight_texture.loadFromFile("../pieces/knight.png");
    knight_sprite.setTexture(knight_texture);
    bishop_texture.loadFromFile("../pieces/bishop.png");
    bishop_sprite.setTexture(bishop_texture);
    king_texture.loadFromFile("../pieces/king.png");
    king_sprite.setTexture(king_texture);
    queen_texture.loadFromFile("../pieces/queen.png");
    queen_sprite.setTexture(queen_texture);
    pawn_texture.loadFromFile("../pieces/pawn.png");
    pawn_sprite.setTexture(pawn_texture);
    valid_move_buffer.loadFromFile("../sounds/piece_move.mp3");
    valid_move.setBuffer(valid_move_buffer);
    invalid_move_buffer.loadFromFile("../sounds/invalid_move.mp3");
    invalid_move.setBuffer(invalid_move_buffer);
    king_checked_buffer.loadFromFile("../sounds/king_check.mp3");
    king_checked.setBuffer(king_checked_buffer);
    font.loadFromFile("../arial.ttf");
}


void ManageView::fillBoardTexture() {
    for (int i = 0; i < CHESS_SIZE; ++i) {
        for (int j = 0; j < CHESS_SIZE; ++j) {
            sf::RectangleShape box(sf::Vector2f(BOX_SIZE, BOX_SIZE));
            box.setPosition(sf::Vector2f((BOX_SIZE * i), (BOX_SIZE * j)));

            if (i == (8 - selected.point.column) &&
                j == (selected.point.row - 1) &&
                selected.isActive == true)
                box.setFillColor(selected_box);
            else {
                if ((i + j) % 2) box.setFillColor(blue);
                else box.setFillColor(light_blue);
            }

            window.draw(box);
        }
    }
}


void ManageView::drawRook(int player, sf::Vector2f pieceLocation) {
    if (player == 1) rook_sprite.setColor(opponentPieceColor);
    else rook_sprite.setColor(myPieceColor);
    rook_sprite.setPosition(pieceLocation);
    window.draw(rook_sprite);
}


void ManageView::drawKnight(int player, sf::Vector2f pieceLocation) {
    if (player == 1) knight_sprite.setColor(opponentPieceColor);
    else knight_sprite.setColor(myPieceColor);
    knight_sprite.setPosition(pieceLocation);
    window.draw(knight_sprite);
}


void ManageView::drawBishop(int player, sf::Vector2f pieceLocation) {
    if (player == 1) bishop_sprite.setColor(opponentPieceColor);
    else bishop_sprite.setColor(myPieceColor);
    bishop_sprite.setPosition(pieceLocation);
    window.draw(bishop_sprite);
}


void ManageView::drawKing(int player, sf::Vector2f pieceLocation) {
    if (player == 1) king_sprite.setColor(opponentPieceColor);
    else kingInCheck ? king_sprite.setColor(sf::Color(255,0,0)) : king_sprite.setColor(myPieceColor);
    king_sprite.setPosition(pieceLocation);
    window.draw(king_sprite);
}


void ManageView::drawQueen(int player, sf::Vector2f pieceLocation) {
    if (player == 1) queen_sprite.setColor(opponentPieceColor);
    else queen_sprite.setColor(myPieceColor);
    queen_sprite.setPosition(pieceLocation);
    window.draw(queen_sprite);
}


void ManageView::drawPawn(int player, sf::Vector2f pieceLocation) {
    if (player == 1) pawn_sprite.setColor(opponentPieceColor);
    else pawn_sprite.setColor(myPieceColor);
    pawn_sprite.setPosition(pieceLocation);
    window.draw(pawn_sprite);
}


void ManageView::drawCurrentPiecesState() {
    // Keeping track of two indices: rows/columns in SFML chess board and in Engine
    for (int row_pos = 0, bit_row_pos = 1;
        row_pos < CHESS_SIZE && bit_row_pos <= CHESS_SIZE;
        ++row_pos, ++bit_row_pos) {
        for (int column_pos = 0, bit_column_pos = CHESS_SIZE;
            column_pos < CHESS_SIZE && bit_column_pos >= 1;
            ++column_pos, --bit_column_pos) {
            sf::Vector2f pieceLocation = sf::Vector2f((BOX_SIZE * column_pos), (BOX_SIZE * row_pos));
            for (int player = 0 ; player < PLAYERS; ++player) {
                if (board.rookExists(player, bit_row_pos, bit_column_pos))
                    drawRook(player, pieceLocation);
                else if (board.knightExists(player, bit_row_pos, bit_column_pos))
                    drawKnight(player, pieceLocation);
                else if (board.bishopExists(player, bit_row_pos, bit_column_pos))
                    drawBishop(player, pieceLocation);
                else if (board.kingExists(player, bit_row_pos, bit_column_pos))
                    drawKing(player, pieceLocation);
                else if (board.queenExists(player, bit_row_pos, bit_column_pos))
                    drawQueen(player, pieceLocation);
                else if (board.pawnExists(player, bit_row_pos, bit_column_pos))
                    drawPawn(player, pieceLocation);
            }
        }
    }
    window.display();
}


void ManageView::drawMessage(sf::String message) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(700,100));
    rectangle.setPosition(sf::Vector2f(0,700));
    rectangle.setFillColor(sf::Color::Blue);
    window.draw(rectangle);

    sf::Text text(message, font);
    text.setCharacterSize(45);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(0,700);

    window.draw(text);
}


void ManageView::drawPawnPromotion() {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(700,100));
    rectangle.setPosition(sf::Vector2f(0,700));
    rectangle.setFillColor(sf::Color::Blue);
    window.draw(rectangle);

    sf::Text text("Pawn Promotion", font);
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(0,700));
    window.draw(text);

    // Queen
    queen_sprite.setPosition(sf::Vector2f(612.5,700));
    queen_sprite.setColor(myPieceColor);
    window.draw(queen_sprite);
    // Rook
    rook_sprite.setPosition(sf::Vector2f(525, 700));
    rook_sprite.setColor(myPieceColor);
    window.draw(rook_sprite);
    // Bishop
    bishop_sprite.setPosition(sf::Vector2f(437.5, 700));
    bishop_sprite.setColor(myPieceColor);
    window.draw(bishop_sprite);
    // Knight
    knight_sprite.setPosition(sf::Vector2f(350, 700));
    knight_sprite.setColor(myPieceColor);
    window.draw(knight_sprite);

    window.display();
}


void ManageView::drawWinMessage(sf::String message, sf::Color background) {
    sf::RectangleShape cover;
    cover.setSize(sf::Vector2f(700,100));
    cover.setPosition(sf::Vector2f(0,700));
    cover.setFillColor(background);
    window.draw(cover);

    sf::Text winMessage(message, font);
    winMessage.setCharacterSize(50);;
    winMessage.setStyle(sf::Text::Bold);
    winMessage.setFillColor(sf::Color::White);
    winMessage.setPosition(100, 700);

    window.draw(winMessage);
}


void ManageView::drawWinner(int playerWon) {
    if (playerWon == 1) drawWinMessage("You Lost", sf::Color::Red);
    else if (playerWon == 2) drawWinMessage("You Won", sf::Color::Green);
    else drawWinMessage("Draw", sf::Color::Yellow);
}


std::string ManageView::handlePawnPromotion(int player, int moving_to_col, int moving_to_row) {
    sf::Event event;
    std::string pawnPromotingTo = "";

    while (pawnPromotingTo != "Queen" and pawnPromotingTo != "Rook" and pawnPromotingTo != "Bishop" and pawnPromotingTo != "Knight") {
        drawPawnPromotion();
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                    if (currentMousePos.y >= 700) {
                        double x_pos = currentMousePos.x;
                        if (x_pos >= 612.5) pawnPromotingTo = "Queen";
                        else if (x_pos >= 525) pawnPromotingTo = "Rook";
                        else if (x_pos >= 437.5) pawnPromotingTo = "Bishop";
                        else if (x_pos >= 350) pawnPromotingTo = "Knight";
                        else invalid_move.play();
                    }
                    else invalid_move.play();
                }
            }
        }
    }
    return pawnPromotingTo;
}


Bitboard_Point ManageView::pixels_to_bitboard_point(int pixel_x, int pixel_y) {
    int column = ((WINDOW_SIZE - pixel_x) / (WINDOW_SIZE / CHESS_SIZE)) + 1;
    int row = (pixel_y / (WINDOW_SIZE / CHESS_SIZE)) + 1;
    return Bitboard_Point{row,column};
}


bool ManageView::selectPiece(int player, Bitboard_Point bitboard_point) {
    // Return true if the selected piece was changed otherwise return false
    if (board.rookExists(player, bitboard_point.row, bitboard_point.column))
        selected = Selection{player, "Rook", bitboard_point, true};
    else if (board.knightExists(player, bitboard_point.row, bitboard_point.column))
        selected = Selection{player, "Knight", bitboard_point, true};
    else if (board.bishopExists(player, bitboard_point.row, bitboard_point.column))
        selected = Selection{player, "Bishop", bitboard_point, true};
    else if (board.kingExists(player, bitboard_point.row, bitboard_point.column))
        selected = Selection{player, "King", bitboard_point, true};
    else if (board.queenExists(player, bitboard_point.row, bitboard_point.column))
        selected = Selection{player, "Queen", bitboard_point, true};
    else if (board.pawnExists(player, bitboard_point.row, bitboard_point.column))
        selected = Selection{player, "Pawn", bitboard_point, true};
    else
        return false;
    return true;
}


void ManageView::movePiece(Bitboard_Point bitboard_point, sf::TcpSocket& socket, int& winnerAnnounced) {
    bool move_valid;
    std::string pawnPromotingTo;
    bool enPassant;

    if ((selected.element == "Rook" &&
        board.isValidRookMove(selected.point.column, selected.point.row, bitboard_point.column, bitboard_point.row)) ||
        (selected.element == "Knight" &&
        board.isValidKnightMove(selected.point.column, selected.point.row, bitboard_point.column, bitboard_point.row)) ||
        (selected.element == "Bishop" &&
        board.isValidBishopMove(selected.point.column, selected.point.row, bitboard_point.column, bitboard_point.row)) ||
        (selected.element == "Queen" &&
        board.isValidQueenMove(selected.point.column, selected.point.row, bitboard_point.column, bitboard_point.row))
    )
        move_valid = true;

    else if (selected.element == "King" &&
        board.isValidKingMove(selected.point.column, selected.point.row, bitboard_point.column, bitboard_point.row))
        move_valid = true;

    else if (selected.element == "Pawn" &&
        board.isValidPawnMove(selected.point.column, selected.point.row, bitboard_point.column, bitboard_point.row)) {
        move_valid = true;
        if (bitboard_point.row == 1)
            pawnPromotingTo = handlePawnPromotion(selected.player, bitboard_point.column, bitboard_point.row);

    }
    // handle special case of en passant
    else if (selected.element == "Pawn" &&
        board.isValidPawnEnPassantMove(selected.point.column, selected.point.row, bitboard_point.column, bitboard_point.row)) {
        move_valid = true;
        enPassant = true;
    }

    else {
        move_valid = false;
    }

    if (move_valid == false) {
        invalid_move.play();
    }
    else {
        valid_move.play();
        selected.isActive = false;

        std::string removing_element;
        std::string adding_element;

        if (!(selected.element == "Pawn" and bitboard_point.row == 1)) {
            removing_element = selected.element;
            adding_element = selected.element;
        }
        else {
            removing_element = selected.element;
            adding_element = pawnPromotingTo;
        }

        Temp_Game_State startGameState = board.getCurrentGameState();
        addRemoveBoardPieces("Remove", removing_element, selected.point.row, selected.point.column, 2, 1);
        addRemoveBoardPieces("Add", adding_element, bitboard_point.row, bitboard_point.column, 2, 1);
        if (enPassant) {
            board.removeSpecialPawn(selected.point.row, bitboard_point.column); // update our tracking of special pawns
            board.removePawn(1, selected.point.row, bitboard_point.column);
        }
        bool putsKingInCheck = board.isKingCheck();

        if (kingInCheck) {
            if (board.isKingCheck()) {
                // king still in check
                king_checked.play();
                board.revertGameState(startGameState);
                return;
            }
            kingInCheck = false;
        }
        else if (putsKingInCheck) {
            // king put in check
            invalid_move.play();
            board.revertGameState(startGameState);
            return;
        }

        fillBoardTexture();
        drawMessage("Other player's turn...");
        drawCurrentPiecesState();

        // other player: determining the piece locations for the other player to let them know where to make changes
        std::string removing_row = std::to_string(9 - selected.point.row);
        std::string removing_col = std::to_string(9 - selected.point.column);
        std::string adding_row = std::to_string(9 - bitboard_point.row);
        std::string adding_col = std::to_string(9 - bitboard_point.column);

        std::string moveMessage;
        moveMessage = "Remove " + removing_element + " " + removing_row + " " + removing_col + " Add " +
            adding_element + " " + adding_row + " " + adding_col;

        if (enPassant) {
            moveMessage += " En_Passant " + removing_row + " " + adding_col;
        }
        sf::Packet info;
        info << moveMessage;
        socket.send(info);

        // asking other player which changes they made
        sf::Packet data;
        std::string received;
        if (socket.receive(data) == sf::Socket::Done) {
            data >> received;
        }

        if (received == "LOST") {
            winnerAnnounced = 2;
            return;
        }
        if (received == "DRAW") {
            winnerAnnounced = 3;
            return;
        }

        // updating other player's changes on our board
        processAddRemoveServerMessage(received, 1, 2);

        bool inCheck = board.isKingCheck();
        if (inCheck) {
            std::cout << "King in check" << std::endl;
            kingInCheck = true;
            king_checked.play();
        }

    }
}

void ManageView::mouseButtonPress(Bitboard_Point bitboard_point, int player, sf::TcpSocket& socket, int& winnerAnnounced) {
    if (!selectPiece(player, bitboard_point)) {
        if (selected.isActive == true) movePiece(bitboard_point, socket, winnerAnnounced);
    }
}

void ManageView::addRemoveBoardPieces(std::string operation, std::string piece, int row, int column, int player, int removing_player) {
    if (operation == "Remove") {
        if (piece == "Rook") board.removeRook(player, row, column);
        else if (piece == "Knight") board.removeKnight(player, row, column);
        else if (piece == "Bishop") board.removeBishop(player, row, column);
        else if (piece == "King") board.removeKing(player, row, column);
        else if (piece == "Queen") board.removeQueen(player, row, column);
        else if (piece == "Pawn") board.removePawn(player, row, column);
    }
    else if (operation == "Add") {
        if (piece == "Rook") board.setRook(player, row, column);
        else if (piece == "Knight") board.setKnight(player, row, column);
        else if (piece == "Bishop") board.setBishop(player, row, column);
        else if (piece == "King") board.setKing(player, row, column);
        else if (piece == "Queen") board.setQueen(player, row, column);
        else if (piece == "Pawn") board.setPawn(player, row, column);
    }

    // removing opponent player's pieces at the position you striked
    board.removeRook(removing_player, row, column);
    board.removeKnight(removing_player, row, column);
    board.removeBishop(removing_player, row, column);
    board.removeKing(removing_player, row, column);
    board.removeQueen(removing_player, row, column);
    board.removePawn(removing_player, row, column);
}


void ManageView::processAddRemoveServerMessage(std::string serverMessage, int player, int removing_player) {
    // only used for player 1
    std::vector<std::string> messageParts;
    std::istringstream message(serverMessage);
    std::string word;

    while (message >> word) messageParts.push_back(word);

    std::vector<std::string> first_part;
    std::vector<std::string> second_part;

    std::copy(messageParts.begin(), messageParts.begin() + 4, std::back_inserter(first_part));
    std::copy(messageParts.begin() + 4, messageParts.end(), back_inserter(second_part));

    // keeping track of the special movement of other player's pawn movement -- for en passant rule implementation
    // in game's engine
    if (board.specialPawnExists(std::stoi(first_part[2]), std::stoi(first_part[3]))) {
        board.removeSpecialPawn(std::stoi(first_part[2]), std::stoi(first_part[3]));
    }

    if (first_part[1] == "Pawn" and std::stoi(first_part[2]) == 2 and std::stoi(second_part[2]) == 4) {
        board.setSpecialPawn(std::stoi(second_part[2]), std::stoi(second_part[3]));
    }

    // remove part
    addRemoveBoardPieces(first_part[0], first_part[1], std::stoi(first_part[2]), std::stoi(first_part[3]), player, removing_player);
    // add part
    addRemoveBoardPieces(second_part[0], second_part[1], std::stoi(second_part[2]), std::stoi(second_part[3]), player, removing_player);

    // handling special case of en passant
    if (messageParts.size() > 8) {
        board.removePawn(removing_player, std::stoi(messageParts[9]), std::stoi(messageParts[10]));
    }
}
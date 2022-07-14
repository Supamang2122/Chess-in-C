#ifndef CHESS_FUNCTIONS_H
#define CHESS_FUNCTIONS_H

/* Used libraries: */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* Main error codes: */

#define FAILED_TO_ALLOCATE_MEMORY { printf("CRITICAL ERROR: Failed to allocate memory"); return 1; }
#define INCORRECT_INPUT { destroyGame(chess); printf("CRITICAL ERROR: Incorrect input"); return 2; }

/* Core function's error codes: */

#define FUNCTION_SUCCESS return 0;
#define FUNCTION_INPUT_ERROR return -1;
#define FUNCTION_DATA_ERROR return -2;
#define MEMORY_CRITICAL_ERROR { destroyGame(*data); return -3; }
#define ILLEGAL_MOVE return -4;

/* User communication error codes: */

#define HOW_IT_EVEN_HAPPENED -2137
#define GAME_END -1
#define USER_SUCCESSFUL_MOVE 0
#define USER_INCORRECT_INPUT 1
#define USER_INCORRECT_INPUT_DATA 2
#define PIECE_DOES_NOT_EXIST 3
#define PIECE_DOES_NOT_BELONG_TO_USER 4
#define MOVE_IS_ILLEGAL 5
#define KING_IS_IN_CHECK 6
#define STALEMATE 7
#define CHECKMATE 8

/* Declaration of essential variables: */

enum pieceColor {
    WHITE,
    BLACK
};

enum pieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

struct coordinates {
    char x;             // Horizontal coordinates: a - h
    unsigned char y;    // Vertical coordinates: 1 - 8
};

union bonusInfo {
    unsigned char canCastle;    // = 1 -> KING can castle; = 0 -> Castling is not possible;
    unsigned char firstMove;    // = 2 -> PAWN hasn't move yet; = 1 -> PAWN just moved; = 0 -> PAWN moved more than once;
};

struct piece {
    struct coordinates position;    // Current position on the board
    union bonusInfo additional;     // Additional info for pieces (PAWN, ROOK and KING only)
    enum pieceColor color;          // Color of the piece (WHITE / BLACK)
    enum pieceType type;            // Type of the piece
};

struct game {
    struct piece*** board;              // 2D (8x8) board of pointers to pieces (pointer == NULL if there is no piece)
    struct piece* currentPiece;         // Pointer to the piece that player takes action with
    unsigned int currentRoundNumber;    // Round counter (1 round = 2 moves)
    unsigned int materialAdvantage;     // Measures player's advantage in pieces
};

/* General functions: */

int initiateGame(struct game** data);   // Allocates memory for whole game and sets up the pieces on board
void displayGame(struct game* data);    // Displays current state of the game
void destroyGame(struct game* data);    // Frees allocated memory

/* Move functions: */

int move(struct game* data, struct coordinates newPosition);    // Core function that validates the move and commits it if it's possible

int (*validateByType(enum pieceType type))(struct game*, struct coordinates);   // Returns pointer to a proper piece validation function according to the given type

int validatePawn(struct game* data, struct coordinates newPosition);    // Validates move of the PAWN assuming a clear board
int validateKnight(struct game* data, struct coordinates newPosition);  // Validates move of the KNIGHT assuming a clear board
int validateBishop(struct game* data, struct coordinates newPosition);  // Validates move of the BISHOP assuming a clear board
int validateRook(struct game* data, struct coordinates newPosition);    // Validates move of the ROOK assuming a clear board
int validateQueen(struct game* data, struct coordinates newPosition);   // Validates move of the QUEEN assuming a clear board
int validateKing(struct game* data, struct coordinates newPosition);    // Validates move of the KING assuming a clear board

int validateInterruption(struct game* data, struct coordinates newPosition);        // Validates move of the piece by checking if there is no other piece on its path
int validateKingsCheckHazard(struct game* data, struct coordinates newPosition);    // Validates move of the piece by testing if it wouldn't cause a check for piece's own KING

/* Additional functions: */

struct piece* searchForPiece(struct game* data, struct coordinates position);   // Returns pointer to a piece that is on given coordinates (returns NULL if there is no piece)

int isEnemy(struct game* data, struct coordinates position);    // Checks if a piece at given coordinates is different color (1 = enemy, 0 = ally)

int isPositionAttacked(struct game* data, struct coordinates position, enum pieceColor color);  // Checks if a position at given coordinates is attacked by given color

int lookForCheck(struct game* data, enum pieceColor color);    // Infroms if the KING is checked

int areThereAnyLegalMovesLeft(struct game* data, enum pieceColor color);    // Checks if there are any legal moves left for the player to execute

int userCommunication(struct game* data, enum pieceColor color);    // Takes user's input, analyze it, execute necessary functions and returns proper error code

#endif //CHESS_FUNCTIONS_H

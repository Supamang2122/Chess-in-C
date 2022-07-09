#include "functions.h"

/* -------------------------------------------------------------------- */
/*                               READ ME!                               */
/* Some important dev info that I will write later if I won't forget it */
/*       I wish you good luck in browsing this spaghetti code! :)       */
/* -------------------------------------------------------------------- */

int main() {
    struct game* chess;

    if(initiateGame(&chess))
        FAILED_TO_ALLOCATE_MEMORY

    printf("CHESS IN C (C stands for cancer edition) -> version 0.1.1a\n\n");

    printf("IMPORTANT INFO:\n\n");

    printf("In order to move your pieces you have to type for example: \"a1 h8\", where:\n");
    printf("- \"a1\" are coordinates of a piece you want to move\n");
    printf("- \"h1\" are destination coordinates\n");
    printf("In order to castle you have to \"move\" your king on a position of one of the rooks\n");
    printf("Pawn is being automatically promoted to Queen without user interference\n");
    printf("You can exit the game whenever you want by typing: \"x0 x0\" instead of move\n");
    printf("And finally I hope you will enjoy this crazy experience! ^.^\n\n");

    printf("Press enter to continue...");
    scanf("%*[^\n]");
    scanf("%*c");

    enum pieceColor color = WHITE;
    int errCode;

    displayGame(chess);

    do {
        printf("%s's move: ", (color == WHITE) ? "White" : "Black");

        errCode = userCommunication(chess, color);

        if(errCode == USER_SUCCESSFUL_MOVE || errCode == KING_IS_IN_CHECK || errCode == CHECKMATE || errCode == STALEMATE)
            displayGame(chess);
        else if(errCode == USER_INCORRECT_INPUT)
            INCORRECT_INPUT
        else if(errCode == USER_INCORRECT_INPUT_DATA)
            printf("\nIncorrect position data!\n\n");
        else if(errCode == PIECE_DOES_NOT_EXIST)
            printf("\nThere is no piece at given coordinates!\n\n");
        else if(errCode == PIECE_DOES_NOT_BELONG_TO_USER)
            printf("\nPiece at given coordinates doesn't belong to %s!\n\n", (color == WHITE) ? "white" : "black");
        else if(errCode == MOVE_IS_ILLEGAL)
            printf("\nIllegal move!\n\n");

        if(errCode == KING_IS_IN_CHECK)
            printf("%s'S KING IN CHECK!\n\n", (color == WHITE) ? "BLACK" : "WHITE");

        if(errCode == USER_SUCCESSFUL_MOVE || errCode == KING_IS_IN_CHECK)
            color = (color == WHITE) ? BLACK : WHITE;

        if(color == BLACK)
            chess -> currentRoundNumber++;
    } while(errCode != GAME_END && errCode != CHECKMATE && errCode != STALEMATE);

    if(errCode == CHECKMATE)
        printf("CHECKMATE!\n");
    else if(errCode == STALEMATE)
        printf("STALEMATE!\n");

    printf("\nTHANKS FOR PLAYING! <3");

    destroyGame(chess);

    return 0;
}

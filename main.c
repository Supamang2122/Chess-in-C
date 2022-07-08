#include "functions.h"

/* -------------------------------------------------------------------- */
/*                               READ ME!                               */
/* Some important dev info that I will write later if I won't forget it */
/*       I wish you good luck in browsing this spaghetti code! :)       */
/* -------------------------------------------------------------------- */

int main() {
    struct game* chess;

    if(initiateGame(&chess))
        failedToAllocateMemory

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

        if(errCode == userSuccessfulMove || errCode == kingInCheck || errCode == checkmate || errCode == stalemate)
            displayGame(chess);
        else if(errCode == userIncorrectInput)
            incorrectInput
        else if(errCode == userIncorrectInputData)
            printf("\nIncorrect position data!\n\n");
        else if(errCode == pieceDoesntExist)
            printf("\nThere is no piece at given coordinates!\n\n");
        else if(errCode == pieceDoesntBelongToUser)
            printf("\nPiece at given coordinates doesn't belong to %s!\n\n", (color == WHITE) ? "white" : "black");
        else if(errCode == illegalMove)
            printf("\nIllegal move!\n\n");

        if(errCode == kingInCheck)
            printf("%s'S KING IN CHECK!\n\n", (color == WHITE) ? "BLACK" : "WHITE");

        if(errCode == userSuccessfulMove || errCode == kingInCheck)
            color = (color == WHITE) ? BLACK : WHITE;

        if(color == BLACK)
            chess -> currentRoundNumber++;

        if(errCode == checkmate)
            printf("CHECKMATE!\n");

        if(errCode == stalemate)
            printf("STALEMATE!\n");
    } while(errCode != gameEnd && errCode != checkmate && errCode != stalemate);

    printf("\nTHANKS FOR PLAYING! <3");

    free(chess);

    return 0;
}

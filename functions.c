#include "functions.h"

int initiateGame(struct game** data)
{
    if(!data)
        FunctionInputError

    *data = (struct game*) malloc(sizeof(struct game));
    if(!(*data))
        MemoryCriticalError

    struct piece*** board = (struct piece***) calloc(9, sizeof(void*));
    (*data) -> board = board;
    if(!board)
        MemoryCriticalError

    for(int i = 0; i < 8; i++)
    {
        *(board + i) = (struct piece**) calloc(8, sizeof(void*));
        if(!(*(board + i)))
            MemoryCriticalError

        if(i < 2 || i > 5)
            for(int j = 0; j < 8; j++)
            {
                *(*(board + i) + j) = (struct piece*) malloc(sizeof(struct piece));
                if(!(*(*(board + i) + j)))
                    MemoryCriticalError
            }
    }

    struct piece* piece;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            piece = *(*(board + i) + j);
            if(!piece)
                continue;

            piece -> position.x = j + 97;
            piece -> position.y = 8 - i;

            if(i < 2)
                piece -> color = BLACK;
            else if(i > 5)
                piece -> color = WHITE;

            if(i == 1 || i == 6)
            {
                piece -> type = PAWN;
                piece -> additional.firstMove = 2;
            }
            else if(i == 0 || i == 7)
            {
                if(j == 0 || j == 7)
                {
                    piece -> type = ROOK;
                    piece -> additional.canCastle = 1;
                }
                else if(j == 1 || j == 6)
                    piece -> type = KNIGHT;
                else if(j == 2 || j == 5)
                    piece -> type = BISHOP;
                else if(j == 3)
                    piece -> type = QUEEN;
                else if(j == 4)
                {
                    piece -> type = KING;
                    piece -> additional.canCastle = 1;
                }
            }
        }
    }

    (*data) -> currentPiece = NULL;
    (*data) -> currentRoundNumber = 1;
    (*data) -> materialAdvantage = 0;

    FunctionSuccess
}

void displayGame(struct game* data)
{
    if(data)
    {
        printf("\nRound no: %u\n\n", data -> currentRoundNumber);
        printf("Black's material advantage: %d\n\n", -1 * data -> materialAdvantage);
        struct piece* piece;

        SetConsoleOutputCP(CP_UTF8);

        if(data -> board)
        {
            if(GetConsoleOutputCP() == CP_UTF8)
            {
                printf("  \u2554\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2557\n");
                for(int i = 0; i < 8; i++)
                {
                    printf("%d \u2551\u2001", 8 - i);
                    for(int j = 0; j < 8; j++)
                    {
                        piece = *(*((data -> board) + i) + j);
                        if(!piece)
                        {
                            printf("\u2009   ");
                            continue;
                        }

                        if(piece -> color == WHITE)
                        {
                            switch (piece -> type)
                            {
                                case PAWN: printf("\u2659\u2001"); break;
                                case ROOK: printf("\u2656\u2001"); break;
                                case KNIGHT: printf("\u2658\u2001"); break;
                                case BISHOP: printf("\u2657\u2001"); break;
                                case QUEEN: printf("\u2655\u2001"); break;
                                case KING: printf("\u2654\u2001"); break;
                                default: printf("\u2009   "); break;
                            }
                        }
                        else
                        {
                            switch (piece -> type)
                            {
                                case PAWN: printf("\u265f\u2001"); break;
                                case ROOK: printf("\u265c\u2001"); break;
                                case KNIGHT: printf("\u265e\u2001"); break;
                                case BISHOP: printf("\u265d\u2001"); break;
                                case QUEEN: printf("\u265b\u2001"); break;
                                case KING: printf("\u265a\u2001"); break;
                                default: printf("\u2009   "); break;
                            }
                        }
                    }
                    printf("\u2551\n");
                }
                printf("  \u255a\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u2550\u2001\u255d\n");
                printf("     a\u2009  b\u2009  c\u2009  d\u2009  e\u2009  f\u2009  g\u2009  h\n\n");
            }
            else
            {
                printf("  /--------------------------\\\n");
                for(int i = 0; i < 8; i++)
                {
                    printf("%d |  ", 8 - i);
                    for(int j = 0; j < 8; j++)
                    {
                        piece = *(*((data -> board) + i) + j);
                        if(!piece)
                        {
                            printf("   ");
                            continue;
                        }


                        if(piece -> color == WHITE)
                        {
                            switch (piece -> type)
                            {
                                case PAWN: printf("P  "); break;
                                case ROOK: printf("R  "); break;
                                case KNIGHT: printf("S  "); break;
                                case BISHOP: printf("B  "); break;
                                case QUEEN: printf("Q  "); break;
                                case KING: printf("K  "); break;
                                default: printf("   "); break;
                            }
                        }
                        else
                        {
                            switch (piece -> type)
                            {
                                case PAWN: printf("p  "); break;
                                case ROOK: printf("r  "); break;
                                case KNIGHT: printf("s  "); break;
                                case BISHOP: printf("b  "); break;
                                case QUEEN: printf("q  "); break;
                                case KING: printf("k  "); break;
                                default: printf("   "); break;
                            }
                        }

                    }
                    printf("|\n");
                }
                printf("  \\--------------------------/\n");
                printf("     a  b  c  d  e  f  g  h\n\n");
            }
        }

        printf("White's material advantage: %d\n\n", data -> materialAdvantage);
    }
}

void destroyGame(struct game* data)
{
    if(data)
    {
        if(data -> board)
        {
            for(int i = 0; *(data -> board + i); i++)
            {
                for(int j = 0; j < 8; j++)
                    if(*(*(data -> board + i) + j))
                        free(*(*(data -> board + i) + j));
                free(*(data -> board + i));
            }
            free(data -> board);
        }
        free(data);
    }
}

int move(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    enum pieceType type = data -> currentPiece -> type;
    struct piece* piece = data -> currentPiece;

    if(validateByType(type)(data, newPosition))
        IllegalMove

    if(validateInterruption(data, newPosition))
        IllegalMove

    if(validateKingsCheckHazard(data, newPosition))
        IllegalMove

    if(piece -> type == KING)
    {
        struct piece* castle = searchForPiece(data, newPosition);

        if(castle)
            if(castle -> color == piece -> color && castle -> type == ROOK && piece -> additional.canCastle && castle -> additional.canCastle)
            {
                struct coordinates newKingPosition = piece -> position;
                struct coordinates newRookPosition = castle -> position;

                if(newRookPosition.x > newKingPosition.x)
                {
                    newKingPosition.x += 2;
                    newRookPosition.x = newKingPosition.x - 1;
                }
                else if(newRookPosition.x < newKingPosition.x)
                {
                    newKingPosition.x -= 2;
                    newRookPosition.x = newKingPosition.x + 1;
                }

                int x = castle -> position.x - 97;
                int y = 8 - castle -> position.y;
                *(*(data -> board + y) + x) = NULL;
                castle -> position = newRookPosition;
                x = newRookPosition.x - 97;
                y = 8 - newRookPosition.y;
                *(*(data -> board + y) + x) = castle;
                x = piece -> position.x - 97;
                y = 8 - piece -> position.y;
                *(*(data -> board + y) + x) = NULL;
                piece -> position = newKingPosition;
                x = newKingPosition.x - 97;
                y = 8 - newKingPosition.y;
                *(*(data -> board + y) + x) = piece;

                piece -> additional.canCastle = 0;

                FunctionSuccess
            }
    }

    struct piece* enemy = searchForPiece(data, newPosition);
    if(enemy)
    {
        if(isEnemy(data, newPosition))
        {
            switch (enemy -> type)
            {
                case PAWN: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 1) : (data -> materialAdvantage += 1); break;
                case ROOK: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 5) : (data -> materialAdvantage += 5); break;
                case KNIGHT: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 3) : (data -> materialAdvantage += 3); break;
                case BISHOP: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 3) : (data -> materialAdvantage += 3); break;
                case QUEEN: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 9) : (data -> materialAdvantage += 9); break;
                default: break;
            }
            int x = enemy -> position.x - 97;
            int y = 8 - enemy -> position.y;
            free(enemy);
            *(*(data -> board + y) + x) = NULL;
        }
    }
    else if(piece -> type == PAWN)
    {
        struct coordinates enPassantCoordinates = newPosition;
        if(piece -> color == WHITE)
            enPassantCoordinates.y--;
        else if(piece -> color == BLACK)
            enPassantCoordinates.y++;

        enemy = searchForPiece(data, enPassantCoordinates);
        if(enemy)
            if(isEnemy(data, enPassantCoordinates) && enemy -> type == PAWN && enemy -> additional.firstMove == 1)
            {
                switch (enemy -> type)
                {
                    case PAWN: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 1) : (data -> materialAdvantage += 1); break;
                    case ROOK: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 5) : (data -> materialAdvantage += 5); break;
                    case KNIGHT: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 3) : (data -> materialAdvantage += 3); break;
                    case BISHOP: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 3) : (data -> materialAdvantage += 3); break;
                    case QUEEN: (enemy -> color == WHITE) ? (data -> materialAdvantage -= 9) : (data -> materialAdvantage += 9); break;
                    default: break;
                }
                int x = enemy -> position.x - 97;
                int y = 8 - enemy -> position.y;
                free(enemy);
                *(*(data -> board + y) + x) = NULL;
            }
    }

    int x = piece -> position.x - 97;
    int y = 8 - piece -> position.y;
    *(*(data -> board + y) + x) = NULL;
    piece -> position = newPosition;
    x = newPosition.x - 97;
    y = 8 - newPosition.y;
    *(*(data -> board + y) + x) = piece;

    if(type == PAWN)
    {
        if(piece -> additional.firstMove > 0)
            piece -> additional.firstMove--;
        if((piece -> color == WHITE && newPosition.y == 8) || (piece -> color == BLACK && newPosition.y == 1))
            piece -> type = QUEEN;
    }
    else if(type == ROOK || type == KING)
        piece -> additional.canCastle = 0;

    FunctionSuccess
}

int (*validateByType(enum pieceType type))(struct game*, struct coordinates)
{
    switch (type)
    {
        case PAWN: return validatePawn;
        case KNIGHT: return validateKnight;
        case BISHOP: return validateBishop;
        case ROOK: return validateRook;
        case QUEEN: return validateQueen;
        case KING: return validateKing;
        default: return NULL;
    }
}

int validatePawn(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    struct piece* piece = data -> currentPiece;

    if(piece -> color == WHITE)
    {
        if(piece -> position.x == newPosition.x && !searchForPiece(data, newPosition))
        {
            if(piece -> position.y + 1 == newPosition.y)
                FunctionSuccess
            else if(piece -> position.y + 2 == newPosition.y && piece -> additional.firstMove == 2)
                FunctionSuccess
        }
        else if((piece -> position.x - 1 == newPosition.x || piece -> position.x + 1 == newPosition.x) && piece -> position.y + 1 == newPosition.y)
        {
            if(searchForPiece(data, newPosition))
                if(isEnemy(data, newPosition))
                    FunctionSuccess
            struct coordinates enPassantCoordinates = {.x = newPosition.x, .y = newPosition.y - 1};
            struct piece* enemy = searchForPiece(data, enPassantCoordinates);
            if(enemy)
                if(isEnemy(data, enPassantCoordinates) && enemy -> type == PAWN && enemy -> additional.firstMove == 1)
                    FunctionSuccess
        }
    }
    else if(piece -> color == BLACK)
    {
        if(piece -> position.x == newPosition.x && !searchForPiece(data, newPosition))
        {
            if(piece -> position.y - 1 == newPosition.y)
                FunctionSuccess
            else if(piece -> position.y - 2 == newPosition.y && piece -> additional.firstMove == 2)
                FunctionSuccess
        }
        else if((piece -> position.x - 1 == newPosition.x || piece -> position.x + 1 == newPosition.x) && piece -> position.y - 1 == newPosition.y)
        {
            if(searchForPiece(data, newPosition))
                if(isEnemy(data, newPosition))
                    FunctionSuccess
            struct coordinates enPassantCoordinates = {.x = newPosition.x, .y = newPosition.y + 1};
            struct piece* enemy = searchForPiece(data, enPassantCoordinates);
            if(enemy)
                if(isEnemy(data, enPassantCoordinates) && enemy -> type == PAWN && enemy -> additional.firstMove == 1)
                    FunctionSuccess
        }
    }

    IllegalMove
}

int validateKnight(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    struct piece* piece = data -> currentPiece;

    if(piece -> position.x + 1 == newPosition.x || piece -> position.x - 1 == newPosition.x)
        if(piece -> position.y + 2 == newPosition.y || piece -> position.y - 2 == newPosition.y)
            FunctionSuccess

    if(piece -> position.y + 1 == newPosition.y || piece -> position.y - 1 == newPosition.y)
        if(piece -> position.x + 2 == newPosition.x || piece -> position.x - 2 == newPosition.x)
            FunctionSuccess

    IllegalMove
}

int validateBishop(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    struct piece* piece = data -> currentPiece;

    if(abs(newPosition.x - piece -> position.x) == abs(newPosition.y - piece -> position.y))
        FunctionSuccess

    IllegalMove
}

int validateRook(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    struct piece* piece = data -> currentPiece;

    if(piece -> position.x == newPosition.x || piece -> position.y == newPosition.y)
        FunctionSuccess

    IllegalMove
}

int validateQueen(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    struct piece* piece = data -> currentPiece;

    if(abs(newPosition.x - piece -> position.x) == abs(newPosition.y - piece -> position.y))
        FunctionSuccess

    if(piece -> position.x == newPosition.x || piece -> position.y == newPosition.y)
        FunctionSuccess

    IllegalMove
}

int validateKing(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    struct piece* piece = data -> currentPiece;

    if(piece -> position.x + 1 == newPosition.x || piece -> position.x - 1 == newPosition.x)
        FunctionSuccess

    if(piece -> position.y + 1 == newPosition.y || piece -> position.y - 1 == newPosition.y)
        FunctionSuccess

    piece = searchForPiece(data, newPosition);

    if(piece)
        if(piece -> color == data -> currentPiece -> color && piece -> type == ROOK && data -> currentPiece -> additional.canCastle && piece -> additional.canCastle)
        {
            struct coordinates currentPosition = data -> currentPiece -> position;

            if(isPositionAttacked(data, currentPosition, (piece -> color == WHITE) ? BLACK : WHITE))
            {
                if(piece -> position.x > data -> currentPiece -> position.x)
                {
                    currentPosition.x++;
                    if(isPositionAttacked(data, currentPosition, (piece -> color == WHITE) ? BLACK : WHITE))
                    {
                        currentPosition.x++;
                        if(isPositionAttacked(data, currentPosition, (piece -> color == WHITE) ? BLACK : WHITE))
                            FunctionSuccess
                    }
                }
                else if(piece -> position.x < data -> currentPiece -> position.x)
                {
                    currentPosition.x--;
                    if(isPositionAttacked(data, currentPosition, (piece -> color == WHITE) ? BLACK : WHITE))
                    {
                        currentPosition.x--;
                        if(isPositionAttacked(data, currentPosition, (piece -> color == WHITE) ? BLACK : WHITE))
                            FunctionSuccess
                    }
                }
            }
        }

    IllegalMove
}

int validateInterruption(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    if(searchForPiece(data, newPosition))
        if(!isEnemy(data, newPosition))
            if(!(data -> currentPiece -> type == KING && searchForPiece(data, newPosition) -> type == ROOK && data -> currentPiece -> additional.canCastle && searchForPiece(data, newPosition) -> additional.canCastle))
                IllegalMove

    if(data -> currentPiece -> type == KNIGHT)
        FunctionSuccess

    struct coordinates orignalPosition = data -> currentPiece -> position;
    struct coordinates currentPosition = orignalPosition;

    do
    {
        if(newPosition.y > orignalPosition.y)
            currentPosition.y++;
        else if(newPosition.y < orignalPosition.y)
            currentPosition.y--;

        if(newPosition.x > orignalPosition.x)
            currentPosition.x++;
        else if(newPosition.x < orignalPosition.x)
            currentPosition.x--;

        if(!((memcmp(&(currentPosition), &(newPosition), sizeof(struct coordinates)))))
            FunctionSuccess

    } while(!searchForPiece(data, currentPosition));

    IllegalMove
}

int validateKingsCheckHazard(struct game* data, struct coordinates newPosition)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(newPosition.x < 'a' || newPosition.x > 'h')
        FunctionDataError

    if(newPosition.y < 1 || newPosition.y > 8)
        FunctionDataError

    if(searchForPiece(data, newPosition))
        if(searchForPiece(data, newPosition) -> type == KING)
            IllegalMove

    struct piece* piece = data -> currentPiece;
    struct coordinates currentPosition = piece -> position;
    struct piece* enemy = searchForPiece(data, newPosition);

    int x = newPosition.x - 97;
    int y = 8 - newPosition.y;
    *(*(data -> board + y) + x) = piece;
    piece -> position = newPosition;
    x = currentPosition.x - 97;
    y = 8 - currentPosition.y;
    *(*(data -> board + y) + x) = NULL;

    if(lookForCheck(data, piece -> color))
    {
        piece -> position = currentPosition;
        *(*(data -> board + y) + x) = piece;
        x = newPosition.x - 97;
        y = 8 - newPosition.y;
        *(*(data -> board + y) + x) = enemy;

        IllegalMove
    }

    piece -> position = currentPosition;
    *(*(data -> board + y) + x) = piece;
    x = newPosition.x - 97;
    y = 8 - newPosition.y;
    *(*(data -> board + y) + x) = enemy;

    FunctionSuccess
}

struct piece* searchForPiece(struct game* data, struct coordinates position)
{
    if(data == NULL)
        return NULL;

    if(data -> board == NULL)
        return NULL;

    if(position.x < 'a' || position.x > 'h')
        return NULL;

    if(position.y < 1 || position.y > 8)
        return NULL;

    struct piece* piece;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            piece = *(*(data -> board + i) + j);
            if(!piece)
                continue;

            if(!(memcmp(&(piece -> position), &(position), sizeof(struct coordinates))))
                return piece;
        }
    }

    return NULL;
}

int isEnemy(struct game* data, struct coordinates position)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(position.x < 'a' || position.x > 'h')
        FunctionDataError

    if(position.y < 1 || position.y > 8)
        FunctionDataError

    if(!searchForPiece(data, position))
        FunctionDataError

    if(data -> currentPiece -> color != searchForPiece(data, position) -> color)
        return 1;

    return 0;
}

int isPositionAttacked(struct game* data, struct coordinates position, enum pieceColor color)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    if(position.x < 'a' || position.x > 'h')
        FunctionDataError

    if(position.y < 1 || position.y > 8)
        FunctionDataError

    struct piece *piece;
    struct coordinates piecePosition;
    struct piece *currentPiece = data -> currentPiece;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            piecePosition.x = j + 97;
            piecePosition.y = 8 - i;

            piece = searchForPiece(data, piecePosition);
            if(piece)
                if(piece -> color == color)
                {
                    data -> currentPiece = piece;

                    if(!validateByType(piece -> type)(data, position) && !validateInterruption(data, position))
                    {
                        data -> currentPiece = currentPiece;
                        return 1;
                    }

                    data -> currentPiece = currentPiece;
                }
        }
    }

    return 0;
}

int lookForCheck(struct game* data, enum pieceColor color)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    struct piece *piece;
    struct coordinates piecePosition;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            piecePosition.x = j + 97;
            piecePosition.y = 8 - i;

            piece = searchForPiece(data, piecePosition);
            if(piece)
                if(piece -> color == color && piece -> type == KING)
                    if(isPositionAttacked(data, piecePosition, (color == WHITE) ? BLACK : WHITE))
                        return 1;
        }
    }

    return 0;
}

int areThereAnyLegalMovesLeft(struct game* data, enum pieceColor color)
{
    if(!data)
        FunctionInputError

    if(!(data -> board) || !(data -> currentPiece))
        FunctionInputError

    struct piece *piece;
    struct coordinates piecePosition;
    struct coordinates movePosition;
    struct piece *currentPiece = data -> currentPiece;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            piecePosition.x = j + 97;
            piecePosition.y = 8 - i;

            piece = searchForPiece(data, piecePosition);
            if(piece)
                if(piece -> color == color)
                {
                    data -> currentPiece = piece;

                    for(int k = 0; k < 8; k++)
                    {
                        for(int l = 0; l < 8; l++)
                        {
                            movePosition.x = l + 97;
                            movePosition.y = 8 - k;

                            if(!validateByType(piece -> type)(data, movePosition) && !validateInterruption(data, movePosition) && !validateKingsCheckHazard(data, movePosition))
                            {
                                data -> currentPiece = currentPiece;
                                return 1;
                            }
                        }
                    }

                    data -> currentPiece = currentPiece;
                }
        }
    }

    return 0;
}

int userCommunication(struct game* data, enum pieceColor color)
{
    if(!data)
        return howItEvenHappened;

    if(!(data -> board))
        return howItEvenHappened;

    struct coordinates originalPosition, newPosition;

    if(scanf(" %c%hhu %c%hhu", &originalPosition.x, &originalPosition.y, &newPosition.x, &newPosition.y) != 4)
        return userIncorrectInput;

    if(originalPosition.x == 'x' && originalPosition.y == 0 && newPosition.x == 'x' && newPosition.y == 0)
        return gameEnd;

    if(originalPosition.x < 'a' || originalPosition.x > 'h' || newPosition.x < 'a' || newPosition.x > 'h')
        return userIncorrectInputData;

    if(originalPosition.y < 1 || originalPosition.y > 8 || newPosition.y < 1 || newPosition.y > 8)
        return userIncorrectInputData;

    data -> currentPiece = searchForPiece(data, originalPosition);
    if(!(data -> currentPiece))
        return pieceDoesntExist;

    if(data -> currentPiece -> color != color)
        return pieceDoesntBelongToUser;

    if(move(data, newPosition))
        return illegalMove;

    if(!areThereAnyLegalMovesLeft(data, (data -> currentPiece -> color == WHITE) ? BLACK : WHITE))
    {
        if(lookForCheck(data, (data -> currentPiece -> color == WHITE) ? BLACK : WHITE))
            return checkmate;
        return stalemate;
    }

    if(lookForCheck(data, (data -> currentPiece -> color == WHITE) ? BLACK : WHITE))
        return kingInCheck;

    return userSuccessfulMove;
}

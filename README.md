# Chess in C
> ~~Nearly~~ fully functional chess created in C ♟

## In general
Using my lack of knowledge and severe brain damage, I created 2 player chess that is playable via terminal!

Every round, each player is asked to write 2 coordinates as an input in the form `"src dest"`. 

The `src` field represents the original coordinate of the piece and the `dest` field represents the destination coordinate for that same piece. 
Example input: `"a1 h8"`.


User input is analyzed and program determines if the move is valid. After each move a new state of the chessboard is displayed. In case of an illegal move/input, the program will ask again for coordinates until a legal move is entered.

## How it works?

Chessboard is 2D array of pointers to structures that holds all the info about each piece. Whole game logic is based on that info which is being constantly analyzed and updated. 

User input is being transformed to data that is pushed into core functions, which decide if the move is legal or not. If it is, necessary pieces are being updated. Then a function which communicates with the user gives right error code that will be analyzed and translated to user if it will be needed.

## Limitations
There are little things that were not implemented:
 - User cannot choose a piece that pawn is promoted to -> Pawn is automatically promoted to Queen
 - The only way to draw is by stalemate. It is impossible to:
	 - draw by threefold repetition
	 - draw by 50 move rule
	 - draw by insufficient mating material
- Time limit does not exist

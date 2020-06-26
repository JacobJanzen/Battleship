#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 10 //size of the square board
/*size of each ship*/
#define C_SIZE 5
#define B_SIZE 4
#define D_SIZE 3
#define S_SIZE 3
#define P_SIZE 2

/*the boards*/
char board1[SIZE][SIZE];
char board2[SIZE][SIZE];

bool gameOver = false; //checks when the game ends

/*declare functions*/
void printBoard(char[SIZE][SIZE]);
void printOpponentBoard(char[SIZE][SIZE]);
void setBoard(char[SIZE][SIZE]);
void chooseLocation(char[SIZE][SIZE], int, char);
void addShip(int, int, char, int, char[SIZE][SIZE], char);
void playGame(char[SIZE][SIZE], char[SIZE][SIZE]);

int main(void){
	system("@cls||clear");
	/*fill board with '.'*/
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++){
			board1[i][j] = '.';
			board2[i][j] = '.';
		}

	/*set the boards*/
	setBoard(board1);
	setBoard(board2);
	/*the game starts*/
	do{
		playGame(board1,board2);
		printf("Press ENTER to end turn :\n");
		getchar();
		getchar();
		system("@cls||clear");
		if(!gameOver){
			playGame(board2,board1);
			printf("Press ENTER to end turn :\n");
			getchar();
			getchar();
			system("@cls||clear");
		}
	}while(!gameOver);

	return 0;
}

void printBoard(char board[SIZE][SIZE]){
	printf("   ");

	/*print the letter coordinates*/
	for(int i = 0; i < SIZE; i++)
		printf("%c ", 'a'+i);
	printf("\n");

	/*print the grid*/
	for(int i = 0; i < SIZE; i++){
		if(i+1 < 10)
			printf(" ");
		printf("%d ", i+1); //print the number coordinates
		for(int j = 0; j < SIZE; j++)
			printf("%c ",board[j][i]);
		printf("\n");
	}
}

void printOpponentBoard(char board[SIZE][SIZE]){
	printf("   ");

	/*print the letter coordinates*/
	for(int i = 0; i < SIZE; i++)
		printf("%c ", 'a'+i);
	printf("\n");

	/*print the grid*/
	for(int i = 0; i < SIZE; i++){
		if(i+1 < 10)
			printf(" ");
		printf("%d ", i+1); //print the number coordinates
		for(int j = 0; j < SIZE; j++){
			if(board[j][i]=='X'||board[j][i]=='O')
				printf("%c ", board[j][i]);
			else
				printf(". ");
		}
		printf("\n");
	}
}

void setBoard(char board[SIZE][SIZE]){
	chooseLocation(board, C_SIZE, 'C'); //carrier
	system("@cls||clear");
	chooseLocation(board, B_SIZE, 'B'); //battleship
	system("@cls||clear");
	chooseLocation(board, D_SIZE, 'D'); //destroyer
	system("@cls||clear");
	chooseLocation(board, S_SIZE, 'S'); //submarine
	system("@cls||clear");
	chooseLocation(board, P_SIZE, 'P'); //patrol boat
	system("@cls||clear");
}

void chooseLocation(char board[SIZE][SIZE], int size, char shipNum){
	int vPos = 10, hPos = 10; //the coordinates
	int width, height; //the size of the boat
	char hPosChar, direction; //input variable for x-coord and direction
	
	do{
		printBoard(board); //draw the board to the screen

		/*choose the location*/
		printf("Enter the top left coordinate in format and direction (h = horizontal, v = vertical) in format \"7bh\". Size is %d: ", size);
		scanf("%d%c%c", &vPos, &hPosChar, &direction);

		/*make the values useable*/
		--vPos;
		hPos = hPosChar - 'a';

		/*set the width and height*/
		switch(direction){
			case 'h':
				width = size;
				height = 1; break;
			case 'v':
				height = size;
				width = 1; break;
			default:
				printf("Enter a valid direction\n");
		}

		//checks if there is a ship already in the way
		for(int i = 0; i < width; i++){
			for(int j = 0; j < height; j++){
				if(board[hPos+i][vPos+j] != '.'){
					vPos = SIZE + 1;
					break;
				}
			}
		}
		if(vPos+height > SIZE || hPos+width > SIZE || hPos < 0 || vPos < 0)
			printf("Enter a valid location\n");
	}while(vPos+height > SIZE || hPos+width > SIZE || (direction != 'h' && direction != 'v') || hPos < 0 || vPos < 0);

	addShip(vPos, hPos, direction, size, board, shipNum); //places the ship on the board
}

void addShip(int vPos, int hPos, char direction, int size, char board[SIZE][SIZE], char shipNum){
	if(direction=='h'){//horizontal
		for(int i = 0; i < size; i++){
			board[hPos+i][vPos] = shipNum;
		}
	}else{//vertical
		for(int i = 0; i < size; i++){
			board[hPos][vPos+i] = shipNum;
		}
	}
}

void playGame(char pBoard[SIZE][SIZE], char oBoard[SIZE][SIZE]){
	int hPos, vPos;//coordinates
	char hPosChar, temp;//input variable for x-coord, the type of ship hit
	bool sink = true, allSank = true;//check whether ship was sank and whether all ships have sank
	printOpponentBoard(oBoard);
	printf("\n");
	printBoard(pBoard);

	/* get the location to aim */
	do{
		printf("Enter the location you want to hit (e.g. 7b): ");
		scanf("%d%c", &vPos, &hPosChar);
		vPos--;
		hPos = hPosChar - 'a';
		if(hPos >= SIZE || vPos >= SIZE || oBoard[hPos][vPos] == 'X' || oBoard[hPos][vPos] == 'O' || hPos < 0 || vPos < 0)
			printf("Enter a valid Location\n");
	}while(hPos >= SIZE || vPos >= SIZE || oBoard[hPos][vPos] == 'X' || oBoard[hPos][vPos] == 'O' || hPos < 0 || vPos < 0);

	if(oBoard[hPos][vPos] == '.'){ //MISS
		oBoard[hPos][vPos] = 'O';
		printf("MISS!\n");
		allSank = false;
	}else{ //HIT
		temp = oBoard[hPos][vPos];
		oBoard[hPos][vPos] = 'X';

		/* checks if the ship sank and if all ships have sank */
		for(int i = 0; i < SIZE; i++){
			for(int j = 0; j < SIZE; j++)
				if(oBoard[j][i] == temp){//sink
					sink = false;
					break;
				}else if(oBoard[j][i] != '.' && oBoard[j][i] != 'X' && oBoard[j][i] != 'O')
					allSank = false;
			if(!sink)
				break;
		}
		if(sink)
			printf("SINK!\n");
		else{
			printf("HIT!\n");
			allSank = false;
		}
	}

	if(allSank)//ends the game
		gameOver = true;
}

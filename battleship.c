#include <stdio.h>

#define SIZE 10 //size of the square board

/*size of each ship*/
#define C_SIZE 5
#define B_SIZE 4
#define D_SIZE 3
#define S_SIZE 3
#define P_SIZE 2

char board1[SIZE][SIZE];
char board2[SIZE][SIZE];

/*declare functions*/
void printBoard(char[SIZE][SIZE]);
void setBoard(char[SIZE][SIZE]);
void chooseLocation(char[SIZE][SIZE], int, char);
void addShip(int, int, char, int, char[SIZE][SIZE], char);

int main(void){
	/*fill board with '.'*/
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++){
			board1[i][j] = '.';
			board2[i][j] = '.';
		}

	/*set the boards*/
	setBoard(board1);
	setBoard(board2);
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

void setBoard(char board[SIZE][SIZE]){
	//set carrier location
	chooseLocation(board, C_SIZE, 'C');
	chooseLocation(board, B_SIZE, 'B');
	chooseLocation(board, D_SIZE, 'D');
	chooseLocation(board, S_SIZE, 'S');
	chooseLocation(board, P_SIZE, 'P');
	printBoard(board);
}

void chooseLocation(char board[SIZE][SIZE], int size, char shipNum){
	int vPos = 10, hPos = 10;
	int width, height;
	char hPosChar, direction;
	
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
		for(int i = 0; i < width; i++){
			for(int j = 0; j < height; j++){
				if(board[hPos+i][vPos+j] != '.'){
					vPos = SIZE + 1;
					break;
				}
			}
		}
		if(vPos+height > SIZE || hPos+width > SIZE)
			printf("Enter a valid location\n");
	}while(vPos+height > SIZE || hPos+width > SIZE || (direction != 'h' && direction != 'v'));

	addShip(vPos, hPos, direction, size, board, shipNum);
}

void addShip(int vPos, int hPos, char direction, int size, char board[SIZE][SIZE], char shipNum){
	if(direction=='h'){
		for(int i = 0; i < size; i++){
			board[hPos+i][vPos] = shipNum;
		}
	}else{
		for(int i = 0; i < size; i++){
			board[hPos][vPos+i] = shipNum;
		}
	}
}

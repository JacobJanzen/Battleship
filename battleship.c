#include <stdio.h>

#define SIZE 10

#define NUM_C 1
#define NUM_B 2
#define NUM_D 3
#define NUM_S 4
#define NUM_P 5

#define C_SIZE 5
#define B_SIZE 4
#define D_SIZE 3
#define S_SIZE 3
#define P_SIZE 2

char board1[SIZE][SIZE];
char board2[SIZE][SIZE];

void printBoard(char[SIZE][SIZE]);
void setBoard(char[SIZE][SIZE]);
int * chooseLocation(char[SIZE][SIZE], int[3]);
int main(void){
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++){
			board1[i][j] = '.';
			board2[i][j] = '.';
		}
	setBoard(board1);
	return 0;
}

void printBoard(char board[SIZE][SIZE]){
	printf("   ");
	for(int i = 0; i < SIZE; i++)
		printf("%c ", 'a'+i);
	printf("\n");
	for(int i = 0; i < SIZE; i++){
		if(i+1 < 10)
			printf(" ");
		printf("%d ", i+1);
		for(int j = 0; j < SIZE; j++)
			printf("%c ",board[i][j]);
		printf("\n");
	}
}

void setBoard(char board[SIZE][SIZE]){
	int selections[3];
	//set carrier location
	for(int i = 0; i < NUM_C; i++)
		chooseLocation(board,selections);
}

int * chooseLocation(char board[SIZE][SIZE],int selections[3]){
	int direction;
	int vPos, hPos;
	char hPosChar;
	printf("Horizontal (1) or Vertical (2)?");
	scanf("%d", &direction);

	printf("List coordinates in format \"7b\": ");
	scanf("%d%c", &vPos, &hPosChar);
	vPos--;

	switch(hPosChar){
		case 'a':
			hPos=0; break;
		case 'b':
			hPos=1; break;
		case 'c':
			hPos=2; break;
		case 'd':
			hPos=3; break;
		case 'e':
			hPos=4; break;
		case 'f':
			hPos=5; break;
		case 'g':
			hPos=6; break;
		case 'h':
			hPos=7; break;
		case 'i':
			hPos=8; break;
		case 'j':
			hPos=9; break;
		default:
			hPos=-1; printf("something went wrong"); break;
	}
	selections[0] = direction;
	selections[1] = vPos;
	selections[2] = hPos;
	return selections;
}

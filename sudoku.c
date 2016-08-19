/*
 *  sudoku.c
 *  This program is created to solve a sudoku puzzle
 *
 *
 *  Created by Bella Mangunsong
 *  (z5083765)
 *
 *  started on 28 April 2016
 *  Copyright 2016 Licensed under Creative Commons SA-BY-NC 3.0.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ROW 9
#define COL 9
#define REG 9
#define REG_ROW 3
#define REG_COL 3
#define LINE 25

#define FALSE 0
#define TRUE 1


typedef struct _grid {
	char num;
	int given;
} grid;

void printPuzzle(grid box[ROW][COL+1]);
void printLine(void);
void solveSudoku(grid box[ROW][COL+1]);
int compareCol (char a, int col, grid box[ROW][COL+1]);
int compareRow (char a, int row, grid box[ROW][COL+1]);
int compareReg (char a, int col, int row, grid box[ROW][COL+1]);

int main (int argc, char * argv[]) {

	grid box[ROW][COL+1] = {0};
	//The [COL+1] is to acount new line ('\n')

	int col = 0; // the puzzle is stored as a 9x9 box
	int row = 0; 

	while(row < ROW) {
		
		col = 0;
		while (col < COL+1) {
			box[row][col].num = getchar();
			if(box[row][col].num != '\n'){
				assert(box[row][col].num >= '0' && 
						box[row][col].num <= '9');
			}
			if(box[row][col].num != '0'){
				box[row][col].given = TRUE;
			} else {
				box[row][col].given = FALSE;
			}
			col++;
		}
		row++;
	}
	//put terminating character at the end of the array
	box[ROW-1][COL].num = 0;

	printPuzzle(box);
	solveSudoku(box);


	return EXIT_SUCCESS;
}


void printPuzzle(grid box[ROW][COL+1]){

	int col = 0; 
	int row = 0;
	while(row < ROW) {
		col = 0;
		if(row % REG_ROW == 0) {
			printLine();
		}
		while (col < COL) {
			if (col % REG_ROW == 0) {
				printf("| ");
			}
			if (box[row][col].given == TRUE){
				printf("\x1b[1;33m"); //print in bold
			}

			printf("%c ", box[row][col].num); //actual number inside the box
			printf("\x1b[0m");
			col++;
		}			
		printf("|\n");
		row++;
	}
	printLine();
}

void printLine(void){
	int counter = 0;
	while (counter < LINE) {
		if (counter % 8 == 0){
			printf("+");
		} else {
			printf("-");
		}
	counter++;
	}
	printf("\n");
}


// Solve the puzzle
void solveSudoku(grid box[ROW][COL+1]){
	int row = 0;
	int col = 0;
	char a = '1';
	while (row < ROW && a != ':') {
		col = 0;
		while (col < COL && a != ':') {
			if (box[row][col].num == '0') {
				a = '1';
				while(box[row][col].num == '0'){
					if(compareCol(a, col, box) == TRUE &&
						compareRow(a, row, box) == TRUE &&
						compareReg(a, col, row, box) == TRUE){
						box[row][col].num = a;
					} else {
						a++;
					}
				}
			}
			col++;
		}
		row++; 
		
	}
	if (a == ':') {
		printf("Puzzle can not be solved\n");
	} else {
		printPuzzle(box);
	}

}

int compareCol (char a, int col, grid box[ROW][COL+1]){
	int i = 0;
	int j = 0;

	while (i < ROW){
		if (a == box[i][col].num){
			j++;
		}
		i++;
	}

	if(j > 0){
		i = FALSE;
	} else {
		i = TRUE;
	}
	return i;
}

int compareRow (char a, int row, grid box[ROW][COL+1]){
	int i = 0;
	int j = 0;

	while (i < COL){
		if (a == box[row][i].num){
			j++;
		}
		i++;
	}

	if(j > 0){
		i = FALSE;
	} else {
		i = TRUE;
	}
	return i;
}

int compareReg (char a, int col, int row, grid box[ROW][COL+1]){
	row = row / 3;
	col = col / 3;

	int i = 3*row;
	int j = 3*col;
	int colF = j;
	row = i + 3;
	col = j + 3;

	int k = 0;
	int l = 0;

	while (i < row){
		j = colF;
		while (j < col){
			if (a == box[i][j].num){
				k++;
			}
			j++;
		}
		i++;
	}

	if(k > 0){
		l = FALSE;
	} else {
		l = TRUE;
	}
	return l;
}
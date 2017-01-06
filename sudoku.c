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

typedef grid * Grid;
void printPuzzle(void);
void printLine(void);
int compareCol (char a, int col);
int compareRow (char a, int row);
int compareReg (char a, int col, int row);
int solve(int row, int col);

grid box[ROW][COL+1] = {0};

int main (int argc, char * argv[]) {

    //The [COL+1] is to acount new line ('\n')
    // the puzzle is stored as a 9x9 box
    int col = 0; 
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
    printPuzzle();
    if (solve(0,0)) {
        printPuzzle();
    } else {
        printf("puzzle could not be solved\n");
        printPuzzle();
    }

    return EXIT_SUCCESS;
}


void printPuzzle(void){

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
            if (box[row][col].given == TRUE) {
                //print in bold
                printf("\x1b[1;33m"); 
            }
            //actual number inside the box
            printf("%c ", box[row][col].num); 
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

int compareCol (char a, int col){
    int i = 0;
    int same = 0;
    for (i = 0; i < ROW; i++) {
        if (a == box[i][col].num) {
            same++;
        }
    }
    return (same > 0) ? FALSE : TRUE;
}

int compareRow (char a, int row){
    int i = 0;
    int same = 0;
    for (i = 0; i < COL; i++) {
        if (a == box[row][i].num) {
            same++;
        }
    }
    return (same > 0) ? FALSE : TRUE;
}

int compareReg (char a, int col, int row){
    int rowStart = row/3*3;
    int colStart = col/3*3;
    row = rowStart + 3;
    col = colStart + 3;
    int i, j, same = 0;
    for (i = rowStart; i < row; i++) {
        for (j = colStart; j < col; j++) {
            if (a == box[i][j].num){
                same++;
            }
        }
    }
    return (same > 0) ? FALSE : TRUE;
}

// Solve using DFS (recursion) 
int solve(int row, int col){
    // First check if grid is empty
    int next_row, next_col;
    while (box[row][col].given == TRUE) {
        if (col < 8) {
            next_row = row;
            next_col = col + 1;
        } else {
            next_row = row + 1;
            next_col = 0;
        }
        row = next_row;
        col = next_col;
    }
    if (col < 8) {
        next_row = row;
        next_col = col + 1;
    } else {
        next_row = row + 1;
        next_col = 0;
    }
    // Check if puzzle solved
    if (row > 8) {
        return TRUE;
    }
    char a = '1';
    while (TRUE) {
        if (compareCol(a, col) == TRUE &&
           compareRow(a, row) == TRUE &&
           compareReg(a, col, row) == TRUE) {
            box[row][col].num = a;
            if (solve(next_row, next_col)) {
                return TRUE;
            }
        }    
        a++;
        if (a == ':') {
            box[row][col].num = '0';
            return FALSE;
        }
    }
    return FALSE;
}
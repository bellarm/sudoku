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
void solveSudoku(void);
int compareCol (char a, int col);
int compareRow (char a, int row);
int compareReg (char a, int col, int row);
int new(int row, int col);

grid box[ROW][COL+1] = {0};

int main (int argc, char * argv[]) {

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

    if (new(0,0)) {
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
void solveSudoku(void){
    int row = 0;
    int col = 0;
    char a = '1';
    while (row < ROW && a != ':') {
        col = 0;
        while (col < COL && a != ':') {
            if (box[row][col].num == '0') {
                a = '1';
                while(box[row][col].num == '0'){
                    if(compareCol(a, col) == TRUE &&
                        compareRow(a, row) == TRUE &&
                        compareReg(a, col, row) == TRUE){
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
        printPuzzle();
    }

}

int compareCol (char a, int col){
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

int compareRow (char a, int row){
    int i = 0;
    int j = 0;
    printPuzzle();
    while (i < COL){
        if (a == box[row][i].num){
            j++;
        }
        printf(" %d,%d -> %c\n", row, i, box[row][i].num);
        i++;
    }
    printf("\n");
    if(j > 0){
        i = FALSE;
    } else {
        i = TRUE;
    }
    return i;
}

int compareReg (char a, int col, int row){

    row = row / 3;
    col = col / 3;
    int i = 3*row;
    int j = 3*col;
    int colF = j;
    row = i + 3;
    col = j + 3;

    int k = 0;
    int l = 0;
    //printf("%d-%d, %d-%d\n", i,row, j, col);
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

// NEW ATTEMPT
/*  Find all the possible numbers for a grid
    Then do a DFS
    DFS:
        - if puzzle solved: return 1
        - else do a recursion:
            - check if a number is legal
            - if legal: call the next one
            - if next returns 0:
                - try another number
*/

int new(int row, int col){
    // First check if puzzle solved
    if (row > 8) {
        return 1;
    }
    // Then check if grid is empty
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
    char a = '1';
    int result = 0;
    printf("%d %d\n", row, col);
    while (TRUE) {

        if (row == 3 && col == 8 && a == '5') {
                printf("\t%c\n", a);
                printf("%d\n", compareCol(a, col));
                printf("%d\n", compareRow(a, row));
                printf("%d\n", compareReg(a, col, row));
        }
        if (compareCol(a, col) == TRUE &&
           compareRow(a, row) == TRUE &&
           compareReg(a, col, row) == TRUE) {
            box[row][col].num = a;
            
            result = new(next_row, next_col);
            if (result) {
                return 1;
            }
        }    
        a++;
        if (a == ':' && !result) {
            return 0;
        } else if (a == ':') {
            a = '1';
        }
    }
    return 0;
}
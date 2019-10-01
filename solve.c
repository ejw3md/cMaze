#include <stdio.h>
#include <stdlib.h>

//#include "queue.h"

typedef struct cell
{
    int r;
    int c;
    int visited;
    struct cell * prev;
}Cell;

int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int ** createMaze(char * filename, int * rows, int * cols);
void printMaze(int ** maze, int rows, int cols);
Cell createCell(int r, int c);
Cell findStart(int ** maze, int rows, int cols);
Cell findEnd(int ** maze, int rows, int cols);
Cell BFS(int ** maze, int rows, int cols);

int main(int argc, char ** argv)
{
    int rows, cols;
    int ** maze = createMaze(argv[1], &rows, &cols);
    printMaze(maze, rows, cols);
    return 0;
}

Cell createCell(int r, int c)
{
    Cell new = {r, c, 0, NULL};
    return new;
}

int ** createMaze(char * filename, int * rows, int * cols)
{
    FILE * f = fopen(filename, "r");
    int r, c;
    fscanf(f, "%d %d", &r, &c);
    int ** maze = malloc(sizeof(int *) * r);
    for(int i=0; i<r; i++)
    {
        maze[i] = malloc(sizeof(int) * c);
    }

    for(int i=0; i<r; i++)
    {
        char temp;
        fscanf(f, "%c", &temp);             //this fscanf gets rid of the newlines
        for(int j=0; j<c; j++)
        {
            fscanf(f, "%c", &temp);
            maze[i][j] = temp - '0';
        }

    }
    *rows = r;
    *cols = c;
    return maze;
}

void printMaze(int ** maze, int rows, int cols)
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            printf("%d", maze[i][j]);
        }
        printf("\n");
    }
}

Cell findStart(int ** maze, int rows, int cols)
{
    for(int i=0; i<cols; i++)
    {
        if(maze[0][i] == 1)
            return createCell(0, i);
    }
    return createCell(-1, -1);
}

Cell findEnd(int ** maze, int rows, int cols)
{
    for(int i=0; i<cols; i++)
    {
        if(maze[rows-1][i] == 1)
            return createCell(rows-1, i);
    }
    return createCell(-1, -1);
}

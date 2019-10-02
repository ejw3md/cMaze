#include <stdio.h>
#include <stdlib.h>

#include "ECL/ECL_queue.h"

typedef struct mazeType
{
    int val;
    int visited;
}MazeType;

typedef struct cell
{
    int r;
    int c;
    struct cell * prev;
}Cell;

int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

MazeType ** createMaze(char * filename, int * rows, int * cols);
void printMaze(MazeType ** maze, int rows, int cols);
Cell * createCell(int r, int c);
Cell * findStart(MazeType ** maze, int rows, int cols);
Cell * findEnd(MazeType ** maze, int rows, int cols);
Cell * BFS(MazeType ** maze, int rows, int cols, Queue * garbageCollect);
int isValid(int rows, int cols, int r, int c);
void printPath(Cell * end, char * filename);
void freeMaze(MazeType ** maze, int rows, int cols);

int main(int argc, char ** argv)
{
    if(argc!= 2)
    {
        printf("Format of file is ./a.out <input_file>\n");
        return 0;
    }
    int rows, cols;
    MazeType ** maze = createMaze(argv[1], &rows, &cols);
    Queue * garbageCollect = initQueue();
    Cell * end = BFS(maze, rows, cols, garbageCollect);
    printPath(end, "temp2.txt");
    freeQueue(garbageCollect);
    freeMaze(maze, rows, cols);

    return 0;
}

Cell * createCell(int r, int c)
{
    Cell * new = malloc(sizeof(Cell));
    new->r = r;
    new->c = c;
    new->prev = NULL;
    return new;
}

int isValid(int rows, int cols, int r, int c)
{
    return r>=0 && r<rows && c>=0 && c<cols;
}

MazeType ** createMaze(char * filename, int * rows, int * cols)
{
    FILE * f = fopen(filename, "r");
    int r, c;
    fscanf(f, "%d %d", &r, &c);
    MazeType ** maze = malloc(sizeof(MazeType *) * r);
    for(int i=0; i<r; i++)
    {
        maze[i] = malloc(sizeof(MazeType) * c);
    }

    for(int i=0; i<r; i++)
    {
        char temp;
        fscanf(f, "%c", &temp);             //this fscanf gets rid of the newlines
        for(int j=0; j<c; j++)
        {
            fscanf(f, "%c", &temp);
            maze[i][j].val = temp - '0';
            maze[i][j].visited = 0;
        }

    }
    *rows = r;
    *cols = c;
    return maze;
}

Cell * findStart(MazeType ** maze, int rows, int cols)
{
    for(int i=0; i<cols; i++)
    {
        if(maze[0][i].val == 1)
            return createCell(0, i);
    }
    return createCell(-1, -1);
}

Cell * findEnd(MazeType ** maze, int rows, int cols)
{
    for(int i=0; i<cols; i++)
    {
        if(maze[rows-1][i].val == 1)
            return createCell(rows-1, i);
    }
    return createCell(-1, -1);
}

Cell * BFS(MazeType ** maze, int rows, int cols, Queue * garbageCollect)
{
    Queue * queue = initQueue();

    Cell * start = findStart(maze, rows, cols);
    Cell * end = findEnd(maze, rows, cols);

    queuePush(garbageCollect, end);

    Cell * cur;
    int found = 0;

    maze[start->r][start->c].visited = 1;
    queuePush(queue, start);

    while(!queueEmpty(queue))
    {
        cur = queuePop(queue);
        queuePush(garbageCollect, cur);
        if(cur->r == end->r && cur->c == end->c)
        {
            found = 1;
            break;
        }

        for(int i=0; i<4; i++)
        {
            int newr, newc;
            newr = cur->r + directions[i][0];
            newc = cur->c + directions[i][1];
            if(isValid(rows, cols, newr, newc) && maze[newr][newc].val == 1 && !maze[newr][newc].visited)
            {
                Cell * new = createCell(newr, newc);
                new->prev = cur;
                maze[newr][newc].visited = 1;
                queuePush(queue, new);
            }
        }
    }
    freeQueue(queue);
    if(found)
        return cur;
    return NULL;
}

void printPath(Cell * end, char * filename)
{
    FILE * f = fopen(filename, "w");
    Cell * itr = end;
    while(itr)
    {
        fprintf(f, "%d %d\n", itr->r, itr->c);
        itr = itr->prev;
    }
}

void freeMaze(MazeType ** maze, int rows, int cols)
{
    for(int i=0; i<rows; i++)
    {
        free(maze[i]);
    }
    free(maze);
}

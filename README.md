# cMaze
This directory will solve an n x n maze. The input file of the maze is of file format png and must have its start in the top row, and
its end at the bottom row. Every pixel in the maze is black or white, black signaling wall and white signaling path. When solved
the path will be outlined in red, and the image will be saved to the solved directory.

main.py - main driver of the program, uses PIL library to read and edit the image, and calls solve.c. One improvement
to speed that could be made to this program is to use libpng library to parse image, avoiding use of python altogether

solve.c - uses parsed image output from main.py to do a simple BFS on the graph, and output path coordinates into a temporary file

ECL - "Ethan Common Library" - submodule used to implement queues 

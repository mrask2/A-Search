# A* Search Algorithm

## Structure
The structure of the codebase is as follows: 

data - contains the datasets we tested on in .txt or .csv format

lib - contains the PNG classes with functions we used to create images (part of Illinois CS225 course)

src - contains our code for creation and traversion of Grids and Points, as well as the implementation for the algorithm itself 

tests - contain our test cases, as well as helper functions to test our code effectivley

## Running Instructions
cd into the repository, run command mkdir build. cd into build, run command make. Given a csv or txt file of two numbers, one number representing a wall and the other a passable tile, create a new Grid variable. Then, readFromCSV to that variable the file you want to create a grid from. ceatePointMaze with your goal x and y coordinates as parameters. 

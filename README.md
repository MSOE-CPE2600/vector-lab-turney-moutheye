## How the Program Works

Vectors can be created or cleared. Math operations can be performed on the vectors and their results will be displayed. This result also can be given a name so that it will be saved. You can also have a text file in the format of v, 3, 2, 1 and the vector will be loaded in. You can also save the current list of vectors that you have.

## How to build the program

Using a make file - make 

## How to run program

1. vector_calc
   - runs program normally
2. vector_calc -h 
   - displays the help menu before running the program

## Supported commands

        create <name> <x> <y> <z>   - Create or replace a vector
        add <name1> <name2>         - Add two vectors
        sub <name1> <name2>         - Subtract second vector from first
        scale <name> <scalar>       - Multiply vector by scalar
        list                        - Show all stored vectors
        clear                       - Remove all stored vectors
        q                           - Exit the program
        a + b, a - b, a * 2, 2 * a  - Math opperations
        load <filename>             - loads in filename of vectors
        save <filename>             - saves list as <filename>

## Dynamic Memory Usage

This program uses dynamic memory to allocate space in the array of vectors. It does this using the realloc() function to continually add more space to storage before an array is made. Unlike the first version where the storage was fixed at a value of 10 vectors, v2.0 allows as many vectors as you want to add. The program then uses free() at the end to free storage preventing any possible memory leaks.

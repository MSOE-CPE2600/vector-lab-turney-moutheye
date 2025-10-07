/*
* filename: vector.h
* author: Elias Mouthey
* date: 9/30/25
* description: vector declaration
* Note: 
*/

void program(int argc, char *argv[]); //run program

typedef struct vector
{
    char name[10];
    double x;
    double y;
    double z;
} vector;

vector add(vector a, vector b);
vector sub(vector a, vector b);
vector scale(vector a, double scalar);
void print_result(vector a);    
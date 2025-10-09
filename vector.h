/*
* filename: vector.h
* author: Elias Mouthey
* date: 10/7/25
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

vector add(vector a, vector b); //add function
vector sub(vector a, vector b); //subtract function
vector scale(vector a, double scalar); //scale function
void help_menu(); //help menu
void print_result(vector a); //prints the resulting vector name and values
void updatevect(vector v);


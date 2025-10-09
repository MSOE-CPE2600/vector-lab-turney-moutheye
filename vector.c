/*
* filename: vector.c
* author: Elias Mouthey
* date: 10/10/25
* description: vector definition
* Note: 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

#define MAX_VECTORS 10
static vector storage[MAX_VECTORS];
static int v_count = 0;

vector add(vector a, vector b)
{
    vector result;
    strcpy(result.name, "sum");
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

vector sub(vector a, vector b)
{
    vector result;
    strcpy(result.name, "sub");
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;

}

vector scale(vector v, double scalar)
{
    vector result;
    strcpy(result.name, "scalar");
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;

}

//helper method to update vector
void updatevect(vector v) 
{
    for (int i = 0; i < v_count; i++) 
    {
        if (strcmp(storage[i].name, v.name) == 0) 
        {
            storage[i] = v;  // overwrite existing vector
            return;
        }
    }
}

void help_menu()
{
    printf("Vector Calculator Help:\n");
    printf("Commands:\n");
    printf("  <name> = <x> <y> <z>        - Create or replace a vector\n");
    printf("  list                        - Show all stored vectors\n");
    printf("  clear                       - Remove all stored vectors\n");
    printf("  q                           - Exit the program\n");
    printf("  a + b, a - b, a * 2, 2 * a  - another way to perform operations\n");
    printf("\n");
}

void print_result(vector a)
{
    printf("%s: (%.2f, %.2f, %.2f)\n", a.name, a.x, a.y, a.z);
}   

///storage for vectors///

int addvect(vector new) {
    // Check for existing name
    for (int i = 0; i < v_count; ++i) 
    {
        if (strcmp(storage[i].name, new.name) == 0) 
        { 
            printf("Updated vector '%s'\n", new.name);
            storage[i] = new; 
            return 1;
        }
    }

    // Adds to next spot in array if there is space
    if (v_count < MAX_VECTORS) 
    {
        storage[v_count++] = new;
        printf("Added vector '%s'\n", new.name);
        return 1;
    }


    return 0;
}

//vector finder in my storage
vector *findvect(const char *name) 
{
    for (int i = 0; i < v_count; ++i) 
    {
        if (strcmp(storage[i].name, name) == 0)
            return &storage[i];
    }

    return NULL;
}

//clear function
void clear()
{
    v_count = 0;
}
void stored_vectors()
{
    if(v_count == 0)
    {
        printf("There are currently no vectors created\n");
    } 
    else 
        {
            for (int i = 0; i < v_count; ++i) 
            {
                printf("%s: (%.2f, %.2f, %.2f)\n",
                storage[i].name,
                storage[i].x,
                storage[i].y,
                storage[i].z);
            }
        }
}

///interface area///

void program(int argc, char *argv[])
{

       //help command
    if (argc == 2 && strcmp(argv[1], "-h") == 0) 
    {
        help_menu();

    }

    char input[100];
    printf("Welcome to the vector calculator! Type 'q' to quit. or type h to provide a list of commands to begin\n");

    while (1)
    {
        printf("> ");

         // Expressions
        char res [10];
        char var1[10];
        char var2[10];
        double scalar;

        if (!fgets(input, sizeof(input), stdin))
        {
            break;
        } 
        input[strcspn(input, "\n")] = '\0';

        //quit command
        if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0)
        {
            printf("Quitting...\n");
            break;
        }

        if(strcmp(input, "h") == 0)
        {
            help_menu();
        }

               //operation plus assignment
        if(sscanf(input, "%s = %s + %s", res, var1, var2) == 3)
        {
            vector *a = findvect(var1);
            vector *b = findvect(var2);
            if (a == NULL || b == NULL)
            {
                printf("Error: One or both vectors not found.\n");
            } 
            else 
            {
                vector result = add(*a, *b);
                strncpy(result.name, res, sizeof(result.name) - 1);
                result.name[sizeof(result.name) - 1] = '\0';
                if (addvect(result))
                {
                    print_result(result);
                } 
                else 
                {
                    printf("Error: Memory full.\n");
                }
                
            }
            continue;
        }
        
        //operation subtraction assignment
         if(sscanf(input, "%s = %s - %s", res, var1, var2) == 3)
        {
            vector *a = findvect(var1);
            vector *b = findvect(var2);
            if (a == NULL || b == NULL) 
            {
                printf("Error: One or both vectors not found.\n");
            } 
            else 
            {
                vector result = sub(*a, *b);
                strncpy(result.name, res, sizeof(result.name) - 1);
                result.name[sizeof(result.name) - 1] = '\0';
                if (addvect(result))
                {
                    print_result(result);
                } 
                else 
                {
                    printf("Error: Memory full.\n");
                }
            }
            continue;
        }

        //operation vector first then scalar assignment
        if (sscanf(input, "%s = %s * %lf", res, var1, &scalar) == 3) 
        {
            vector *a = findvect(var1);
            if (a == NULL)
            {
                printf("Error: Vector '%s' not found.\n", var1);
            } 
            else 
            {
                vector result = scale(*a, scalar);
                strncpy(result.name, res, sizeof(result.name) - 1);
                result.name[sizeof(result.name) - 1] = '\0';
                if (addvect(result))
                {
                    print_result(result);
                } 
                else 
                {
                    printf("Error: Memory full.\n");
                }
            }
            continue;
        }
        //operation scalar first then vector assignment
        if (sscanf(input, "%s = %lf * %s", res, &scalar, var1) == 3) 
        {
            vector *a = findvect(var1);
            if (a == NULL) 
            {
                printf("Error: Vector '%s' not found.\n", var1);
            } 
            else 
            {
                vector result = scale(*a, scalar);
                strncpy(result.name, res, sizeof(result.name) - 1);
                result.name[sizeof(result.name) - 1] = '\0';
                if (addvect(result))
                {
                    print_result(result);
                } 
                else
                {
                    printf("Error: Memory full.\n");
                } 
            }
            continue;
        }

        // Assignment expression
        if (strchr(input, '=') != NULL) 
        {
                char name[10], values[100];
                double x = 0.0; 
                double y = 0.0;
                double z = 0.0;

        
                if (sscanf(input, " %[^=]=%[^\n]", name, values) == 2) 
                {
       
                    int len = strlen(name);
                    while (len > 0 && (name[len - 1] == ' ' || name[len - 1] == '\t')) 
                    {
                        name[len - 1] = '\0';
                        len--;
                    }

                    for (int i = 0; values[i]; i++) 
                    {
                        if (values[i] == ',') 
                        values[i] = ' ';
                    }

                    int count = sscanf(values, "%lf %lf %lf", &x, &y, &z);
                    if (count < 2) 
                    {
                        printf("Invalid vector components. At least x and y required.\n");
                        continue;
                    }

    
                    vector v;
                    strncpy(v.name, name, sizeof(v.name) - 1);
                    v.name[sizeof(v.name) - 1] = '\0';
                    v.x = x;
                    v.y = y;
                    if (count == 3) 
                    {
                        v.z = z;
                    } 
                    else 
                    {
                        v.z = 0.0;
                    }

                    //adds new vector to the list of vectors if it hasnt already been created 
                    //otherwise it just updates the existing one
                    vector *existing = findvect(name); 
                   if (existing != NULL) 
                   {
                       
                        updatevect(v); 
                        printf("Updated vector '%s' to (%.2f, %.2f, %.2f)\n",
                        v.name, v.x, v.y, v.z);
                    } 
                    //create new vector
                    else if (addvect(v)) 
                    {
                        print_result(v);
                    } 
                    else 
                    {
                        printf("Error: Memory full. Cannot store more vectors. ");
                        printf("Please clear list before creating another vector! \n");
                    }

                    continue;
                } 
                else 
                {
                    printf("Invalid assignment format. Use: name = x,y,z or name = x y z\n");
                    continue;
                }
        }


        //addition line
        if (sscanf(input, "%s + %s", var1, var2) == 2) 
        {
            vector *a = findvect(var1);
            vector *b = findvect(var2);
            if (a == NULL || b == NULL)
            {
                printf("Error: One or both vectors not found.\n");
            } else 
            {
                print_result(add(*a, *b));
            }
            continue;
        }

        //subtraction line
        if (sscanf(input, "%s - %s", var1, var2) == 2) 
        {
            vector *a = findvect(var1);
            vector *b = findvect(var2);
            if (a == NULL || b == NULL)
            {
                printf("Error: One or both vectors not found.\n");
            } else {
                print_result(sub(*a, *b));
            }
            continue;
        }

        //scalar line vector first
        if (sscanf(input, "%s * %lf", var1, &scalar) == 2) 
        {
            vector *a = findvect(var1);
            if (a == NULL)
            {
                printf("Error: Vector '%s' not found.\n", var1);
            } else {
                print_result(scale(*a, scalar));
            }
            continue;
        }

        //scalar line scalar first
        if (sscanf(input, "%lf * %s", &scalar, var1) == 2) 
        {
            vector *a = findvect(var1);
            if (a == NULL) 
            {
                printf("Error: Vector '%s' not found.\n", var1);
            } else {
                print_result(scale(*a, scalar));
            }
            continue;
        }

        //list
        if (strcmp(input, "list") == 0) 
        {
            stored_vectors();
            continue;
        }

        //clear
        if (strcmp(input, "clear") == 0) 
        {
            clear();
            printf("All vectors cleared.\n");
            continue;
        } 

        vector* v = findvect(input);
        if (v == NULL) 
        {
            printf("Unknown command or vector '%s' not found.\n", input);
            printf("If you are attempting to add, subtract, or multiply make"); 
            printf(" sure you have space in-between characters and sign!\n");
            printf("Example: v1 + v2\n");

        } 
        else 
        {
            print_result(*v);
        }
    }
}
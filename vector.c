/*
* filename: vector.c
* author: Elias Mouthey
* date: 10/21/25
* description: vector definition
* Note: 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"


vector *storage = NULL;
int v_count = 0;
char fname[100];


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
            storage[i] = new; 
            return 1;
        }
    }

    // Adds to next spot in array
    vector *temp = realloc(storage, (v_count + 1) * sizeof(vector));
    if (temp == NULL) 
    {
        return 0;
    }
    storage = temp;
    storage[v_count++] = new;
    return 1;
}

//vector finder in my storage
vector findvect(const char *name) 
{
    for (int i = 0; i < v_count; ++i) 
    {
        if (strcmp(storage[i].name, name) == 0)
            return storage[i];
    }

    vector empty;
    strcpy(empty.name, "not found");
    empty.x = 0.0;
    empty.y = 0.0;
    empty.z = 0.0;
    return empty;
}
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

    int load_vectors(const char *fname)
    {
        FILE *vec_file = fopen(fname, "r");
        if (vec_file == NULL) 
        {
            return 0;
        }

        vector temp;
        //scan for name, x, y, z
        while (fscanf(vec_file, " %49[^,], %lf, %lf, %lf", temp.name, &temp.x, &temp.y, &temp.z) == 4) 
        {
            addvect(temp);
        }

        fclose(vec_file);
        return 1;
        }

    int save_vectors(const char *save_name)
    {
        FILE *vec_file = fopen(save_name, "w");
        if(vec_file == NULL)
        {
            printf("Error opening file");
            return 0;
        }

        for(int i = 0; i<v_count; i++)
        {
            if (strcmp(storage[i].name, "") != 0) 
            {
            fprintf(vec_file, "%s, %.2lf, %.2lf, %.2lf\n", storage[i].name,
                    storage[i].x, storage[i].y, storage[i].z);
            }
        }
        fclose(vec_file);
        return 1;

    }

///interface area///

void program(int argc, char *argv[])
{

       //help command
    if (argc == 2 && strcmp(argv[1], "-h") == 0) 
    {
        printf("Vector Calculator Help:\n");
        printf("Commands:\n");
        printf("  create <name> <x> <y> <z>   - Create or replace a vector\n");
        printf("  add <name1> <name2>         - Add two vectors\n");
        printf("  sub <name1> <name2>         - Subtract second vector from first\n");
        printf("  scale <name> <scalar>       - Multiply vector by scalar\n");
        printf("  list                        - Show all stored vectors\n");
        printf("  clear                       - Remove all stored vectors\n");
        printf("  q                           - Exit the program\n");
        printf("  a + b, a - b, a * 2, 2 * a  - Math opperations\n");
        printf("  load <filename>             - loads in filename of vectors\n");
        printf("  save <filename>             - saves list as <filename>\n\n");

        
    }

    char input[100];
    printf("Welcome to the vector calculator! Type 'q' to quit. or -h to provide a list of commands\n");

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
        if (strcmp(input, "q") == 0) 
        {
            printf("Quitting...\n");
            break;
        }

               //operation plus assignment
        if(sscanf(input, "%s = %s + %s", res, var1, var2) == 3)
        {
            vector a = findvect(var1), b = findvect(var2);
            if (strcmp(a.name, "not found") == 0|| strcmp(b.name, "not found") == 0) 
            {
                printf("Error: One or both vectors not found.\n");
            } 
            else 
            {
                vector result = add(a, b);
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
            vector a = findvect(var1), b = findvect(var2);
            if (strcmp(a.name, "not found") ==0 || strcmp(b.name, "not found") ==0) {
                printf("Error: One or both vectors not found.\n");
            } else {
                vector result = sub(a, b);
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
            vector a = findvect(var1);
            if (strcmp(a.name, "not found") == 0) 
            {
                printf("Error: Vector '%s' not found.\n", var1);
            } 
            else 
            {
                vector result = scale(a, scalar);
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
        if (sscanf(input, "%s = %lf * %s", res, &scalar, var1) == 3) {
            vector a = findvect(var1);
            if (strcmp(a.name, "not found") == 0) {
                printf("Error: Vector '%s' not found.\n", var1);
            } else {
                vector result = scale(a, scalar);
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

            if (sscanf(input, "%s = %[^\n]", name, values) == 2) 
            {
                for (int i = 0; values[i]; i++) {
                    if (values[i] == ',') values[i] = ' ';
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

                if (addvect(v)) 
                {
                    print_result(v);
                } 
                else 
                {
                    printf("Error: Memory full. Cannot store more vectors.\n");
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
            vector a = findvect(var1);
            vector b = findvect(var2);
            if (strcmp(a.name, "not found") == 0 || strcmp(b.name, "not found") == 0) 
            {
                printf("Error: One or both vectors not found.\n");
            } else 
            {
                print_result(add(a, b));
            }
            continue;
        }

        //subtraction line
        if (sscanf(input, "%s - %s", var1, var2) == 2) 
        {
            vector a = findvect(var1);
            vector b = findvect(var2);
            if (strcmp(a.name, "not found") == 0 || strcmp(b.name, "not found") == 0) 
            {
                printf("Error: One or both vectors not found.\n");
            } else {
                print_result(sub(a, b));
            }
            continue;
        }

        //scalar line vector first
        if (sscanf(input, "%s * %lf", var1, &scalar) == 2) 
        {
            vector a = findvect(var1);
            if (strcmp(a.name, "not found") == 0) 
            {
                printf("Error: Vector '%s' not found.\n", var1);
            } else {
                print_result(scale(a, scalar));
            }
            continue;
        }

        //scalar line scalar first
        if (sscanf(input, "%lf * %s", &scalar, var1) == 2) 
        {
            vector a = findvect(var1);
            if (strcmp(a.name, "not found") == 0) 
            {
                printf("Error: Vector '%s' not found.\n", var1);
            } else {
                print_result(scale(a, scalar));
            }
            continue;
        }




        // commands
        //create
        if (strncmp(input, "create", 6) == 0) 
        {
            char name[10];
            double x, y, z;
            if (sscanf(input, "create %s %lf %lf %lf", name, &x, &y, &z) == 4) 
            {
                vector v;
                strncpy(v.name, name, sizeof(v.name) - 1);
                v.name[sizeof(v.name) - 1] = '\0';
                v.x = x; 
                v.y = y; 
                v.z = z;
                if (addvect(v)) 
                {
                    printf("Vector '%s' added.\n", v.name);
                } 
                else 
                {
                    printf("Error: Memory full.\n");
                }
            } 
            else 
            {
                printf("Usage: create <name> <x> <y> <z>\n");
            }
            continue;
        }
        //scalar
        if (strncmp(input, "scale", 5) == 0) 
        {
            char name[10];
            double scalar;
            if (sscanf(input, "scale %s %lf", name, &scalar) == 2) 
            {
                vector a = findvect(name);
                if (strcmp(a.name, "not found") == 0) 
                {
                    printf("Error: Vector '%s' not found.\n", name);
                } 
                else 
                {
                    print_result(scale(a, scalar));
                }
            } 
            else 
            {
                printf("Usage: scale <name> <scalar>\n");
            }
        continue;
        }

        //add function
        if (strncmp(input, "add", 3) == 0) 
        {
            char name1[10], name2[10];
            if (sscanf(input, "add %s %s", name1, name2) == 2) 
            {
                vector a = findvect(name1);
                vector b = findvect(name2);
                if (strcmp(a.name, "not found") == 0 || strcmp(b.name, "not found") == 0) 
                {
                    printf("Error: One or both vectors not found.\n");
                } 
                else 
                {
                    print_result(add(a, b));
                }
            } 
            else 
            {
                printf("Usage: add <name1> <name2>\n");
            }
            continue;
        }

        //sub
        if (strncmp(input, "sub", 3) == 0) 
        {
            char name1[10], name2[10];
            if (sscanf(input, "sub %s %s", name1, name2) == 2) 
            {
                vector a = findvect(name1);
                vector b = findvect(name2);
                if (strcmp(a.name, "not found") == 0 || strcmp(b.name, "not found") == 0) 
                {
                    printf("Error: One or both vectors not found.\n");
                } 
                else 
                {
                    print_result(sub(a, b));
                }
            } 
            else 
            {
                printf("Usage: sub <name1> <name2>\n");
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

        //load
        if (strncmp(input, "load ", 5) == 0 && sscanf(input, "load %99s", fname) == 1) 
        {
            if (strchr(fname, ' ') != NULL) 
            {
                printf("Error: filename cannot contain spaces.\n");
                continue;
            }
            if (load_vectors(fname)) 
            {
                clear();
                load_vectors(fname);
                printf("Vectors loaded from %s\n", fname);
                continue;
            } 
            else 
            {
                printf("Failed to load vectors from %s\n", fname);
                continue;
            }
        } 
        //save
        if (sscanf(input, "save %99s", fname) == 1) 
        {
            if (save_vectors(fname)) 
            {
                printf("Vectors saved to %s\n", fname);
                continue;
        
            } 
            else 
            {
                printf("Failed to save vectors to %s\n", fname);
                continue;
            }
        } 
    
        vector v = findvect(input);
        if (strcmp(v.name, "not found") == 0) 
        {
            printf("Unknown command or vector '%s' not found.\n", input);
            printf("If you are attempting to add, subtract, or multiply make"); 
            printf(" sure you have space in-between characters and sign!\n");
            printf("Example: v1 + v2\n");

        } 
        else 
        {
            print_result(v);
        }
    }
    free(storage);
}
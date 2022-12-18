#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Penguin
{
    int x[9];
    int y[9];
};
struct Penguin penguins;

int placePenguin(int rows, int cols, int **matrix, int currentPeng);
int updateBoard(char outputFile[20], int rows, int cols, int **matrix);
int readBoard(char inputFile[20], int rows, int cols, int **matrix);
void movePenguin(int rows, int cols, int **matrix, char outputFile[20], int i);
int PenguinCanMove(int **matrix, int i);
int main(int argc, char *argv[])
{
    if (argv[1] == "name")
    {
        printf("%s", argv[1]);
    }
    int numberOfPenguins;
    char filename[20];
    char stage[20];
    char inputFile[20];
    char outputFile[20];
    char firstArgument[20];
    strcpy(firstArgument, argv[1]);
    int **matrix;
    int rows, cols;
    if (strcmp(firstArgument, "phase=placement") == 0)
    {
        if (argc < 5)
        {
            printf("Not enough parameters");
            return 1;
        }
        numberOfPenguins = argv[2][9] - 48;
        if (numberOfPenguins < 1)
        {
            printf("There must be at least 1 penguin");
            return 1;
        }
        strcpy(filename, argv[0]);
        strcpy(stage, argv[1]);
        strcpy(inputFile, argv[3]);
        strcpy(outputFile, argv[4]);
        // printf("%s %s %d %s %s\n", filename, stage, numberOfPenguins, inputFile, outputFile);
    }
    else if (strcmp(firstArgument, "phase=movement") == 0)
    {
        if (argc < 4)
        {
            printf("Not enough parameters");
            return 1;
        }
        strcpy(filename, argv[0]);
        strcpy(stage, argv[1]);
        strcpy(inputFile, argv[2]);
        strcpy(outputFile, argv[3]);
        // printf("%s %s %s %s\n", filename, stage, inputFile, outputFile);
    }
    else
    {
        printf("Value for phase has been incorrectly entered");
    }
    FILE *input;

    input = fopen(inputFile, "r");
    if (input == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read number of rows and columns
    fscanf(input, "%d %d", &rows, &cols);

    // Allocate memory for rows
    matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL)
    {
        perror("Error allocating memory");
        return 1;
    }

    // Allocate memory for columns
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            perror("Error allocating memory");
            return 1;
        }
    }

    // Read matrix from file
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(input, "%2d", &matrix[i][j]);
        }
    }

    fclose(input);
    // Print matrix to check that it was read correctly
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    if (strcmp(firstArgument, "phase=placement") == 0)
    {
        for (int currentPeng = 0; currentPeng < numberOfPenguins; currentPeng++)
        {
            placePenguin(rows, cols, matrix, currentPeng);
        }
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (strcmp(firstArgument, "phase=movement") == 0)
    {
        int i = 0;
        while (i < numberOfPenguins)
        {
            if (PenguinCanMove(matrix, i) == 0)
            {
                i++;
                continue;
            }
            else
            {
                movePenguin(rows, cols, matrix, outputFile, i);
                break;
            }
        }
    }
    return 0;
}
int placePenguin(int rows, int cols, int **matrix, int currentPeng)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 10)
            {
                penguins.x[currentPeng] = j;
                penguins.y[currentPeng] = i;
                matrix[i][j] = 01;
                return 0;
            }
        }
    }
}
int updateBoard(char outputFile[20], int rows, int cols, int **matrix)
{
    FILE *output;

    output = fopen(outputFile, "w");
    if (output == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read number of rows and columns
    fprintf(output, "%d %d\n", rows, cols);

    // Read matrix from file
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(output, "%2d ", matrix[i][j]);
        }
        fprintf(output, "\n");
    }

    fclose(output);
}
void movePenguin(int rows, int cols, int **matrix, char outputFile[20], int i)
{
    if (matrix[penguins.y[i]][penguins.x[i] + 1] == 30)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.x[i]++;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i] + 1][penguins.x[i]] == 30)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.y[i]++;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i] - 1][penguins.x[i]] == 30)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.y[i]--;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i]][penguins.x[i] - 1] == 30)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.x[i]--;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i]][penguins.x[i] + 1] == 20)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 0;
        penguins.x[i]++;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i] + 1][penguins.x[i]] == 20)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.y[i]++;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i] - 1][penguins.x[i]] == 20)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.y[i]--;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i]][penguins.x[i] - 1] == 20)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.x[i]--;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i]][penguins.x[i] + 1] == 10)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.x[i]++;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i] + 1][penguins.x[i]] == 10)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.y[i]++;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i] - 1][penguins.x[i]] == 10)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.y[i]--;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
    else if (matrix[penguins.y[i]][penguins.x[i] - 1] == 10)
    {
        matrix[penguins.y[i]][penguins.x[i]] = 00;
        penguins.x[i]--;
        matrix[penguins.y[i]][penguins.x[i]] = 01;
        updateBoard(outputFile, rows, cols, matrix);
    }
}
int PenguinCanMove(int **matrix, int i)
{
    // YousefCode
    if ((matrix[penguins.y[i]][penguins.x[i] + 1] >= 10) || matrix[penguins.y[i]][penguins.x[i] - 1] >= 10 || matrix[penguins.y[i] - 1][penguins.x[i]] >= 10 || matrix[penguins.y[i] + 1][penguins.x[i]] >= 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
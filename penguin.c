#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Declaring variables
int columns, rows, numberOfPlayers, numberOfPenguins, totalPenguins, fish, moveR, moveC, p, move, plays, stuck_players, g;
double maxPenguins, rounds;
int playersPlayed;
int numbers[25][25];
char first_place[12];
char name[12];
int scoreboard[10];
char letter;
typedef struct
{
    char name[12];
    int score;
    int moves;
    int positionR;
    int positionC;
    bool canMove;
} Players;
Players players[10];
// Declaring Functions
void create_board();
int check_free_spaces();
void player_move();
void check_1st_place();
void check_2nd_place();
void check_3rd_place();
void print_board();
void printArray(int array[], int size);
void sort(int array[], int size);

int main()
{
    srand(time(0));

    // Taking input to make the table
    while (true)
    {
        printf("Enter number of columns:");
        scanf("%d", &columns);
        if (columns <= 0)
        {
            printf("Columns must have a positive value\n");
            continue;
        }
        printf("Enter number of rows: ");
        scanf("%d", &rows);
        if (columns * rows >= 25)
        {
            // Create board
            create_board();
            break;
        }
        else
        {
            printf("Board is too small\n");
        }
    }

    // Make sure the table is not too crowded
    while (true)
    {
        printf("Enter number of players: ");
        scanf("%d", &numberOfPlayers);
        if (numberOfPlayers <= 1 || numberOfPlayers > 10)
        {
            printf("Invalid number of players\n");
            continue;
        }
        printf("Enter number of penguins per player: ");
        scanf("%d", &numberOfPenguins);
        if (numberOfPenguins <= 0)
        {
            printf("Invalid number of penguins\n");
            continue;
        }
        totalPenguins = numberOfPenguins * numberOfPlayers;
        maxPenguins = 0.5 * sqrt(rows * columns);
        if (totalPenguins <= maxPenguins)
        {
            break;
        }
        else
        {
            printf("Error: Too many players/penguins!\n");
        }
    }
    char penguins[numberOfPenguins * 2];

    // Start game

    for (int p = 0; p < numberOfPlayers; p++)
    {
        printf("Player %d's turn\n", p + 1);
        printf("Enter player's name:");
        scanf("%s", name);
        strcpy(players[p + 1].name, name);
        //  Placing penguins
        for (int n = 1; n <= numberOfPenguins; n++)
        {
            while (true)
            {
                printf("Which row do you want to place penguin no.%d on?\n", n);
                scanf("%d", &moveR);
                printf("Which column do you want to place penguin no.%d on?\n", n);
                scanf("%d", &moveC);
                if (numbers[moveR][moveC] == 1)
                {
                    players[p + 1].positionR = moveR;
                    players[p + 1].positionC = moveC;
                    players[p + 1].score += 1;
                    numbers[players[p + 1].positionR][players[p + 1].positionC] = players[p + 1].name[0];
                    print_board();
                    break;
                }
                else
                {
                    printf("Penguin must be placed on block with one penguin only\n");
                };
            }
        };
    };
    // Moving phase
    while (g == 0)
    {
        for (p = 0; p < numberOfPlayers; p++)
        {
            if (stuck_players == numberOfPlayers)
            {
                g = 1;
            }
            else
            {
                if (check_free_spaces() == 1)
                {
                    stuck_players = 0;
                }
                else
                {
                    stuck_players++;
                    continue;
                }
            }
            for (int penguinsMoved = 0; penguinsMoved < numberOfPenguins; penguinsMoved++)
            {
                if (check_free_spaces() == 1)
                {
                    printf("%s's turn:\n", players[p + 1].name);
                    players[p + 1].canMove = true;
                    player_move();
                    print_board();
                }
                else
                {
                    players[p + 1].canMove = false;
                }
            }
        }
    }
    int n = 0;
    for (p = 0; p < numberOfPlayers; p++)
    {
        scoreboard[p] = players[p + 1].score;
    }
    int size = sizeof(scoreboard) / sizeof(scoreboard[0]);
    sort(scoreboard, size);
    check_1st_place();
    check_2nd_place();
    check_3rd_place();
    return 0;
}

void create_board()
{
    for (int i = 0; i < rows; i++)
    {
        printf("  |");
        for (int j = 0; j < columns; j++)
        {
            fish = rand() % 4;
            numbers[i][j] = fish;
            if (numbers[i][j] > 3)
            {
                printf(" %c", numbers[i][j]);
                printf(" |");
            }
            else
            {
                printf(" %d", numbers[i][j]);
                printf(" |");
            }
        }
        printf("\n--");
        for (int dashes = 1; dashes <= columns; dashes++)
        {
            printf("|---");
        }
        printf("|--\n");
    }
}
void print_board()
{
    for (int i = 0; i < rows; i++)
    {
        printf("  |");
        for (int j = 0; j < columns; j++)
        {
            if (numbers[i][j] > 3)
            {
                printf(" %c", numbers[i][j]);
                printf(" |");
            }
            else
            {
                printf(" %d", numbers[i][j]);
                printf(" |");
            }
        }
        printf("\n--");
        for (int dashes = 1; dashes <= columns; dashes++)
        {
            printf("|---");
        }
        printf("|--\n");
    }
}
int check_free_spaces()
{
    if (numbers[players[p + 1].positionR + 1][players[p + 1].positionC] == 0 && numbers[players[p + 1].positionR][players[p + 1].positionC + 1] == 0 && numbers[players[p + 1].positionR - 1][players[p + 1].positionC] == 0 && numbers[players[p + 1].positionR][players[p + 1].positionC - 1] == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void player_move()
{
    printf("Where do you want to move? (1=left, 2=up, 3=right, 4= down)\n");
    scanf("%d", &move);
    while (true)
    {
        if (move == 1)
        {
            if (numbers[players[p + 1].positionR][players[p + 1].positionC - 1] == 0)
            {
                printf("Invalid movement\n");
                break;
            }
            else
            {
                printf("%s moved left!\n", players[p+1].name);
                numbers[players[p + 1].positionR][players[p + 1].positionC] = 0;
                players[p + 1].score += numbers[players[p + 1].positionR][players[p + 1].positionC - 1];
                players[p + 1].positionC -= 1;
                numbers[players[p + 1].positionR][players[p + 1].positionC] = players[p + 1].name[0];
                break;
                ;
            }
        }
        else if (move == 2)
        {
            if (numbers[players[p + 1].positionR - 1][players[p + 1].positionC] == 0)
            {
                printf("Invalid movement\n");
                break;
            }
            else
            {
                printf("%s moved up!\n", players[p+1].name);
                numbers[players[p + 1].positionR][players[p + 1].positionC] = 0;
                players[p + 1].score += numbers[players[p + 1].positionR - 1][players[p + 1].positionC];
                players[p + 1].positionR -= 1;
                numbers[players[p + 1].positionR][players[p + 1].positionC] = players[p + 1].name[0];
                break;
            }
        }
        else if (move == 3)
        {
            if (numbers[players[p + 1].positionR][players[p + 1].positionC + 1] == 0)
            {
                printf("Invalid movement\n");
                break;
            }
            else
            {
                printf("%s moved right!\n", players[p+1].name);
                numbers[players[p + 1].positionR][players[p + 1].positionC] = 0;
                players[p + 1].score += numbers[players[p + 1].positionR][players[p + 1].positionC + 1];
                players[p + 1].positionC += 1;
                numbers[players[p + 1].positionR][players[p + 1].positionC] = players[p + 1].name[0];
                break;
            }
        }
        else if (move == 4)
        {
            if (numbers[players[p + 1].positionR + 1][players[p + 1].positionC] == 0)
            {
                printf("Invalid movement\n");
                break;
            }
            else
            {
                printf("%s moved down\n", players[p+1].name);
                numbers[players[p + 1].positionR][players[p + 1].positionC] = 0;
                players[p + 1].score += numbers[players[p + 1].positionR + 1][players[p + 1].positionC];
                players[p + 1].positionR += 1;
                numbers[players[p + 1].positionR][players[p + 1].positionC] = players[p + 1].name[0];

                break;
            }
        }

        else
        {
            printf("Invalid value!\n");
            break;
        }
    }
}
void check_1st_place()
{
    for (int place = 0; place < numberOfPlayers; place++)
    {
        if (scoreboard[0] == players[place + 1].score)
        {
            printf("%s (%d) won \n", players[place + 1].name, players[place + 1].score);
            break;
        }
        else
        {
            continue;
        }
    }
}
void check_2nd_place()
{
    for (int place = 0; place < numberOfPlayers; place++)
    {
        if (scoreboard[1] == players[place + 1].score)
        {
            if(numberOfPlayers == 2)
            {
                printf("%s (%d) lost :( \n", players[place + 1].name, players[place + 1].score);
                break;
            }
            else
            {
                printf("%s (%d) placed second\n", players[place + 1].name, players[place + 1].score);
                break;
            }
        }
        else
        {
            continue;
        }
    }
}
void check_3rd_place()
{
    if (numberOfPlayers > 2)
    {
        for (int place = 0; place < numberOfPlayers; place++)
        {
            if (scoreboard[2] == players[place + 1].score)
            {
                printf("%s (%d) placed third \n", players[place + 1].name, players[place + 1].score);
                break;
            }
            else
            {
                continue;
            }
        }
    }
}
void sort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] < array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}
void checkInput(int input)
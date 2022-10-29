#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Declaring variables
int columns, rows, numberOfPlayers, numberOfPenguins, totalPenguins, fish, moveR, moveC, p, move, plays, stuck_players;
double maxPenguins, rounds;
int playersPlayed;
int numbers[25][25];
char first_place[12];
char name[12];
int scoreboard[10];
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
int roundNearest();
void create_board();
int check_free_spaces();
bool player_move();
char check_1st_place();
char check_2nd_place();
char check_3rd_place();
void print_1st_place(char);
void print_2nd_place(char);
void print_3rd_place(char);
void print_board();

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
        if (numberOfPlayers <= 0)
        {
            printf("Invalid number of players\n");
            continue;
        }
        printf("%d\n", numberOfPlayers);
        printf("Enter number of penguins per player: ");
        scanf("%d", &numberOfPenguins);
        printf("%d\n", numberOfPenguins);
        if (numberOfPlayers < 0)
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
                    players[p + 1].score = 1;
                    numbers[players[p + 1].positionR][players[p + 1].positionC] = 0;
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
    while (true)
    {
        for (p = 0; p < numberOfPlayers; p++)
        {
            for (p = 0; p < numberOfPlayers; p++)
            {
                if (check_free_spaces() == 1)
                {
                    continue;
                }
                else
                {
                    players[p + 1].canMove = false;
                }
                if (players[p + 1].canMove == false)
                {
                    stuck_players++;
                }
            }
            if (stuck_players == numberOfPlayers)
            {
                return false;
            }
            else
            {
                stuck_players = 0;
            }
            printf("%s's turn:\n", players[p + 1].name);
            for (int penguinsMoved = 0; penguinsMoved < numberOfPenguins; penguinsMoved++)
            {
                if (check_free_spaces() == 1)
                {
                    players[p + 1].canMove = true;
                    player_move();
                    print_board();
                }
                else
                {
                    players[p + 1].canMove = false;

                    stuck_players++;

                    if (stuck_players == numberOfPlayers)
                    {
                        return false;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    int n = 0;
    for (p = 0; p < numberOfPlayers; p++)
    {
        scoreboard[p] = players[p + 1].score;
    }
    printf("[");
    for (int scores = 0; scores < 10; scores++)
    {
        if (scoreboard[scores] > 0)
        {
            printf("%d,", scoreboard[scores]);
        }
        else
        {
            continue;
        }
    }
    printf("]\n");
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

            printf(" %d", numbers[i][j]);
            printf(" |");
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
            if (i == players[p + 1].positionR && j == players[p + 1].positionC)
            {
                printf(" %c", players[p + 1].name[0]);
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
    if (numbers[players[p + 1].positionR + 1][players[p + 1].positionC] > 0 || numbers[players[p + 1].positionR][players[p + 1].positionC + 1] > 0 || numbers[players[p + 1].positionR - 1][players[p + 1].positionC] > 0 || numbers[players[p + 1].positionR][players[p + 1].positionC - 1] > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool player_move()
{
    printf("Where do you want to move? (1=left, 2=up, 3=right, 4= down)\n");
    scanf("%d", &move);
    while (true)
    {
        switch (move)
        {
        case 1:
            if (numbers[players[p + 1].positionR][players[p + 1].positionC - 1] == 0)
            {
                printf("Invalid movement\n");
                continue;
            }
            else
            {
                printf("You moved left!\n");
                players[p + 1].score += numbers[players[p + 1].positionR][players[p + 1].positionC - 1];
                numbers[players[p + 1].positionR][players[p + 1].positionC - 1] = 0;
                players[p + 1].positionC -= 1;
                return false;
            }

        case 2:
            if (numbers[players[p + 1].positionR - 1][players[p + 1].positionC] == 0)
            {
                printf("Invalid movement\n");
                continue;
            }
            else
            {
                printf("You moved up!\n");
                players[p + 1].score += numbers[players[p + 1].positionR - 1][players[p + 1].positionC];
                numbers[players[p + 1].positionR - 1][players[p + 1].positionC] = 0;
                players[p + 1].positionR -= 1;
                return false;
            }

        case 3:
            if (numbers[players[p + 1].positionR][players[p + 1].positionC + 1] == 0)
            {
                printf("Invalid movement\n");
                continue;
            }
            else
            {
                printf("You moved right!\n");
                players[p + 1].score += numbers[players[p + 1].positionR][players[p + 1].positionC + 1];
                numbers[players[p + 1].positionR][players[p + 1].positionC + 1] = 0;
                players[p + 1].positionC += 1;
                return false;
            }

        case 4:
            if (numbers[players[p + 1].positionR + 1][players[p + 1].positionC] == 0)
            {
                printf("Invalid movement\n");
                continue;
            }
            else
            {
                printf("You moved down\n");
                players[p + 1].score += numbers[players[p + 1].positionR + 1][players[p + 1].positionC];
                numbers[players[p + 1].positionR + 1][players[p + 1].positionC] = 0;
                players[p + 1].positionR += 1;

                return false;
            }

        default:
            printf("Invalid value!\n");
            continue;
        }
    }
}
char check_1st_place()
{
}
char check_2nd_place()
{
}
char check_3rd_place()
{
}
void print_1st_place(char first)
{
}
void print_2nd_place(char second)
{
}
void print_3rd_place(char third)
{
}
int roundNearest(double x)
{
    if (ceil(x) - x > floor(x) - x)
    {
        return ceil(x);
    }
    else
    {
        return floor(x);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SHIP{
    int row, column, length;
    char direction;
} SHIP;

typedef struct ATTACK{
    int row, column;
} ATTACK;

// these are the prototype functions developed for our solution.  You are welcome to use them 
// or modify them if you have a different strategy for solving this project.
void Read_Save_Game_File(char *filename, int *rows, int *columns, int *ship_count,struct SHIP allShips[100], int *attack_count, struct ATTACK allAttacks[1000]);
void Initialize_Board(int rows, int columns, char **board);
void Print_Board(int rows, int columns, char *board);
void Add_Ships(int rows, int columns, char *board, int ship_count, struct SHIP allShips[100]);
void Process_Attacks(int rows, int columns, char *board, int attack_count,struct ATTACK allAttacks[1000]);
void Game_Over(int rows, int columns, char *board);

int main(int argc, char *argv[] ) {

    // verify command line parameters
    if(argc != 2){
        printf("expected usage: %s <save_game_file>", argv[0]);
        exit(1);
    }
    

    // declare variables - feel free to add additional variables as needed
    char *board = NULL;
    struct SHIP allShips[100];//array to hold all the ships to be added
    struct ATTACK allAttacks[1000];//array to hold all the attacks to be added
    int rows=0, columns=0, ship_count=0, attack_count=0;
    
    // read the save game file
    Read_Save_Game_File(argv[1], &rows, &columns, &ship_count, allShips, &attack_count, allAttacks);
    /* Note: Reading the file and using malloc to reserve space for 
     * the data may be easier to do here, in main, rather than in a 
     * function */

    // Generate the board;
    Initialize_Board(rows, columns, &board);
    Print_Board(rows, columns, board);

    // Add Ships to the board;
    Add_Ships(rows, columns, board, ship_count, allShips);
    Print_Board(rows, columns, board);

    // Process Attacks
    Process_Attacks(rows, columns, board, attack_count, allAttacks);
    Print_Board(rows, columns, board);
    
    //checks if all ships were sunk
    Game_Over(rows, columns, board);
    
    // free memory
    free(board);

    return 0;
}

////////////////////////////////////////////
// reads in the file to create all the ships, attacks, and store the baord; we pass in the filename so we can read it, the rows, columns, ship_count, and attack_count pointers to change them, and the trwo array to store the ships and attaks for later use; no return 
////////////////////////////////////////////
void Read_Save_Game_File(char *filename, int *rows, int *columns, int *ship_count,struct SHIP allShips[100], int *attack_count, struct ATTACK allAttacks[1000]) {
    printf("Reading Save Game File\n");
    FILE *input = fopen(filename, "r");
    if(!input){
        printf("INPUT File open failed\n");
        exit(1);
    }
    
    // skip the board size line
    char skip_this_text[1000];
    if (!fgets(skip_this_text, 1000, input)) {
        printf("Error reading board size");
        exit(1);}

    // read the board size
    fscanf(input, "%d", rows);
    fscanf(input, "%d", columns);
    fgets(skip_this_text, 1000, input); // read the newline character
    printf("Board Size = (%d, %d)\n",*rows, *columns);

    // read the number of ships
    fgets(skip_this_text, 1000, input); //skip the number of ships line
    fscanf(input, "%d", ship_count);
    printf("Number of Ships = %d\n",*ship_count);

    // read the ship details
    char direction[10];
    if (*ship_count == 0){
        fgets(skip_this_text, 1000, input); //skip the number of ships line
    }
    for(int i = 0; i < *ship_count; i = i + 1){//loop for all ships
        fscanf(input, "%d", &allShips[i].row);
        fscanf(input, "%d", &allShips[i].column);
        fscanf(input, "%d", &allShips[i].length);
        fgets(direction, 10, input);
        allShips[i].direction = direction[1];
        printf("Ship %d: (%d, %d), length = %d, direction %c\n",i, allShips[i].row, allShips[i].column, allShips[i].length, allShips[i].direction);
    }
    //read the number of attacks
    fgets(skip_this_text, 1000, input); //skip the number of attacks line
    fscanf(input, "%d", attack_count);//gets the 
    printf("Number of Attacks = %d\n",*attack_count);   
    
    //read the attacks 
    for (int i = 0; i < *attack_count; i = i + 1){//loop for all attacks
        fscanf(input, "%d", &allAttacks[i].row);//gets rows
        fscanf(input, "%d", &allAttacks[i].column);//gets columns 
        printf("Attack %d: (%d, %d)\n", i, allAttacks[i].row, allAttacks[i].column);
    }
    // adding a space
    printf("\n");
  
    fclose(input);//closes the read
}

//creates the array for the board and stores it on the heap with malloc; rrows and columns to find the size of the board, the board pointer so we can change it; no return
void Initialize_Board(int rows, int columns, char **board){
    printf("Initializing Board\n");
    int size = (rows*columns);//gets the sizze of board
    *board = (char *)malloc(sizeof(char)*(size));//adds a . for size of board
    char *dptr = *board;//creates pointer
    for(int i=0; i < size; i++) {//loop for size of board
        *dptr ='.';
        dptr++;//index
    }
}

//prints out the board out; rows and columns for size, board pointer to print from it; no return
void Print_Board(int rows, int columns, char *board){
     char *dptr = board;//creates pointer to board
     for(int i=0; i < rows; i++) {//loop for rows of baord
        for(int j = 0; j < columns; j++){//loop for columns of board 
            printf("%c",*dptr);
            dptr++;//index
        }
        printf("\n");//next row
    }
    printf("\n");//foramting 
}

//checks that ships are valid and adds them if they are, if not prints out error; rows and columsn to find the size, board pointer to change it, ship count and array of ships to add them to the baord; no return 
void Add_Ships(int rows, int columns, char *board, int ship_count, struct SHIP allShips[100]){
    printf("Adding Ships\n");
    for(int i = 0; i < ship_count; i++){//loop for all ships
        int check = 0;//flag variable
        if(allShips[i].direction == 'V'){//if the ship is vertical 
            if(allShips[i].row + allShips[i].length > rows || allShips[i].column >= columns || allShips[i].row < 0 || allShips[i].column < 0 || allShips[i].row >= rows ){//makes sure boat is in bounds
                printf("Ship %d is out of bounds - skipping\n", i);
            }
            else{
                char *dptr = board;
                dptr = dptr + (allShips[i].row * columns) + allShips[i].column;//index to spot on board
                for(int j = 0; j < allShips[i].length; j++){//loop for length of ships
                    if(*dptr == 'S'){//checks if part of ship is on this board spot
                        check = 1;//if it is make flag = 1
                    }
                    dptr = dptr + columns;//index   
                }
                if(check == 1){//if flag is 1
                    printf("Ship %d overlaps another ship - skipping\n", i);
                }
                else{//add ship
                    char *dptr = board;
                    dptr = dptr + (allShips[i].row * columns) + allShips[i].column;//index to location on board
                    for(int j = 0; j < allShips[i].length; j++){//loop for ship length
                        *dptr = 'S';//add part of ship
                        dptr = dptr + columns;//index 
                    }
                }
            }
        }
        else{//if ship is horizontal 
            if(allShips[i].row >= rows || allShips[i].column + allShips[i].length > columns || allShips[i].row < 0 || allShips[i].column < 0 || allShips[i].column >= columns){//checks if boat is in bounds
                printf("Ship %d is out of bounds - skipping\n", i);
            }
            else{
                char *dptr = board;
                dptr = dptr + (allShips[i].row * columns) + allShips[i].column;//index to spot on board
                for(int j = 0; j < allShips[i].length; j++){//for length of board
                    if(*dptr == 'S'){//check is ship is rpesent
                        check = 1;//change flag to 1
                    }
                    dptr++;//index 
                }
                if(check == 1){//if flag is 1
                    printf("Ship %d overlaps another ship - skipping\n", i);
                }
                else{//add ship
                    char *dptr = board;
                    dptr = dptr + (allShips[i].row * columns) + allShips[i].column;//index to spot on board
                    for(int j = 0; j < allShips[i].length; j++){//for lengrth of ship
                        *dptr = 'S';//add ship
                        dptr++;//index 
                    }
                }
            }
        }
    }       
}

//adds all attacks to the board if they are valid; rows and columns for size, board pointer to chagne it, attack count and array of attacks to add to board; no return
void Process_Attacks(int rows, int columns, char *board, int attack_count,struct ATTACK allAttacks[1000]){
    printf("Processing Attacks\n");
    char *dptr = board;//pointer to board
    for(int i = 0; i < attack_count; i++){//for all attakcs 
        if (allAttacks[i].row > rows || allAttacks[i].column > columns || allAttacks[i].row < 0 || allAttacks[i].column < 0){//checks if valid attack
            printf("Attack %d is out of bounds - skipping\n", i);
        }
        else{
            for(int j = 0; j < (allAttacks[i].row * columns + allAttacks[i].column); j++){//index the pointer to attack location
                dptr++;
            }   
            if (*dptr == 'S' || *dptr == 'H'){//if ship, mark as hit
                *dptr = 'H';
            }
            else{
                *dptr = 'M';//else mark as a miss
            }
            for(int k = (allAttacks[i].row * columns + allAttacks[i].column); k > 0; k--){//index back to (0,0)
                dptr--;
            }
        }
    }
}

//checks the board for an S chars, if one is left the loop breaks and prints the statement; rows and columns for board size. board to acces it and check it; no return
void Game_Over(int rows, int columns, char *board){
    char *dptr = board;//pointer for board
    int check = 0;//flag variable for is ship is left 
    int size = (rows*columns);//size of board
    for(int i=0; i < size; i++){//loop for size of baord
        if(*dptr == 'S'){//if a ship is left
            printf("Ships remain afloat - game on\n");
            check = -1;
            break;    
        }
        dptr++;//index 
    }
    if(check != -1){//if the flag vairable does  not matche
        printf("All ships have been sunk - game over\n");
    }   
}

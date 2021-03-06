/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct coords{
    int x;
    int y;
};

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int);
bool won(void);
struct coords get_coords(int);
void swap_tiles(struct coords, struct coords);
bool is_near(struct coords, struct coords);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        } else {
            
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    
    int num = d*d-1;
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            board[i][j] = num;
            num--;
        }
    }
    if(d % 2 == 0){
        swap_tiles(get_coords(1), get_coords(2));
    }
}
/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for ( int i = 0; i < d; i++ ){
        for ( int j = 0; j < d; j++ ){
            printf("%i ",board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile_to_check)
{
    struct coords tile = get_coords(tile_to_check);
    struct coords empty_tile = get_coords(0);
    
    if(is_near(tile, empty_tile)){
        swap_tiles(tile, empty_tile);
        return true;   
    }
    return false;
}
/**
 * returns true if one tile borders the second
 */
bool is_near(struct coords first_tile, struct coords second_tile){
    if(abs((first_tile.x+first_tile.y)-(second_tile.x+second_tile.y)) == 1){
        if(abs(first_tile.x-second_tile.x) < 2 && abs(first_tile.y-second_tile.y) < 2){
            return true;
        }
    }
    return false;
}
/**
 * returns structure with x and y int coordinates of tile
 */
struct coords get_coords(int tile){
    struct coords coords;
    for(int i = 0; i < d; i++){
        for(int j =0; j < d; j++){
            if(board[i][j] == tile){
                coords.x = i;
                coords.y = j;
                return coords;
            }
        }
    }
    return coords;
}
/**
 * swap to elemetns in array by their coordinates
 */
void swap_tiles(struct coords first_tile, struct coords second_tile){
    int temp = board[first_tile.x][first_tile.y];
    board[first_tile.x][first_tile.y] = board[second_tile.x][second_tile.y];
    board[second_tile.x][second_tile.y] = temp; 
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int num = 1;
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            if (num == (d*d) && board[i][j] == 0){
                return true;
            }
            if(board[i][j] != num){
                return false;
            }
            num++;
        }
    }
    return true;
}
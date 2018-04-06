#include <stdio.h>

int checkForWinner( char*, int, char* );
void drawGrid( char a[] );
void takeTurn( char*, char* );
void swapPlayer( char* );
int findMove(char*);
int winner( char, int, char*);

//Patrick Bruce's Code
int AI(char*, char );
char winnerAI(char*);
int moveEval(char*, char);
void drawGrid( char a[]);
void printOutComes(int a[], int b[], int);
int frees( char board[]);
void freesLocations(int*, char*);

int main(){
    char grid[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9' };
    char currentPlayer = 'O';
    int counter = 0, done = 0;
    
    drawGrid( grid );
    
    while( done == 0 ){
        takeTurn( grid, &currentPlayer );
        drawGrid( grid );
        done = checkForWinner( grid, counter, &currentPlayer );
        swapPlayer( &currentPlayer );
        counter++;
    }
}


/** swapPlayer
 Swaps current player from 'X' to 'O' and vice-versa **/

void swapPlayer( char *playerPtr ){
    
    if( *playerPtr == 'X' )
        *playerPtr = 'O';
    else
        *playerPtr = 'X';
}

/**  checkForWinner
 Checks to see if there is a winner    **/
int checkForWinner( char a[], int cnt, char* playerPtr  ){
    
    int i, gameOver = 0;
    
    for( i = 0; i < 3; i++ ){
        if( a[3*i] == a[3*i + 1] && a[3*i + 1] == a[3*i + 2]){
            printf( "We have a winner! It is %c.\n\n", *playerPtr );
            gameOver = 1;
        }
        
        if( a[i] == a[i + 3] && a[i + 3] == a[i + 6]){
            printf( "Game over, man! %c dominates.\n\n", *playerPtr );
            gameOver = 1;
        }
    }
    
    if( a[0] == a[4] && a[4] == a[8]){
        printf( "%c wins on a diagonal move!\n\n", *playerPtr );
        gameOver = 1;
    }
    
    if( a[2] == a[4] && a[4] == a[6]){
        printf( "That's it. %c has prevailed!\n\n", *playerPtr );
        gameOver = 1;
    }
    
    if( cnt == 8  && gameOver == 0 ){
        printf( "Awww. It's a cat's game.\n\n" );
        gameOver = 1;
    }
    
    return gameOver;
}

/**  takeTurn
 Tells the current player the available moves and enters the choice **/

void takeTurn( char a[], char *playerPtr  ){
    
    
    int available[9];
    int i, j = 0, choice = -1, legalMove = 0;
    
    for(i = 0; i < 9; i++ )
        if( (a[i] != 'X') && (a[i] != 'O')  )
            available[ j++ ] = i;
    
    while(!legalMove)
        {
        choice = -1;
        printf( "\nIt is %c's turn.  Choose your move (", *playerPtr );
        for( i = 0; i < j; i++ )
            printf( " %d", available[i]);
        
        printf( " ): ");
        if(*playerPtr == 'X')
            {
            scanf( "%d", &choice);
            choice = choice -1;
            }
        else
            choice = AI(a, *playerPtr);
        
        for(int x = 0;( x < sizeof(available)/4) && (!legalMove); x++)
            if( available[x] == choice)
                legalMove = 1;
        }
    
    if( *playerPtr == 'X' )
        a[ choice ] = 'X';
    else
        a[ choice ] = 'O';
}

/**  drawGrid
 Draws the current state of the tic-tac-toe grid    **/

void drawGrid( char a[] ){
    
    printf( "\n" );
    printf( " %c | %c | %c \n", a[0], a[1], a[2] );
    printf( "---|---|---\n");
    printf( " %c | %c | %c \n", a[3], a[4], a[5] );
    printf( "---|---|---\n");
    printf( " %c | %c | %c \n", a[6], a[7], a[8] );
    printf("\n");
}

int AI(char board[], char player)
{
    
    char boardCopy[9];
    for( int i = 0; i < 9; i++)
        boardCopy[i] = board[i];
    int free;
    free = frees(boardCopy);
    int freeSpaces[free];
    freesLocations(freeSpaces, boardCopy);
    int outComes[free];
    drawGrid(board);
    
    for(int i = 0; i < free; i++)
        {
        for( int i = 0; i < 9; i++)
            boardCopy[i] = board[i];
        
        boardCopy[freeSpaces[i]] = 'O';
        player = 'X';
        outComes[i] = moveEval(boardCopy, player);
        }
    
    for( int i = 0; i < free; i++)
        if(outComes[i] == 10)
            return freeSpaces[i];
    for( int i = 0; i < free; i++)
        if(outComes[i] == 0)
            return freeSpaces[i];
    return freeSpaces[0];
}

int moveEval(char board[], char player)
{
    char boardCopy[9];
    for( int i = 0; i < 9; i++)
        boardCopy[i] = board[i];
    int free;
    free = frees(boardCopy);
    int freeSpaces[free];
    freesLocations(freeSpaces, boardCopy);
    int outComes[free];
    
    
    if(player == 'O')
        {
        for(int i = 0; i < free; i++)
            {
            for( int i = 0; i < 9; i++)
                boardCopy[i] = board[i];
            boardCopy[freeSpaces[i]] = 'O';
            
            if( winnerAI(boardCopy) == 'C')
                outComes[i] = 0;
            else if(winnerAI(boardCopy ) == 'X')
                outComes[i] = -10;
            else if( winnerAI(boardCopy) == 'O')
                return 10;
            else
                {
                player = 'X';
                outComes[i] = moveEval(boardCopy, player);
                }
            }
        for(int i = 0; i < free; i++)
            if( outComes[i] == 10)
                return 10;
        for(int i = 0; i < free; i++)
            if( outComes[i] == 0)
                return 0;
        for(int i = 0; i < free; i++)
            if( outComes[i] == -10)
                return -10;
        }
    else if(player == 'X')
        {
        for(int i = 0; i < free; i++)
            {
            for( int i = 0; i < 9; i++)
                boardCopy[i] = board[i];
            boardCopy[freeSpaces[i]] = 'X';
            if( winnerAI(boardCopy) == 'C')
                outComes[i] = 0;
            else if(winnerAI(boardCopy ) == 'X')
                return -10;
            else if( winnerAI(boardCopy) == 'O')
                outComes[i] = 10;
            else
                {
                player = 'O';
                outComes[i] = moveEval(boardCopy, player);
                }
            }
        for(int i = 0; i < free; i++)
            if( outComes[i] == -10)
                return -10;
        for(int i = 0; i < free; i++)
            if( outComes[i] == 0)
                return 0;
        for(int i = 0; i < free; i++)
            if( outComes[i] == 10)
                return 10;
        }
    drawGrid(board);
    drawGrid(boardCopy);
    printf("there was a problem\n");
    return 0;
}

char winnerAI(char board[])
{
    char victor = 'C';
    
    for( int i = 0; i < 3; i++ ){
        if( board[3*i] == board[3*i + 1] && board[3*i + 1] == board[3*i + 2]){
            victor = board[3*i];
            return victor;
        }
        
        if( board[i] == board[i + 3] && board[i + 3] == board[i + 6]){
            victor = board[i];
            return victor;
        }
    }
    if( board[0] == board[4] && board[4] == board[8]){
        victor = board[4];
        return victor;
    }
    
    else if( board[2] == board[4] && board[4] == board[6]){
        victor = board[4];
        return victor;
    }
    
    for( int i = 0; i < 9; i++)
        {
        if((board[i] != 'X') && (board[i] != 'O'))
            {
            victor = 'N';
            return victor;
            }
        }
    return victor;
}

void printOutComes( int a[], int b[], int free ){
    
    printf( "\n" );
    for(int i = 0; i < free; i++)
        {
        printf("%d: %d\n", b[i], a[i]);
        }
    printf("\n");
}

int frees(char board[])
{
    int free = 0;
    
    for( int i = 0; i < 9; i++)
        if((board[i] != 'X') && (board[i] != 'O'))
            free++;
    return free;
}

void freesLocations(int freeSpaces[], char board[])
{
    for( int i = 0; i < 9; i++)
        if((board[i] != 'X') && (board[i] != 'O'))
            *(freeSpaces++) = i;
    return;
}




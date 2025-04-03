#include <stdio.h> //input - output
#include <stdlib.h> // random library
#include <time.h> //        ''
#include <stdbool.h> // booleans
#include <SDL2/SDL.h> // implement game ticks with SDL_GetTicks()
#include <ncurses.h> // handle terminal UI


//constants

#define SIZEROWS 17
#define SIZECOLS 34 
#define MAXTALES (SIZEROWS-2)*(SIZECOLS-2)
#define GAMETICKS 100//[ms]
#define ESC '\x1b'

char movement = 'd'; // initial movement

typedef struct {
    int snake_body[MAXTALES][2];
    int snake_length;
} TSnake;

void printMap(char map[SIZEROWS][SIZECOLS], int apple_pos[2], TSnake snake){ // loop that prints the array map
    clear();
    for(int i = 0; i < SIZEROWS; i++){
        for(int j = 0; j < SIZECOLS; j++){
            
            if((apple_pos[0] == i) && (apple_pos[1] == j)){
                mvprintw(i, j, "%c", '@');
            } else{
                mvprintw(i, j, "%c", map[i][j]);
            }
            for(int k = 0; k < MAXTALES; k++){//check if tale coincides with snake body
                if((j == 0) && (i == 0) && (snake.snake_body[k][0] == 0) && (snake.snake_body[k][1] == 0)){
                    
                }
                else if((snake.snake_body[k][0] == i) && (snake.snake_body[k][1] == j)){
                    mvprintw(i, j, "%c", 'H');
                }
            } 
        }
    }
    refresh();
}

void generateApplePosition(int apple_position[2]){

    apple_position[0] = 1 + rand() % (SIZEROWS - 2);
    apple_position[1] = 1 + rand() % (SIZECOLS - 2);

}

void snakeMovement(TSnake * snake, int apple_pos[2]){

    int tail_old_row;
    int tail_old_col;

    for(int i = snake->snake_length; i > 0; i--){ //iterate through all the positions of the body
        if(i == snake->snake_length){// when moving each part of the body (first case), save the tail in an external variable in case that the snake needs to grow
            tail_old_row = snake->snake_body[i][0];
            tail_old_col = snake->snake_body[i][1];
        } else{ //set the ith part of the body position to the position of the i-1th body part
            snake->snake_body[i][0] = snake->snake_body[i - 1][0];
            snake->snake_body[i][1] = snake->snake_body[i - 1][1];
        }
    }

    switch(movement){
        case 'w':
            if(((snake->snake_body[0][0] - 1) == (apple_pos[0])) && ((snake->snake_body[0][1]) == (apple_pos[1]))){ //if the next movement coincides with the position of an apple, add a new piece of snake in the position of the old tail that was saved
                snake->snake_body[snake->snake_length + 1][0] = tail_old_row;
                snake->snake_body[snake->snake_length + 1][1] = tail_old_col;
                snake->snake_length +=1;
                generateApplePosition(apple_pos); //generate new apple
            }
            snake->snake_body[0][0] -= 1;
            break;

        case 'a':
            if(((snake->snake_body[0][0]) == (apple_pos[0])) && ((snake->snake_body[0][1] - 1) == (apple_pos[1]))){
                snake->snake_body[snake->snake_length + 1][0] = tail_old_row;
                snake->snake_body[snake->snake_length + 1][1] = tail_old_col;
                snake->snake_length +=1;
                generateApplePosition(apple_pos);
            }
            snake->snake_body[0][1] -= 1;
            break;

        case 's':
            if(((snake->snake_body[0][0] + 1) == (apple_pos[0])) && ((snake->snake_body[0][1]) == (apple_pos[1]))){
                snake->snake_body[snake->snake_length + 1][0] = tail_old_row;
                snake->snake_body[snake->snake_length + 1][1] = tail_old_col;
                snake->snake_length +=1;
                generateApplePosition(apple_pos);
            }
            snake->snake_body[0][0] += 1;
            break;

        case 'd':
            if(((snake->snake_body[0][0]) == (apple_pos[0])) && ((snake->snake_body[0][1] + 1) == (apple_pos[1]))){
                snake->snake_body[snake->snake_length + 1][0] = tail_old_row;
                snake->snake_body[snake->snake_length + 1][1] = tail_old_col;
                snake->snake_length +=1;
                generateApplePosition(apple_pos);
            }
            snake->snake_body[0][1] += 1;
            break;
    }
}

bool movementIsColision(TSnake snake, char map[SIZEROWS][SIZECOLS]){
    for(int i=snake.snake_length - 1; i > 0; i--){

        switch(movement){
            case 'w':
                if((map[snake.snake_body[0][0] - 1][snake.snake_body[0][1]] == '#') || 
                   (((snake.snake_body[0][0] - 1) == snake.snake_body[i][0]) && (snake.snake_body[0][1] == snake.snake_body[i][1]))){
                    return true;
                } //if the position on the map where the snake is gonna move is a wall or is any of the parts of the body, the movement is not valid
                break;
            case 's':
                if((map[snake.snake_body[0][0] + 1][snake.snake_body[0][1]] == '#') || 
                   (((snake.snake_body[0][0] + 1) == snake.snake_body[i][0]) && (snake.snake_body[0][1] == snake.snake_body[i][1]))){
                    return true;
                }
                break;
            case 'a':
                if((map[snake.snake_body[0][0]][snake.snake_body[0][1] - 1] == '#') || 
                   (((snake.snake_body[0][0]) == snake.snake_body[i][0]) && ((snake.snake_body[0][1] - 1) == snake.snake_body[i][1]))){
                    return true;
                }
                break;
            case 'd':
                if((map[snake.snake_body[0][0]][snake.snake_body[0][1] + 1] == '#') ||
                   (((snake.snake_body[0][0]) == snake.snake_body[i][0]) && ((snake.snake_body[0][1] + 1) == snake.snake_body[i][1]))){
                    return true;
                }
                break;
            
        }
    }
    return false;
}

int main(){
    srand(time(NULL));

    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);  // Enable special keys (arrows)
    curs_set(FALSE);       // Hide the cursor
    nodelay(stdscr, TRUE); // Don't block execution on input


    //the snake body info. is saved by a matrix (included in the Tsnake struct) that saves every body part in each row. Index 0 is the head and the snake length marks the tail. It will start with 1 part and can be up to the whole map
    TSnake snake = {0};
    
    for(int i = 0; i < 3; i++){ //initial body 
        snake.snake_body[i][0] = SIZEROWS/2;
        snake.snake_body[i][1] = SIZECOLS/4 - i;
        snake.snake_length +=1; 
    }

    //generate apple position
    int apple_position[2] = {(int) SIZEROWS/2,(int) (SIZECOLS/2 + SIZECOLS/4)}; 

    
    char map[SIZEROWS][SIZECOLS]= {{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};

    Uint32 tick_last = SDL_GetTicks();
    
    bool quit = false;
    bool snake_is_dead = false;

    while(!quit && !snake_is_dead){
        Uint32 tick_current = SDL_GetTicks();
        Uint32 elapsed_time = tick_current - tick_last;

        int input = getch();

        if(input != ERR){
            switch (input)  
            {
            case 'w':
                if(movement != 's'){
                    movement = 'w';
                }
                break;
            case 'a':
                if(movement != 'd'){
                    movement = 'a';
                }
                break;
            case 's':
                if(movement != 'w'){
                    movement = 's';
                }
                break;
            case 'd':
                if(movement != 'a'){
                    movement = 'd';
                }
                break;
            case ESC:
                quit = true;
                break;
            default:
                break;
            }
        }

        if(elapsed_time >= GAMETICKS){
            tick_last = SDL_GetTicks();
            if(movementIsColision(snake, map)){
                snake_is_dead = true;
            } else{
                snakeMovement(&snake, apple_position);
                printMap(map, apple_position, snake);
            }
        }
    }
    endwin();
    return 0;
}

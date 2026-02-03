#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "screen.h"
#include "snake.h"

#define DELAY 200

#ifdef _WIN32
  #include <windows.h>
  #define clear "cls"
    void wait_ms(long milliseconds){
      sleep(milliseconds)
    }
#else
  #define CLEAR "clear"
  void wait_ms(long milliseconds){
    struct timespec req;
    req.tv_sec = milliseconds/1000;
    req.tv_nsec = (milliseconds%1000)*1000000L;
    nanosleep(&req,NULL);
  }
#endif

void gameOver(Snake* snake,ScreenPosition apple){
  system(CLEAR);
  printScreen(snake,apple,GAME_OVER);
  printf("%s=======GAME OVER=======%s\n",CRED,END_COLOR);
  printf("SCORE: %d\n", snake->size-2);
}

void startMenu(int* delay){
  printf("!!!!WELCOME TO THE SNAKE GAME!!!!\n");
  printf("Controls: \nWASD to control the snake \nq to quit\n\n");
  int difficulty;
  printf("Choose the difficulty: 1-easy, 2-normal, 3-hard\n");
  do{
    scanf(" %d",&difficulty);
  }while(difficulty<1 || difficulty>3);

  switch(difficulty){
    case 1: *delay = 250; break;
    case 2: *delay = 200; break;
    case 3: *delay = 150;
  }

  printf("Press any key to start\n");
  setbuf(stdin,NULL);
  getchar();
}

void receive_movement(char movement, Snake* snake){
      switch(movement){
        case 'w':
        case 'W':
          if(snake->head->direction!=DOWN) moveSnake(snake,UP);
          else moveSnake(snake,NO_DIRECTION);
          break;
        case 'A':
        case 'a':
          if(snake->head->direction!=RIGHT) moveSnake(snake,LEFT);
          else moveSnake(snake,NO_DIRECTION);
          break;
        case 's':
        case 'S':
          if(snake->head->direction!=UP) moveSnake(snake,DOWN);
          else moveSnake(snake,NO_DIRECTION);
          break;
        case 'd':
        case 'D':
          if(snake->head->direction!=LEFT) moveSnake(snake,RIGHT);
          else moveSnake(snake,NO_DIRECTION);
          break;
        case 'q':
        case 'Q':
          exit(0);
      }
}

int main(){
  srand(time(NULL));
  Snake* snake = initSnake();
  char movement;
  ScreenPosition apple;
  int delay;

  startMenu(&delay);
  newApple(snake,&apple);
  while(1){
    system(CLEAR);
    printScreen(snake,apple,IN_GAME);
    if(kbhit(&movement)){
      receive_movement(movement,snake);
    }
    else
      moveSnake(snake,NO_DIRECTION);
    
    if(snake->size==COLUMS*LINES){
      system(CLEAR);
      printScreen(snake,apple,PLAYER_WIN);
      printf("I don't know how, but you won. CONGRADULATIONS!!\n");
      return 0;
    }
    if(snake->head->line<0 || snake->head->line==LINES ||
        snake->head->colum<0 || snake->head->colum==COLUMS ||
        snakeInPosition(snake->head->line, snake->head->colum, snake)==TAIL){
      gameOver(snake,apple);
      return 0;
    }

    if(snake->head->line==apple.line && snake->head->colum==apple.colum){
      growTail(snake);
      newApple(snake,&apple);
    }
    printf("WASD to move         q to quit\n");
    wait_ms(delay);
  }
}

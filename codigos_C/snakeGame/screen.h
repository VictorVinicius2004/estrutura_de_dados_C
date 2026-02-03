#ifndef SCREEN_H
#define SCREEN_H

#include <stdlib.h>
#include "gconio.h"
#include "common.h"

SnakePart snakeInPosition(int line, int colum, Snake* snake){
  Part* tail = snake->tail;
  while(tail){
    if(tail->line==line && tail->colum==colum){
      if(tail->part==HEAD) return HEAD;
      return TAIL;
    }
    tail = tail->prev;
  }
  return NONE;
}

void newApple(Snake* snake, ScreenPosition* apple){
  ScreenPosition freePositions[LINES*COLUMS-snake->size];
  int cont = 0;
  for(int i=0; i<LINES; i++){
    for(int j=0; j<COLUMS; j++){
      if(snakeInPosition(i,j,snake)==NONE){
        freePositions[cont].line = i;
        freePositions[cont].colum = j;
        cont++;
      }
    }
  }

  int applePosition = rand()%cont;
  *apple = freePositions[applePosition];
}

void printScreen(Snake* snake, ScreenPosition apple, GameState gameStage){
  const char* boardColor = (gameStage==IN_GAME)? CPURPLE :
  (gameStage==GAME_OVER)? CRED : CGREEN;

  for(int i=-1; i<=LINES; i++){
    for(int j=-1; j<=COLUMS; j++){
      if((i<0 || i==LINES) && (j<0 || j==COLUMS))
        printf("%s#%s",boardColor,END_COLOR);
      else if(i<0 || i==LINES)
        printf("%s##%s",boardColor,END_COLOR);
      else if(j<0 || j==COLUMS)
        printf("%s#%s",boardColor,END_COLOR);
      else{
        printf(" ");
        if(i==apple.line && j==apple.colum)
          printf("%sO%s",CRED,END_COLOR);
        else{
          printf("%s",CGREEN);
          switch(snakeInPosition(i,j,snake)){
            case HEAD: printf("@%s",END_COLOR); break;
            case TAIL: printf("O%s",END_COLOR); break;
            case NONE: printf("%s#",END_COLOR);
          }
        }
      }
    }
    printf("\n");
  }
}

#endif

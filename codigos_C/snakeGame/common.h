#ifndef COMMON_H
#define COMMON_H

#define LINES 15
#define COLUMS 20

#define CRED "\033[31m"
#define CGREEN "\033[32m"
#define CPURPLE "\033[35m"
#define END_COLOR "\033[0m"

typedef enum{
  IN_GAME,
  GAME_OVER,
  PLAYER_WIN
}GameState;

typedef enum{
  NONE,
  HEAD,
  TAIL,
}SnakePart;

typedef enum{
  UP,
  DOWN,
  RIGHT,
  LEFT,
  NO_DIRECTION,
}Directions;

typedef struct Part{
  SnakePart part;
  Directions direction;
  int line;
  int colum;
  int prevLine;
  int prevColum;
  struct Part* next;
  struct Part* prev;
}Part;

typedef struct Snake{
  Part* head;
  Part* tail;
  int size;
}Snake;

typedef struct ScreenPosition{
  int line, colum;
}ScreenPosition;

#endif

#ifndef MENU_H
#define MENU_H 

typedef struct _win_st WINDOW;

int menu(WINDOW *win);

int movepointer (WINDOW *win, int currPos, int maxVal, int minVal);

#endif

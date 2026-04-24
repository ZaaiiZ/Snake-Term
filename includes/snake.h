#ifndef SNAKE_H
#define SNAKE_H

/*
  SYS INCLUDES
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>

/*
  GLOBAL VARIABLES & FUNCTIONS
*/
#define FRAMEBUF_SIZE 8192
char framebuf[FRAMEBUF_SIZE];
int framelen;
int	offsetX, offsetY;
#define fb_printf(...) \
	framelen += snprintf(framebuf + framelen, \
						 FRAMEBUF_SIZE - framelen, __VA_ARGS__)
#define TX 20
#define TY 20
#define BG_WHITE 47
#define BG_YELLOW 43
#define BG_GREEN 42
#define BG_RED 41
#define GREEN 32
#define RED 31
#define RESET 0

/*
  GAME STRUCTURES
*/
//Valeur :  NORD (0), EST (1), SUD (2), OUEST (3)
typedef enum { NORD, EST, SUD, OUEST } direction;

typedef struct s_snake
{
	unsigned int	x;
	unsigned int	y;
	direction 		dir;
	struct s_snake	*next;
}					t_snake;

typedef struct s_apple
{
	unsigned int	x;
	unsigned int	y;
}					t_apple;

/*
  GAME FUNCTIONS
*/

/*
  TERMIOS
*/
void	set_raw_mode(void);
void	set_normal_mode(void);
char	ft_getch(void);
int		ft_kbhit(void);
/*
  UTILS
*/
void	gotoXY(int x, int y);
void	textColor(int color);
long	getTimeMs(void);
void	drawCell(int x, int y, int color);
void	drawCellChar(int x, int y, int color, char *str);
void	getTerminalSize(int *cols, int *rows);
/*
  RENDER
*/
void	printBanner(int termWidth);
void	printApple(t_apple apple);
void	printSnake(t_snake *snake);
void	printScore(int score);
void	printGameOver(void);
void	printBorder(void);
/*
  SNAKE
*/
t_snake	*getHead(t_snake *snake);
t_apple	initApple(t_snake *snake);
t_snake	*initSnake(void);
int		isOnSnake(t_snake *snake, int x, int y);
void	mooveSnake(t_snake **snake, t_snake **head);
int		collisionSnakeApple(t_snake *snake, t_apple apple);
int		isCollisionSnakeBorder(t_snake *snake);
int		collisionHeadTail(t_snake *snake, t_snake *head);
void	addLengthSnake(t_snake **snake);

#endif

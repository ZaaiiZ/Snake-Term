#include "snake.h"

void	gotoXY(int x, int y)
{
	fb_printf("\033[%d;%dH", y, x);
}

void	textColor(int color)
{
	fb_printf("\033[%dm", color);
}

void	drawCell(int x, int y, int color)
{
	fb_printf("\033[%d;%dH\033[%dm  ", offsetY + y, offsetX + x * 2, color);
}

void	drawCellChar(int x, int y, int color, char *str)
{
	fb_printf("\033[%d;%dH\033[%dm%s", offsetY + y, offsetX + x * 2, color, str);
}

long	getTimeMs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void getTerminalSize(int *cols, int *rows)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *cols = w.ws_col;
    *rows = w.ws_row;
}

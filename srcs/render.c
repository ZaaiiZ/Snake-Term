#include "snake.h"

void printBanner(int termWidth)
{
    const char *banner[] = {
        "███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗",
        "██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝",
        "███████╗██╔██╗ ██║███████║█████╔╝ █████╗",
        "╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝",
        "███████║██║ ╚████║██║  ██║██║  ██╗███████╗",
        "╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝",
        "",
        "            ██████╗ ██╗   ██╗     █████╗ ██████╗ ",
        "            ██╔══██╗╚██╗ ██╔╝    ██╔══██╗██╔══██╗",
        "            ██████╔╝ ╚████╔╝     ███████║██║  ██║",
        "            ██╔══██╗  ╚██╔╝      ██╔══██║██║  ██║",
        "            ██████╔╝   ██║       ██║  ██║██████╔╝",
        "            ╚═════╝    ╚═╝       ╚═╝  ╚═╝╚═════╝ "
    };

    int height = 13;
	int	maxLen=0;
	int	len;
	int x;
	int	i=0;

	while (i < height)
	{
		len = strlen(banner[i]);
		if (len > maxLen)
			maxLen = len;
		i++;
	}
	i=0;
	while (i < height)
	{
		x=0;
		if (termWidth > maxLen)
			x = (termWidth - maxLen) / 2;
		gotoXY(x, i + 1);
		fb_printf("%s", banner[i]);
		i++;
	}
}

void	printApple(t_apple apple)
{
	drawCellChar(apple.x, apple.y, RESET, "🍎");
}

void	printSnake(t_snake *snake)
{
	while (snake->next != NULL)
	{
		drawCellChar(snake->x, snake->y, BG_GREEN, "  ");
		snake = snake->next;
	}
	drawCellChar(snake->x, snake->y, BG_GREEN, "  ");
}

void	printScore(int score)
{
	int x = offsetX + (TX * 2) + 10;
	int y = offsetY + 3;

	gotoXY(x, y);
	textColor(RESET);
	textColor(GREEN);
	fb_printf("SCORE : %d  ", score);
	textColor(RESET);
}

void printGameOver(void)
{
	framelen = 0;
    textColor(RESET);
    textColor(GREEN);

    int x = offsetX + (TX * 2) / 2 - 5;
    int y = offsetY + (TY / 2);

    gotoXY(x + 2, y);
    fb_printf("┌─────────────┐");

    gotoXY(x + 2, y + 1);
    fb_printf("   GAME OVER   ");

    gotoXY(x + 2, y + 2);
    fb_printf("└─────────────┘\n\n\n\n\n\n\n\n\n\n\n\n\n");
	write(STDOUT_FILENO, framebuf, framelen);
}

void	printBorder(void)
{
	int	i=1;

	while (i < TX + 3)
	{
		drawCell(i, 1, BG_WHITE);
		i++;
	}
	i = 1;
	while (i < TY + 3)
	{
		drawCell(TX + 2, i, BG_WHITE);
		i++;
	}
	i = TX + 2;
	while (i > 0)
	{
		drawCell(i, TY + 2, BG_WHITE);
		i--;
	}
	i = TY + 2;
	while (i > 0)
	{
		drawCell(1, i, BG_WHITE);
		i--;
	}
}

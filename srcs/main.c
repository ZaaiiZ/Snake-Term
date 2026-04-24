#include "snake.h"

int	main(void)
{
	/*
	  Variables
	*/
	int				fin = 0;
	long			lastTick;
	long			now;
	int				tickMs = 100; //Vitesse du jeu
	char			key;
	int				score=0;
	t_snake			*snake;
	t_apple			apple;
	t_snake			*head;
	int				termW, termH;
	getTerminalSize(&termW, &termH);
	offsetY = 15;
	offsetX = (termW - (TX * 2)) / 2;

	/*
	  Initialisation du jeu
	*/
	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));
	set_raw_mode();
	snake = initSnake();
	apple = initApple(snake);
	head = getHead(snake);
	lastTick = getTimeMs();
	framelen = 0;
	fb_printf("\033[?25l");
	printBanner(termW);
	printBorder();
	printApple(apple);
	printScore(score);
	printSnake(snake);
	write(STDOUT_FILENO, framebuf, framelen);
	
	/*
	  Boucle du jeu : Calcul chaque seconde
	*/
	while (!fin)
	{
		now = getTimeMs();

		//Commandes clavier
		if (ft_kbhit())
		{
			key = ft_getch();
			//Quitter (q)
			if (key == 'q')
			{
				printGameOver();
				fin = 1;
				break ;
			}
			//Pause (ESP)
			if ((int)key == 32)
				getchar();
			//Direction Nord
			if (key == 'U')
				if (! (head->dir == SUD))
					head->dir = NORD;
			//Direction EST 
			if (key == 'R')
				if (! (head->dir == OUEST))
					head->dir = EST;
			//Direction SUD
			if (key == 'D')
				if (! (head->dir == NORD))
					head->dir = SUD;
			//Direction OUEST
			if (key == 'L')
				if (! (head->dir == EST))
					head->dir = OUEST;
		}

		if (now - lastTick >= tickMs)
		{
			lastTick = now;
			framelen = 0;

			mooveSnake(&snake, &head);

			if (isCollisionSnakeBorder(head) || collisionHeadTail(snake, head))
			{
				printGameOver();
				write(STDOUT_FILENO, framebuf, framelen);
				fin = 1;
				break;
			}
			if (collisionSnakeApple(head, apple))
			{
				score += 1;
				drawCell(apple.x, apple.y, RESET);
				apple = initApple(snake);
				addLengthSnake(&snake);
				printScore(score);
				printApple(apple);
				printSnake(snake);
			}
			write(STDOUT_FILENO, framebuf, framelen);
		}
		usleep(1000);
	}

	/*
	  Terminaison du jeu
	*/
	framelen = 0;
	textColor(RESET);
	fb_printf("\033[?25h");
	write(STDOUT_FILENO, framebuf, framelen);
	set_normal_mode();
}

#include "snake.h"

t_snake	*getHead(t_snake *snake)
{
	while (snake->next != NULL)
		snake = snake->next;
	return (snake);
}

t_apple	initApple(t_snake *snake)
{
	t_apple	apple;

	do
	{
		apple.x = 4 + rand() % (TX - 6);
		apple.y = 4 + rand() % (TY - 6);
	} 	while (isOnSnake(snake, apple.x, apple.y) == 1);
	return (apple);
}

t_snake	*initSnake(void)
{
	t_snake	*snake;

	snake = malloc(sizeof(t_snake));
	snake->x = TX / 2;
	snake->y = TY / 2;
	snake->dir = rand() % 4;
	snake->next = NULL;
	addLengthSnake(&snake);
	addLengthSnake(&snake);
	return (snake);
}

int	isOnSnake(t_snake *snake, int x, int y)
{
	while (snake != NULL)
	{
		if (snake->x == (unsigned int)x && snake->y == (unsigned int)y)
			return (1);
		snake = snake->next;
	}
	return (0);
}

void	mooveSnake(t_snake **snake, t_snake **head)
{
	t_snake	*newHead;
	t_snake	*oldTail;

	//Cree la nouvelle Head
	newHead = (t_snake *)malloc(sizeof(*newHead));
	if (newHead == NULL)
		return;

	//Initialise la nouvelle Head
	newHead->x = (*head)->x;
	newHead->y = (*head)->y;
	newHead->dir = (*head)->dir;
	newHead->next = NULL;

	//Moove la nouvelle Head
	switch (newHead->dir)
	{
	case NORD:
		newHead->y -= 1;
		break;
	case EST:
		newHead->x += 1;
		break;
	case SUD:
		newHead->y += 1;
		break;
	case OUEST:
		newHead->x -= 1;
		break;
	}

	//chaine : ancienne Head pointe vers nouvelle Head
	(*head)->next = newHead;

	//Met a jour le pointeur Head
	*head = newHead;

	//Affiche la nouvelle Head
	drawCellChar(newHead->x, newHead->y, BG_GREEN, "  ");

	//Supprime l'ancienne Tail et libere le pointeur
	oldTail = *snake;
	drawCell((*snake)->x, (*snake)->y, RESET);
	*snake = oldTail->next;
	free(oldTail);
}

int	collisionSnakeApple(t_snake *snake, t_apple apple)
{
	if (snake->x == apple.x && snake->y== apple.y)
		return (1);
	return (0);
}

int	isCollisionSnakeBorder(t_snake *snake)
{
	if (snake->x == 1 || snake->x == TX + 2 ||
		snake->y == 1 || snake->y == TY + 2)
		return (1);
	return (0);
}

int	collisionHeadTail(t_snake *snake, t_snake *head)
{
	while (snake->next != NULL)
	{
		if (snake->x == head->x && snake->y == head->y)
			return (1);
		snake = snake->next;
	}
	return (0);
}

void	addLengthSnake(t_snake **snake)
{
	t_snake *new;

	new = malloc(sizeof(t_snake));
	if (new == NULL)
		return;
	new->next = *snake;
	new->dir = (*snake)->dir;
	switch ((*snake)->dir)
	{
	case NORD:
		new->x = (*snake)->x;
		new->y = (*snake)->y + 1;
		break;
	case EST:
		new->x = (*snake)->x - 1;
		new->y = (*snake)->y;
		break;
	case SUD:
		new->x = (*snake)->x;
		new->y = (*snake)->y - 1;
		break;
	case OUEST:
		new->x = (*snake)->x + 1;
		new->y = (*snake)->y;
		break;
	}
	*snake = new;
}


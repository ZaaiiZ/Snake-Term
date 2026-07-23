#include "snake.h"

static char g_buf = 0;

void	set_raw_mode(void)
{
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &t);
}

void	set_normal_mode(void)
{
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &t);
}

char	ft_getch(void)
{
	char	c;
	char	seq[2];

	if (g_buf != 0)
	{
		c = g_buf;
		g_buf = 0;
	}
	else
		read(0, &c, 1);

	if (c == '\033')
	{
		read(0, &seq[0], 1);
		read(0, &seq[1], 1);
		if (seq[0] == '[')
		{
			if (seq[1] == 'A') return ('U');
			if (seq[1] == 'B') return ('D');
			if (seq[1] == 'C') return ('R');
			if (seq[1] == 'D') return ('L');
		}
		return (0);
	}
	return (c);
}

int	ft_kbhit(void)
{
	int		flags;
	int		result;

	if (g_buf != 0)
		return (1);
	flags = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	result = read(0, &g_buf, 1);
	fcntl(0, F_SETFL, flags);
	if (result <= 0)
		g_buf = 0;
	return (result > 0);
}

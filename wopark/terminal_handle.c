#include "../includes/minish.h"

void	term_init(struct termios *term, struct termios *backup)
{
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, term);
	tcgetattr(STDIN_FILENO, backup);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

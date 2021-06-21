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
// void	set_backspace_key(t_cursor *cursor)
// {
// 	char	*tmp;

// 	(void)input;
// 	tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
// 	tputs(tgetstr("dm", NULL), 1, ft_putchar); // enter delete mode
// 	tputs(tgetstr("dc", NULL), 1, ft_putchar); // delete character (P*)
// 	tputs(tgetstr("ed", NULL), 1, ft_putchar); // end delete mode
// 	tmp = cursor->cur->data;
// 	if (*tmp)
// 	{
// 		tmp[cursor->key_pos] = 0;
// 		(cursor->key_pos)--;
// 		(cursor->len)--;
// 	}
// }

void	input_term(int buf)
{
	tputs(tgetstr("im", NULL), 1, ft_putchar); // enter insert mode
	tputs(tgetstr("ic", NULL), 1, ft_putchar); // insert character
	ft_putchar(buf);
	tputs(tgetstr("ip", NULL), 1, ft_putchar); // insert padding after inserted character
	tputs(tgetstr("ei", NULL), 1, ft_putchar); // exit insert mode
}
void	ft_freehistory(void *pending, void *finished)
{
	if (pending != NULL)
		free(pending);
	if (finished != NULL)
		free(finished);
}

int		set_printable_key(t_dllist *h_list, t_cursor *cursor)
{
	char	*pending;
	char	*finished;

	(void)h_list;
	input_term(cursor->buf);
	pending = cursor->cur->pending;
	finished = cursor->cur->finished;
	if (pending == NULL && finished)
	{
		cursor->cur->pending = ft_strdup(cursor->cur->finished);
		cursor->cur->pending = realloc(cursor->cur->pending, cursor->len + 1);
		pending = cursor->cur->pending;
	}
	if (cursor->buf == '\n')
	{
		if (pending && finished)
		{
			ft_dll_addhisnode(h_list, pending, finished);
			free(cursor->cur->pending);
			cursor->cur->pending = NULL;
		}
		else if (finished == NULL && *pending != 0)
		{
			finished = ft_strdup(cursor->cur->pending);
			pending = NULL;
			ft_dll_delhisnode(h_list, cursor->cur, ft_freehistory);
			ft_dll_addhisnode(h_list, pending, finished);
			free(finished);
		}
		else if (finished == NULL && *pending == 0)
			ft_dll_delhisnode(h_list, cursor->cur, ft_freehistory);
		cursor->cur = h_list->tail;
		return (0);
	}
	pending[cursor->key_pos] = cursor->buf;
	cursor->key_pos++;
	cursor->len++;
	cursor->cur->pending = realloc_input(cursor->cur->pending, cursor->len + 1);
	return (1);
}


int		term_key_handler(t_cursor *cursor, t_dllist *h_list)
{
	// if (cursor->buf == KEY_BACKSPACE && (cursor->key_pos) > 0)
	// 	set_backspace_key(cursor);
	// else
	if (cursor->buf == KEY_UP)
		return find_prev_history(h_list, cursor);
	else if (cursor->buf == KEY_DOWN)
		return find_next_history(h_list, cursor);
	else if (ft_isprint(cursor->buf) || cursor->buf == '\n')
	{
		return set_printable_key(h_list, cursor);
	}
	else if (cursor->buf == CTRL_D)
		return (0);
	return (1);
}

#include "includes/minish.h"

void    get_input(char **input)
{
        int             r_nbr;
        int             idx;
        int             cnt;
        char    buf;

        idx = 0;
        cnt = 1;
        *input = malloc(1);     // malloc error 처리

        while (1)
        {
                r_nbr = read(0, &buf, 1);
                if (r_nbr == 0 || buf == '\n')
                    break;
                *(*input + idx) = buf;
                idx++;
                *input = realloc(*input, cnt + 1);
                cnt++;
        }
        *(*input + idx) = '\0';
        return (0);
}

int             minish_loop()
{
        char    *input;

        while (1)
        {
            get_input(&input);
        }
        return (0);
}

int             main(int argc, char **argv, char **envv)
{
        minish_loop();
        return (0);
}

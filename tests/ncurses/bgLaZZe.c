#include <ncurses.h>

int main()
{    
    WINDOW* win = initscr();            /* Start curses mode           */

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }

    start_color();
    
    init_pair(1,COLOR_BLUE, COLOR_RED);

    bkgd(COLOR_PAIR(1));
    printw("Hello World !!!");    /* Print Hello World          */
    mvaddstr(10, 20, "Hello, World! (at pos 10, 20)");
    refresh();            /* Print it on to the real screen */
    getch();            /* Wait for user input */
    endwin();            /* End curses mode          */

    return 0;
}

#include "g_list.h"

/* This function gets the settings of the game including m, n and k */
/* from the setting file.  It open the file, read it by line and expain */
/* every line to get the setting values. It use the function  get_value*/
/* to get int type setting from a string. */
extern int get_setting(list_head_t *list_head,char *file_path, int *m, int *n, int *k);

/* This function use printf to show the menu, get input from terminal */
/* and test if the input word. */
extern int show_menu();

/* This function show the setting to the terminal. It symply use the  */
/* terminal command 'cat 'via function system().                            */
extern void view_setting();

/* This function  start a game and record log. It alloc memery for */
/* pointer titles and free it when a game is over. It use function    */
/* get_coodinates to get input title, and use function show_titles to */
/* reflesh the titles. Function test_winner is used to test if game is */
/* over. If turn reach m*n and no one win, it is a draw game.       */
extern void start_game(list_head_t *list_head,int m, int n, int k);

/* This funciotn show log to the user. It simply save the log using      */
/* function save_log and than show the file via 'cat'. The file is finaly  */
/* remove via 'rm' command. */
extern void view_log(list_head_t *list_head);

/* This function save the log from link list lst_head. It get the date and */
/* time via function time() and function local_time(). FIle is named by  */
/* setting and time information. */
extern void save_log(list_head_t *list_head,char *log_name);

/* This function is for Editor version. It get input from terminal and update */
/* settings file with the input. */
extern void edit_setting();
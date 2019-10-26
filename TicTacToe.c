#include <stdio.h>
#include <stdlib.h>
#include "ttt.h"

/* TicTacToe game. Play a  TicTacToe via a Terminal based menu */
int main(int argc, char **argv) {
    Pnode p, temp;
    int m, n, k;
    int cmd, ret;
    int flag = 1;
    /* Pointer to a generic link list which record the log */
    list_head_t *list_head;

    list_head = malloc(sizeof(list_head_t));
    ListInit(*list_head);

    ret = 0;

    if (argc != 2) {
        printf("usage: ./TicTacToe settings.txt\n");
    } else {
        if (get_setting(list_head, argv[1], &m, &n, &k) < 0) {
            ret = -1;
        } else {
            while (flag && ret == 0) {
                cmd = show_menu();
                switch (cmd) {
#ifdef EDITOR
                    case 0:
                        edit_setting();
                        if (get_setting(list_head, argv[1], &m, &n, &k) < 0)
                            ret = -1;
                        break;
#endif
                    case 1:
                        start_game(list_head, m, n, k);
                        break;
                    case 2:
                        view_setting();
                        break;
                    case 3:
                        view_log(list_head);
                        break;
                    case 4:
#ifdef SECRET
                        printf("cannot save in secret vision\n");
#else
                        save_log(list_head, NULL);
#endif
                        break;
                    case 5:
                        flag = 0;
                        break;
                    default:
                        printf("enter the number above\n");
                }
            }

            p = list_head->node.next;
            if (p != NULL) {
                while (p->next) {
                    temp = p;
                    p = p->next;
                    free(ListGetData(temp, list_entry_t));
                }
                free(ListGetData(p, list_entry_t));
            }

            free(list_head);
        }
    }
    return 0;
}

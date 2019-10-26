#include "ttt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* This funtion is use to get  the setting value from a string. */
/* Integer value is get bia x-'0' ,where x is a char type.      */
int get_value(char *buff);

/* This function show the titles via m*n memery.The flag 0        */
/* means is it space and show " ", 'X' and 'O' means it is placed */
/* by player 'X' or 'O'. */
void show_titles(char *titles, int m, int n);

/* This function get titles coodinates from input and refresh the */
/* m*n memery by coodinates. Player is decided by turn.         */
void get_coodinates(list_head_t *list_head, char *titles, int m, int n,
                    int turn);

/* This function is used to test if someone win the game. It test */
/* 4 orientation to find if k titles is places by one player. If any  */
/* orientaiotn meet the request, winner is the player.                */
int test_winner();

/* This is a poiter to link list entry, it point to titles messages. */
list_entry_t *entry;

int get_setting(list_head_t *list_head, char *file_path, int *m, int *n,
                int *k) {
    FILE *setp;
    char line1[20];
    char line2[20];
    char line3[20];
    char path[256];
    int ret = 0;

    getcwd(path, 256);

    *m = 0;
    *n = 0;
    *k = 0;

    setp = fopen(file_path, "rb");
    if (!setp) {
        printf("fail to open the setting file\n");
        ret = -1;
    }

    if (ret == 0) {
        fgets(line1, 10, setp);
        fgets(line2, 10, setp);
        fgets(line3, 10, setp);
    }

    if (ret == 0) {
        if (line1[0] == line2[0] || line1[0] == line3[0] ||
            line3[0] == line2[0]) {
            printf("duplicated setting\n");
            ret = -1;
        }
    }

    if (ret == 0) {
        switch (line1[0]) {
            case 'M':
                *m = get_value(line1 + 2);
                break;
            case 'N':
                *n = get_value(line1 + 2);
                break;
            case 'K':
                *k = get_value(line1 + 2);
                break;
            default:
                printf("wrong setting format\n");
                ret = -1;
        }
    }

    if (ret == 0) {
        switch (line2[0]) {
            case 'M':
                *m = get_value(line2 + 2);
                break;
            case 'N':
                *n = get_value(line2 + 2);
                break;
            case 'K':
                *k = get_value(line2 + 2);
                break;
            default:
                printf("wrong setting format\n");
                ret = -1;
        }
    }

    if (ret == 0) {
        switch (line3[0]) {
            case 'M':
                *m = get_value(line3 + 2);
                break;
            case 'N':
                *n = get_value(line3 + 2);
                break;
            case 'K':
                *k = get_value(line3 + 2);
                break;
            default:
                printf("wrong setting format\n");
                ret = -1;
        }
    }

    if (ret == 0) {
        if (*m <= 0 || *n <= 0 || *k <= 0) {
            printf("invalid setting values\n");
            ret = -1;
        }
    }

    if (ret == 0) {
        list_head->k = *k;
        list_head->m = *m;
        list_head->n = *n;
    }

    fclose(setp);
    return ret;
}

int get_value(char *buff) {
    int res = 0;
    while (*buff >= '0' && *buff <= '9') {
        res *= 10;
        res += *buff - '0';
        ++buff;
    }
    return res;
}

int show_menu() {
    int res;

    printf("\n");
#ifdef EDITOR
    printf("0. Edit settings\n");
#endif
    printf("1. Start a new game\n");
    printf("2. View the settings of the game\n");
    printf("3. View the current logs\n");
    printf("4. Save the logs to a file\n");
    printf("5. Exit the application\n");

    scanf("%d", &res);
#ifdef EDITOR
    while (res < 0 || res > 5) {
#else
    while (res < 1 || res > 5) {
#endif
        printf("please enter a right value\n");
        scanf("%d", &res);
    }
    return res;
}

static int show_file(char *file_name) {
    char c;
    FILE *fp;
    int ret = 0;
    fp = fopen(file_name, "r");
    if (fp) {
        while ((c = fgetc(fp)) != EOF) {
            putc(c, stdout);
        }
        putc('\n', stdout);
        fclose(fp);
    } else {
        ret = -1;
    }
    return ret;
}

void view_setting() { show_file("./settings.txt"); }

void start_game(list_head_t *list_head, int m, int n, int k) {
    int turn = 0;
    int i;
    int num = m * n;
    int win = 0;
    char *titles = malloc(num);
    for (i = 0; i < num; i++) titles[i] = 0;
    show_titles(titles, m, n);
    while (++turn <= m * n && win == 0) {
        get_coodinates(list_head, titles, m, n, turn);
        show_titles(titles, m, n);
        if (test_winner(list_head, titles, m, n)) {
            win = 1;
        }
    }
    if (turn == m * n + 1) printf("draw\n");
    free(titles);
}

void show_titles(char *titles, int m, int n) {
    int i, j;
    for (i = 0; i < n; i++) printf("--");
    printf("\n");

    for (i = 0; i < m; i++) {
        printf("|");
        for (j = 0; j < n; j++) {
            if (titles[i * n + j] == 0)
                printf(" ");
            else
                printf("%c", titles[i * n + j]);
            printf("|");
        }
        printf("\n");
        for (j = 0; j < n; j++) {
            printf("--");
        }
        printf("\n");
    }
}

void get_coodinates(list_head_t *list_head, char *titles, int m, int n,
                    int turn) {
    char side;
    char input[254];
    int x = 0, y = 0;
    int scan;
    side = turn % 2 == 0 ? 'X' : 'O';

    scan = 1;
    while (scan) {
        scanf("%s", input);

        if (sscanf(input, "%d,%d", &x, &y) == 2) {
            if (x >= n || y >= m) {
                printf("expend the range %d > m - 1, %d > n - 1\n", x, y);
            } else {
                if (titles[y * n + x] != 0) {
                    printf("(%d,%d) already has one\n", x, y);
                } else {
                    titles[y * n + x] = side;
                    entry = malloc(sizeof(list_entry_t));
                    entry->turn = turn;
                    entry->player = side;
                    entry->x = x;
                    entry->y = y;
                    ListTailInsert(*list_head, *entry);
                    scan = 0;
                }
            }
        } else {
            printf("usage:x,y\n");
        }
    }
}

int test_winner(list_head_t *list_head, char *titles, int m, int n) {
    int x = entry->x;
    int y = entry->y;
    int ret = 0;

    /*test orientation 1*/
    int count = 1;
    while (++x < n && titles[y * n + x] == entry->player) count++;
    x = entry->x;
    while (--x >= 0 && titles[y * n + x] == entry->player) count++;
    if (count >= list_head->k) {
        printf("%c win\n", entry->player);
        ret = 1;
    }

    /*test orientation 2*/
    if (ret == 0) {
        x = entry->x;
        y = entry->y;
        count = 1;
        while (++y < m && titles[y * n + x] == entry->player) count++;
        y = entry->y;
        while (--y >= 0 && titles[y * n + x] == entry->player) count++;
        if (count >= list_head->k) {
            printf("%c win\n", entry->player);
            ret = 1;
        }
    }

    if (ret == 0) {
        /*test orientaiton 3*/
        x = entry->x;
        y = entry->y;
        count = 1;
        while (++y < m && ++x < n && titles[y * n + x] == entry->player)
            count++;
        x = entry->x;
        y = entry->y;
        while (--y >= 0 && --x >= 0 && titles[y * n + x] == entry->player)
            count++;
        if (count >= list_head->k) {
            printf("%c win\n", entry->player);
            ret = 1;
        }
    }

    /*test orientaiton 4*/
    if (ret == 0) {
        x = entry->x;
        y = entry->y;
        count = 1;
        while (++y < m && --x >= 0 && titles[y * n + x] == entry->player)
            count++;
        x = entry->x;
        y = entry->y;
        while (--y >= 0 && ++x < n && titles[y * n + x] == entry->player)
            count++;
        if (count >= list_head->k) {
            printf("%c win\n", entry->player);
            ret = 1;
        }
    }

    return ret;
}

extern void view_log(list_head_t *list_head) {
    char log_path[128];
    save_log(list_head, log_path);
    show_file(log_path);
    remove(log_path);
}

void save_log(list_head_t *list_head, char *log_name) {
    char path[128];
    char buff[128];
    Pnode p;
    int n;
    time_t now;
    int fd;
    int game = 0;
    struct tm *now_tmp;
    time(&now);
    now_tmp = localtime(&now);
    n = sprintf(path, "MNK_%d-%d-%d_%d-%d_%d-%d.log", list_head->m,
                list_head->n, list_head->k, now_tmp->tm_hour, now_tmp->tm_min,
                now_tmp->tm_mday, now_tmp->tm_mon + 1);
    if (log_name) {
        sprintf(log_name, "MNK_%d-%d-%d_%d-%d_%d-%d.log", list_head->m,
                list_head->n, list_head->k, now_tmp->tm_hour, now_tmp->tm_min,
                now_tmp->tm_mday, now_tmp->tm_mon + 1);
    }
    fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
    n = sprintf(buff, "SETTINGS:\n\tM: %d\n\tN: %d \n\tK: %d\n\n", list_head->m,
                list_head->n, list_head->k);
    write(fd, buff, n);

    p = list_head->node.next;
    while (p) {
        if (ListGetData(p, list_entry_t)->turn == 1) {
            n = sprintf(buff, "GAME %d:\n", ++game);
            write(fd, buff, n);
        }
        n = sprintf(buff, "\tTurn: %d\n\tPlayer: %c\n\tLocation: %d,%d\n\n",
                    ListGetData(p, list_entry_t)->turn,
                    ListGetData(p, list_entry_t)->player,
                    ListGetData(p, list_entry_t)->x,
                    ListGetData(p, list_entry_t)->y);
        write(fd, buff, n);
        p = p->next;
    }
    close(fd);
}

void edit_setting() {
    int fd;
    int n, m, k;
    int len;
    char buff[128];
    printf("m=?\n");
    scanf("%d", &m);
    printf("n=?\n");
    scanf("%d", &n);
    printf("k=?\n");
    scanf("%d", &k);
    len = sprintf(buff, "M=%d\nN=%d\nK=%d\n", m, n, k);
    buff[len] = 0;

    fd = open("settings.txt", O_WRONLY);
    write(fd, buff, len + 1);
    close(fd);
}
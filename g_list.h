/* Type of node of the generic link list and its pointer. */
/* It is use to search the list.                                     */
typedef struct node Node;
typedef struct node *Pnode;

/* Link list member node prev point to its previous node, */
/* next point to its next node.                                      */
struct node {
    Pnode prev, next;
};

/* Head type of the link list. It stored the information of game */
/* settings. Member node is used to search the list.                */
typedef struct head_entry list_head_t;
struct head_entry {
    int m;
    int n;
    int k;
    Node node;
};

/* Entry type of the link list. It store the infomation of eah steps. */
/* Member node is used to search the list.                                  */
typedef struct step_entry list_entry_t;
struct step_entry {
    int turn;
    char player;
    int x;
    int y;
    Node node;
};

/* Link list head initialize, set prev and next NULL. */
#define ListInit(h)           \
    do {                      \
        (h).node.prev = NULL; \
        (h).node.next = NULL; \
    } while (0)

/* Insert entry to a link list */
#define ListTailInsert(h, l)         \
    do {                             \
        Pnode t = &(h).node;         \
        while (t->next) t = t->next; \
        (l).node.prev = (t);         \
        (l).node.next = (t)->next;   \
        (t)->next = &(l).node;       \
    } while (0)

/* Get a link list entry via its node and the entry type.    */
/* The entry type struct_type pointor point to 0, than -> */
/* point to its member node, so its address is the difference */
/* between node and struct_type. We use '&' to get address. */
/* Address of node minus this different is the address of this */
/* entry. */
#define ListGetData(l, struct_type) \
    ((struct_type *)((char *)(l) - (char *)&((struct_type *)0)->node))

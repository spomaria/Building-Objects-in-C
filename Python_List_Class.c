#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lnode {
    char *text;
    struct lnode *next;
};

struct pylist {
  struct lnode *head;
  struct lnode *tail;
  int count;
};

/* Constructor - lst = list() */
struct pylist * pylist_new() {
    struct pylist *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

/* Destructor - del(lst) */
void pylist_del(struct pylist* self) {
    struct lnode *cur, *next;
    cur = self->head;
    while(cur) {
        free(cur->text);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    struct pylist * lst = pylist_new();
    pylist_append(lst, "Hello world");
    pylist_print(lst);
    pylist_append(lst, "Catch phrase");
    pylist_print(lst);
    pylist_append(lst, "Brian");
    pylist_print(lst);
    printf("Length = %d\n", pylist_len(lst));
    printf("Brian? %d\n", pylist_index(lst, "Brian"));
    printf("Bob? %d\n", pylist_index(lst, "Bob"));
    pylist_del(lst);
}


/* print(lst) */
void pylist_print(struct pylist* self)
{
    /* About 10 lines of code 
       The output should match Python's
       list output

       ['Hello world', 'Catch phrase']

	Use printf cleverly, *not* string
	concatenation since this is C, not Python.
    */
   struct lnode *cur;
   int index = 0;
   printf("[");
   for(cur = self->head; cur != NULL; cur = cur->next){
        if(index == 0){
            printf("'%s'", cur->text);
        } else {
            printf(", '%s'", cur->text);
        }
        index++;
   }
   printf("]\n");
}

/* len(lst) */
int pylist_len(const struct pylist* self)
{
    /* One line of code */
    return self->count;
}

/* lst.append("Hello world") */
void pylist_append(self, str) 
    struct pylist* self; 
    char *str; {
    /* Review: Chapter 6 lectures and assignments */
    struct lnode *new = (struct lnode *) (malloc(sizeof(struct lnode)));
    new->text = str;
    new->next = NULL;

    if(self->head == NULL) self->head = new;
    if (self->tail != NULL) self->tail->next = new;
    self->tail = new;
    self->count++;
}
/* lst.index("Hello world") - if not found -1 */
int pylist_index(struct pylist* self, char *str)
{
    /* Seven or so lines of code */
    struct lnode *cur;
    int index = 0;
    for(cur = self->head; cur != NULL; cur = cur->next) {
        if(cur->text == str) return index;
        index++;
    }
    return -1;
}

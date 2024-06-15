# C Programs that Build Objects in C

## Introduction
In this course, I am learning the how to gain programming mastery in the Building Objects in C Course, as part of the C Programming for Everybody Specialization at [Coursera](https://www.coursera.org/) under the tutelage of [Charles Russel Severance](http://www.dr-chuck.com/)

## Writing the C Program

### 1. The Python String Class
We shall write a C Program that builds a Python String Class.

On our local machine, we create a file and name it `Python_String_Class.c` using the following bash command
```shell
touch Python_String_Class.c
```
Inside our `Python_String_Class.c` file, we write following codes
```javascript
#include <stdio.h>
#include <stdlib.h>

struct pystr
{
    int length;
    /*the length of data */
    int alloc; 
    char *data;
};

/* Constructor - x = str() */ 
struct pystr * pystr_new() {
    struct pystr *p = malloc(sizeof(*p));
    p->length = 0;
    p->alloc = 10;
    p->data = malloc(10);
    p->data[0] = '\0';
    return p;
}

/* Destructor - del(x) */ 
void pystr_del(const struct pystr* self) {
    free((void *)self->data); /* free string first */
    free((void *)self);
}

void pystr_dump(const struct pystr* self)
{
    printf("Pystr length=%d alloc=%d data=%s\n",
            self->length, self->alloc, self->data);
}

int pystr_len(const struct pystr* self)
{
    return self->length;
}

char *pystr_str(const struct pystr* self)
{
    return self->data;
}


int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */ 

    struct pystr * x = pystr_new();
    pystr_dump(x);

    pystr_append(x, 'H');
    pystr_dump(x);

    pystr_appends(x, "ello world");
    pystr_dump(x);

    pystr_assign(x, "A completely new string");
    printf("String = %s\n", pystr_str(x));
    printf("Length = %d\n", pystr_len(x));
    pystr_assign(x, "This is absolutely amazing. Thank you Dr Chuck!");
    printf("String = %s\n", pystr_str(x));
    printf("Length = %d\n", pystr_len(x));
    pystr_del(x);
}




/* x = x + 'h'; */ 

void pystr_append(self, ch) 
    struct pystr* self; 
    char ch; {
    /* Need about 10 lines of code here */
    /* 1. Check the length of data in the struct, say dataLen */ 
    /* 2. Check the size of alloc in the struct, say allocLen */
    /* 3. If allocLen >= dataLen + 2, assign the character to the 'dataLen' position and terminate the string with '\0' at the 'dataLen + 1' position */
    /* 4. If condition in 3 does not hold, request for more space using 'realloc' and carry out steps 1 to 3 again. */
    int dataLen, allocLen;
    dataLen = self->length;
    allocLen = self->alloc;
    if(allocLen >= (dataLen + 2)){
        /* There is sufficient memory to append one character and the zero character */
        self->data[dataLen++] = ch;
        self->data[dataLen] = '\0';
        /* adjust the length of character array accordingly */
        self->length = dataLen;
    } else{
        /* There is no sufficient memory to append one character and the zero character */
        /* Therefore, increase the memory allocation */
        self->alloc += 10;
        self->data = (char *) realloc(self->data, self->alloc);
        /* Now we append one character and the zero character */
        self->data[dataLen++] = ch;
        self->data[dataLen] = '\0';
        /* adjust the length of character array accordingly */
        self->length = dataLen;
    }
}

/* x = x + "hello"; */

void pystr_appends(self, str) 
    struct pystr* self; 
    char *str; {
    /* Need a line or two of code here  */
    int i;
    for (i = 0; str[i]; i++){
        pystr_append(self, str[i]);
    }
    
}

/* x = "hello"; */

void pystr_assign(self, str) 
    struct pystr* self; 
    char *str; {
    /* Need about three lines of code here */

    /* 1. restore the string to default */
    /* 2. append the new string to the restored string */
    /*self->data[0] = '\0';*/
    pystr_del(self);
    self = pystr_new();
    pystr_appends(self, str);
}
```

In the above code snippet, there are eight functions `main()`, `pystr_append`, `pystr_appends`, `pystr_dump`, `pystr_assign`, `pystr_str`, `pystr_len` and `pystr_del`. 
- The `pystr_append` function adds or appends a character to the string
- The `pystr_appends` function adds or appends a string to the string;  
- The `pystr_dump` function prints the string to the console 
- The `pystr_assign` assigns a new string to the variable 
- The `pystr_str` returns the string stored by the variable
- The `pystr_len` returns the length of the string stored by the variable
- The `pystr_del` deletes the string thereby freeing memory 
- The `main()` function calls the other functions and executes them.


### 2. The Python List Class
We shall write a C Program that builds a Python List Class. The below steps can be used to replicate the other programs in this directory.

On our local machine, we create a file and name it `Python_List_Class.c` using the following bash command
```shell
touch Python_List_Class.c
```
Inside our `Python_List_Class.c` file, we write following codes
```javascript
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
    return self->count;
}


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

```

In the above code snippet, there are six functions `main()`, `pylist_append`, `pylist_print`, `pylist_len`, `pylist_index` and `pylist_del`. 
- The `pylist_append` function adds or appends a string to the list; 
- The `pylist_print` function prints the list to the console 
- The `pylist_len` returns the length of the list 
- The `pylist_index` checks if a string is an element of the list and returns its index, otherwise returns `-1`
- The `pylist_del` deletes the list and all its elements thereby freeing memory 
- The `main()` function calls the other functions and executes them.


## Compiling the Script
To compile our script, we use the following bash command
```shell
gcc -ansi Python_List_Class.c -o Python_List_Class
```
The above command will produce an executable file named `Python_List_Class` in the same directory as our `Python_List_Class.c` file upon successful compilation. In order to test the functionality of our C program, we run the following command
```bash
./Python_List_Class
```

The expected result is 
```
['Hello world']
['Hello world', 'Catch phrase']
['Hello world', 'Catch phrase', 'Brian']
Length = 3
Brian? 2
Bob? -1
```

In order to compile other scripts, use the above steps while substituting the name of the relevant C Program.

## Authors
Nengak Emmanuel Goltong 

[@NengakGoltong](https://twitter.com/nengakgoltong) 
[@nengakgoltong](https://www.linkedin.com/in/nengak-goltong-81009b200)

Under the tutelage of 

Charles Russel Severance
[@drchuck](https://twitter.com/drchuck)
[@charlesseverance](https://www.linkedin.com/in/charlesseverance)

## License
This project is licensed under the MIT License - see the LICENSE.md file for details
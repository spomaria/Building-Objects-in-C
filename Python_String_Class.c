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
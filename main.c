#include <stdio.h>
#include <stdlib.h>

/** ===== C Major Library =====
 *  A simple and easy to use set of C functions,
 *  macros, and data structures.
 *  @author Jiangcheng Oliver Chu
 *  Created: The 1st of February, Year 2013 C.E.
 */

#define byte char
#define positive unsigned
#define either signed
#define MEGABYTE 1048576
#define KILOBYTE 1024
#define KILOBYTE_2x 2048
#define SCOPE_SIZE 256
#define SCOPES_MAXIMUM 64
#define var struct jsVar
#define CAT_DIGITS 0
#define CAT_FRACTN 1
#define CAT_STRING 2
#define CAT_LKLIST 3

/** We allow (sizeof(int)) * MEGABYTE bytes of
 *  heap space, and (sizeof(int)) * KILOBYTE bytes
 *  of stack space.
 */
int CM_HEAP[MEGABYTE];
int CM_STACK[KILOBYTE];
int CM_SCOPES[SCOPES_MAXIMUM][SCOPE_SIZE];

int REF_MANAGER[KILOBYTE_2x];

positive int CM_SP  = 0;
positive int CM_HP  = 0;
positive int CM_RMP = 0;

/** Define a JavaScript variable, which holds
 *  arbitrary bytes and a type. */
struct jsVar {
    positive byte category;
    positive short numBytes;
    void *reference;
};

/** Like malloc, but superior.
 *  Garbage collection is handled
 *  if you remember to call destroyScope()
 *  at the end of every function, and
 *  createScope() at the start of every
 *  user-defined function. Notice that
 *  this isn't quite As convenient as
 *  automatic memory management.
 *  You do not need to worry about scope
 *  creation or destruction if you
 *  never use javaNew(...) inside a
 *  particular function.
 */
int javaNew(int wantedBytes) {
    int saved = CM_HP;
    REF_MANAGER[CM_RMP] = saved;
    REF_MANAGER[CM_RMP + 1] = wantedBytes;
    CM_HP += wantedBytes;
    CM_RMP += 2;
    return saved;
}

/** Returns how many Java memory leaks there are. */
int getActiveMemoryLeaks() {
    return CM_RMP / 2;
}

void print(char *someString) {
    puts(someString);
}

void writeLine() {
    print("");
}

void printInt(int i) {
    printf("%i", i);
    writeLine();
}

void write(char *someString) {
    printf("%s", someString);
}

void warning(char *message) {
    write("ERROR: ");
    print(message);
    char useless[256];
    gets(useless);
}

int main(int argc, char **strings) {
    print("hi...");
    write("The total number of memory leaks is: ");
    printInt(getActiveMemoryLeaks());
    javaNew(0);
    javaNew(0);
    write("Now the number of memory leaks is: ");
    printInt(getActiveMemoryLeaks());
    return 0;
}

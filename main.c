#include <stdio.h>
#include <stdlib.h>

/** ===== C Major Library =====
 *  A simple and easy to use set of C functions, macros,
 *  and data structures.
 *  Designed at UC Berkeley for UCB grads and undergrads.
 *
 *  @author Jiangcheng Oliver Chu
 *  Created: The 1st of February, Year 2013 C.E.
 *  Last Modified: 6:43 AM PST on 2 February 2013.
 *
 *  License: GPLv3
 *  View License: http://www.gnu.org/licenses/gpl-3.0.txt
 */

/* Declare psuedo-registers: */
signed long R_ALPHA = 0;
signed long R_DELTA = 0;
signed long R_GAMMA = 0;
signed long R_OMEGA = 0;
unsigned long R2_ALPHA = 0;
unsigned long R2_DELTA = 0;
unsigned long R2_GAMMA = 0;
unsigned long R2_OMEGA = 0;

/* Declare special purpose psuedo-registers: */
unsigned long __iterator__ = 0;
char *__text__ = "";
void *__lambda__ = &printf;

/* Declare floating-point psuedo-registers: */
double R_ICHI = 0.0;
double R_NI   = 0.0;
double R_SAN  = 0.0;
double R_SHI  = 0.0;
double R_GO   = 0.0;
double R_ROKU = 0.0;

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
    int wantedInts = 1 + (wantedBytes / 4);
    int saved = CM_HEAP + CM_HP;
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

void writeInt(int i) {
    printf("%i", i);
}

void printInt(int i) {
    writeInt(i);
    writeLine();
}

void writeFloat(float f) {
    printf("%f", f);
}

void inputInto(char *targeted) {
    gets(targeted);
}

void write(char *someString) {
    printf("%s", someString);
}

/** Warning: Allocates psuedo-dynamic memory. */
char *pyInput(char *prompt) {
    write(prompt);
    char *gotten = javaNew(256);
    gets(gotten);
    return gotten;
}

void warning(char *message) {
    write("ERROR: ");
    print(message);
    char useless[256];
    gets(useless);
}

int square(int x) {
    return x * x;
}

int *sqrDifferently(int f) {
    int *sum = javaNew(4);
    for (__iterator__ = 0; __iterator__ < f; ++__iterator__) {
        *sum += f;
    }
    return sum;
}

int cons(int a, int b) {
    int *linked = javaNew(8);
    linked[0] = a;
    linked[1] = b;
    return linked;
}

int car(int *twoInts) {
    return *twoInts;
}

int cdr(int *twoInts) {
    return twoInts[1];
}

float divideApply(void *functionOne, void *functionTwo, int *pairOfInts) {
    int (*lambda_1)(int);
    int (*lambda_2)(int);
    /* Hey look! Python code with semicolons! */
    lambda_1 = functionOne;
    lambda_2 = functionTwo;
    return ((float) (lambda_1(car(pairOfInts)))) / (lambda_2(cdr(pairOfInts)));
}

int main(int numOfArgs, char **strings) {
    int *x = cons(18, 19);
    writeFloat(divideApply(square, sqrDifferently, x));
    print("");
    printInt(x[0]);
    printInt(x[1]);
    print("");
    write("You gave this program ");
    int actualNumOfArgs = numOfArgs - 1;
    writeInt(actualNumOfArgs);
    write(" argument");
    /* Pluralize the word if necessary. */
    if (actualNumOfArgs != 1) {
        write("s");
    }
    print(", not including the program's name.");
    print("");
    write("The total number of memory leaks is: ");
    printInt(getActiveMemoryLeaks());
    print("< Allocated some memory on the false heap. >");
    javaNew(0);
    javaNew(0);
    write("Now the number of memory leaks is: ");
    printInt(getActiveMemoryLeaks());
    char *gotcha = pyInput("What is your name? ");
    write("Your name must be: ");
    print(gotcha);
    write("Now the number of memory leaks is: ");
    printInt(getActiveMemoryLeaks());
    print("");
    print("Press ENTER or RETURN to close this program.");
    pyInput("");
    return 0;
}

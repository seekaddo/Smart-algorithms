/* Mastervorlage Gueltig ab: 2016-12-26*/

/* Folgende Angaben sind hier im Kommentar verpflichtend zu erfassen */
/* Dennis Addo */

/* Exercise_11_2*/

/* Programmcode hier einfügen */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    int count;
    int capacity;
    int *data;
} Stack;


Stack create_stack(int initialcapacity);

void push(int value, Stack *stack);

int pop(Stack *stack);

int delete_stack(Stack *stack);

int main(int argc, char *argv[]) {

    int i;
    /* create empty stack */
    Stack stack = create_stack(20);
    /* push elements onto stack */
    for (i = 0; i < 20; i++) push(i, &stack);
    /* pop all elements from stack */

    for (i = 20; i < 27; i++) push(i, &stack);
    printf("new cap %d\n", stack.capacity);
    while (stack.count > 0) printf("%d ", pop(&stack));

    delete_stack(&stack);

    return 0;
}


Stack create_stack(int initialcapacity) {
    Stack result;
    result.count = 0;

    result.capacity = initialcapacity;
    result.data = malloc(initialcapacity * sizeof(int));
    if (!result.data) {
        printf("Sorry not enough space available\n");
    }
    return result;
}

/* Pushes value on top of given stack. */
void push(int value, Stack *stack) {

    if (stack->count < stack->capacity) {
        stack->data[stack->count++] = value;

    } else if ((stack->count == stack->capacity)) {
        int ncap = stack->capacity;

        if (!(stack->data = realloc(stack->data, (2 * stack->capacity) * sizeof(int))))
            printf("Realloc failed\n");

        stack->data[stack->count++] = value;
        stack->capacity = 2 * ncap;
    }

}

/* Removes and returns top element of given stack. */
int pop(Stack *stack) {
    if (stack->count < 0)
        printf("Sorry stack full\n");

    return stack->data[--stack->count];
}

/* Deletes the stack */
int delete_stack(Stack *stack) {
    stack->capacity = 0;
    stack->count = 0;
    free(stack->data);
    stack->data = NULL;
    return stack->data != NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 定义栈结构
struct Stack {
    char *array;
    int top;
    int capacity;
};

// Create a stack
struct Stack *createStack(int capacity) {
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Check is the stack is empty
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push an item to the stack
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Pop an item from the stack
char pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

// Return the top item from the stack
char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

// Check if the given character is a valid parenthesis
bool isValid(char *s) {
    struct Stack* stack = createStack(100);  // Suppose the maximum length of the string is 100
    for (int i = 0; s[i] != '\0'; i++) {
        char current = s[i];
        //if the current character is a opening parenthesis, push it to the stack
        if (current == '(' || current == '[' || current == '{') {
            push(stack, current);
        } else {
            // if the current character is a closing parenthesis, check if the stack is empty
            if (isEmpty(stack)) {
                return false;  // Don't have a matching opening parenthesis
            }
            char top = pop(stack);
            // Check if the popped character matches the current closing parenthesis
            if ((current == ')' && top != '(') ||
                (current == '}' && top != '{') ||
                (current == ']' && top != '[')) {
                    return false;
            }
        }
    }
    return isEmpty(stack);
}

// Test the function
int main() {
    char *s = "{[()]}";  // for test
    if (isValid(s)) {
        printf("The string is valid\n");
    } else {
        printf("The string is invalid\n");
    }
    return 0;
}




// The problem to solve is:
// https://leetcode.cn/problems/valid-parentheses/description/
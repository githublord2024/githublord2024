#include<stdio.h>
#include<string.h>
#include<ctype.h>


int priority(char ch) {
    switch (ch) {
        case '+': 
        case '-': return 1;
        case '*': 
        case '/': return 2;
        case '^': return 3;
        case '(': return 0;
        default: return -1;
    }
}


int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main() {
    char exp[100], output[100] = "", stack[100];
    int index = 0, top = -1;
    int evalstack[100];
    int ch;

    printf("Enter the expression: ");
    scanf("%s", exp);

    do {
        printf("\n1. Infix to Postfix\n2. Evaluation\n3. Exit\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: {
                int len = strlen(exp);

                for (int i = 0; i < len; i++) {
                    if (isalpha(exp[i])) {  
                        output[index++] = exp[i];
                    } else {
                        int prio = priority(exp[i]);
                        if (exp[i] == '(') {  
                            stack[++top] = exp[i];
                        } else if (exp[i] == ')') {  
                            while (top != -1 && stack[top] != '(') {
                                output[index++] = stack[top--];
                            }
                            top--;  
                        } else {
                            
                            while (top != -1 && prio <= priority(stack[top])) {
                                output[index++] = stack[top--];
                            }
                            stack[++top] = exp[i];  
                        }
                    }
                }

                
                while (top != -1) {
                    output[index++] = stack[top--];
                }

                output[index] = '\0';  
                printf("Postfix expression: %s\n", output);
                break;
            }

            case 2: {
                if (strlen(output) == 0) {
                    printf("Please convert the infix expression to postfix first.\n");
                    break;
                }

                int operands[26] = {0};  
                int len = strlen(exp);

                
                for (int i = 0; i < len; i++) {
                    if (isalpha(exp[i]) && operands[exp[i] - 'a'] == 0) {
                        printf("Enter value for %c: ", exp[i]);
                        scanf("%d", &operands[exp[i] - 'a']);
                    }
                }

                
                top = -1;
                for (int i = 0; i < strlen(output); i++) {
                    if (isalpha(output[i])) {
                        evalstack[++top] = operands[output[i] - 'a'];
                    } else {
                        int operand2 = evalstack[top--];
                        int operand1 = evalstack[top--];
                        switch (output[i]) {
                            case '+': evalstack[++top] = operand1 + operand2; break;
                            case '-': evalstack[++top] = operand1 - operand2; break;
                            case '*': evalstack[++top] = operand1 * operand2; break;
                            case '/': evalstack[++top] = operand1 / operand2; break;
                            case '^': evalstack[++top] = power(operand1, operand2); break;
                        }
                    }
                }

                
                printf("Result of the expression: %d\n", evalstack[top]);
                break;
            }

            case 3: {
                printf("Exiting...\n");
                break;
            }

            default:
                printf("Invalid choice!\n");
        }

    } while (ch != 3);  

    return 0;
}

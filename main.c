#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

struct stack
{
    char arr[MAX];
    int top;
};
struct stackFloat
{
    float arr[MAX];
    int top;
};

void pushChar(struct stack *s, char ch)
{
    if (s->top >= MAX - 1)
    {
        printf("Stack Overflow Error");
        exit(1);
    }
    s->arr[++s->top] = ch;
}
void pushFloat(struct stackFloat *s, float num)
{
    if (s->top >= MAX - 1)
    {
        printf("Stack Overflow Error");
        exit(1);
    }
    s->arr[++s->top] = num;
}

char popChar(struct stack *s)
{
    if (s->top == -1)
    {
        printf("Stack UnderFlow Error");
        exit(1);
        return '_';
    }
    return s->arr[s->top--];
}
float popFloat(struct stackFloat *s)
{
    if (s->top == -1)
    {
        printf("Stack UnderFlow Error");
        exit(1);
        return -1.0;
    }
    return s->arr[s->top--];
}

char peekChar(struct stack *s)
{
    if (s->top == -1)
    {
        printf("Stack UnderFlow Error");
        exit(1);
        return '_';
    }
    return s->arr[s->top];
}
float peekFloat(struct stackFloat *s)
{
    if (s->top == -1)
    {
        printf("Stack UnderFlow Error");
        exit(1);
        return -1.0;
    }
    return s->arr[s->top];
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void InfixToPostfix(char *expr, char *postfix)
{
    struct stack s, Ps;
    s.top = -1, Ps.top = -1;
    int j = 0;
    int i = 0;

    while (expr[i] == ' ')
        i++;
    if (expr[i] == '-')
        postfix[j++] = expr[i++];
    for (; expr[i]; i++)
    {
        char ch = expr[i];
        if (ch == ' ')
            continue;
        else if (ch >= '0' && ch <= '9')
        {
            while (expr[i] >= '0' && expr[i] <= '9')
            {
                postfix[j++] = expr[i++];
            }
            if (expr[i] == '.')
            {
                postfix[j++] = expr[i++];
                while (expr[i] >= '0' && expr[i] <= '9')
                {
                    postfix[j++] = expr[i++];
                }
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (ch == '(')
        {
            pushChar(&s, ch);
            pushChar(&Ps, ch);
            i++;
            while (expr[i] == ' ')
                i++;
            if (expr[i] == '-')
                postfix[j++] = expr[i++];
            i--;
        }
        else if (ch == ')')
        {
            if (Ps.top == -1 || peekChar(&Ps) != '(')
            {
                printf("Invalid Paranthesis Ordering");
                exit(1);
            }
            popChar(&Ps);
            while (s.top != -1 && peekChar(&s) != '(')
            {
                postfix[j++] = popChar(&s);
                postfix[j++] = ' ';
            }
            popChar(&s);
        }
        else if (precedence(ch) > 0)
        {
            while (s.top != -1 && ((ch == '^' && precedence(peekChar(&s)) > precedence(ch)) || (ch != '^' && precedence(peekChar(&s)) >= precedence(ch))))
            {
                postfix[j++] = popChar(&s);
                postfix[j++] = ' ';
            }
            pushChar(&s, ch);
        }
        else
        {
            printf("Invalid Character : %c at index %d\n", ch, i);
            exit(1);
        }
    }
    if (Ps.top >= 0)
    {
        printf("Invalid Expression-Bracket Mismatch\n");
        exit(1);
    }
    while (s.top != -1)
    {
        postfix[j++] = popChar(&s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}
float EvalExp(char *postfix)
{
    struct stackFloat s;
    s.top = -1;
    int sign = 0;
    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];
        if (ch == ' ')
            continue;
        else if (ch == '-' && (postfix[i + 1] >= '0' && postfix[i + 1] <= '9'))
        {
            sign = 1;
        }
        else if (ch >= '0' && ch <= '9')
        {
            float num = 0.0;
            while (postfix[i] >= '0' && postfix[i] <= '9')
            {
                num = num * 10 + (postfix[i++] - '0');
            }
            if (postfix[i] == '.')
            {
                i++;
                float fraction = 0.1;
                while (postfix[i] >= '0' && postfix[i] <= '9')
                {
                    num = num + (postfix[i++] - '0') * fraction;
                    fraction /= 10;
                }
            }
            if (sign == 1)
            {
                num = -num;
                sign = 0;
            }
            pushFloat(&s, num);
            i--;
        }
        else if (precedence(ch) > 0)
        {
            if (s.top < 1)
            {
                printf("Error: Invalid postfix expression (insufficient operands)\n");
                exit(1);
            }
            float num1 = popFloat(&s);
            float num2 = popFloat(&s);
            switch (ch)
            {
            case '+':
                pushFloat(&s, num2 + num1);
                break;
            case '-':
                pushFloat(&s, num2 - num1);
                break;
            case '*':
                pushFloat(&s, num2 * num1);
                break;
            case '/':
                if (num1 == 0.0)
                {
                    printf("Error: Division by zero\n");
                    exit(1);
                }
                pushFloat(&s, num2 / num1);
                break;
            case '^':
                pushFloat(&s, (float)pow(num2, num1));
                break;
            }
        }
        else if (ch == '\0')
            break;
        else
        {
            printf("Error (invalid character):%c\n", ch);
            exit(1);
        }
    }
    if (s.top > 0)
    {
        printf("Error: Invalid expression (extra operands)\n");
        exit(1);
    }
    return popFloat(&s);
}

int main()
{
    char infix[MAX], postfix[MAX];
    scanf("%[^\n]", infix);
    InfixToPostfix(infix, postfix);
    printf("PostFix Expression: %s\n", postfix);
    printf("Expression Result: %.4f\n", EvalExp(postfix));
    return 0;
}

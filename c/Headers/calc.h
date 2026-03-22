#ifndef _CALC_
#define _CALC_

// #define NDEBUG // for disabling assert calls
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
// #define DEBUG

#define ERR(str) fprintf(stderr, "Error: %s\n", str);
#define SYNTAX_ERR -25
#define INVALID_INPUT -10
#define QUIT 100
#define INITIAL_CAPACITY 128
#define ALLOC_FAILED -1

enum
{
  add = '+',
  substruct = '-',
  multiply = '*',
  divide = '/',
  modulo = '%',
  pleft = '(',
  pright = ')'
}; // operator value

typedef enum
{
  numberType = 666,
  operatorType = 777,
  parentheses = 999,
  eof = 888
} TokenType;

enum
{
  addition = 1,
  substruction = 1,
  multiplication = 2,
  devision = 2
};

typedef struct
{
  char* ptr;
  int currentIdx;
  int capacity;
  int size;
} Buffer;

typedef struct
{
  TokenType type;
  union
  {
    long double numberValue;
    char charValue;
  };
  int l_bp;
  int r_bp;
} Token;

typedef struct
{
  Token* items;
  size_t capacity;
  size_t size;
} TokenArray;

char peek(int offset);
bool is_digit(char input);
bool is_operator(char input);
void destructor(Buffer* buffer);
long double parse_num(Buffer* buffer);
Token parse_op(char c);
Token next_token(TokenArray* tokenArr);
Token evaluate(Token lhs, Token rhs, int op_value);
Token pratt_parser(TokenArray* tokens, int min_bp);
int get_input(Buffer* buffer);
int mainloop();
long double my_power(long double base, int exponent);
TokenArray* lexer(Buffer* buffer);
TokenArray* tokenizer(Buffer* buffer);
void destructArray(TokenArray* tokens);
void pop_back(TokenArray* tokens);
Token peek_last(const TokenArray* tokens);
void reverseArray(TokenArray* tokens);
void printArray(const TokenArray*);
Token evaluate_tokens(Token op, Token lhs, Token rhs);
void postfix_binding_power(Token* op);
Token prefix_binding_power(Token op);
void infix_binding_power(Token* op);

#endif

#ifndef _CALC_
#define _CALC_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRECED_RAISE 5

#define DEBUG

#define ERR(str) fprintf(stderr, "Error: %s\n", str);
#define SYNTAX_ERR -25
#define INVALID_INPUT -10
#define QUIT 100
#define INITIAL_CAPACITY 128
#define ALLOC_FAILED -1

enum
{
	add       = '+',
	substruct = '-',
	multiply  = '*',
	divide    = '/',
	modulo    = '%',
	pleft     = '(',
	pright    = ')'
}; // operator value

typedef enum
{
	err = -1,
	ok  = 0,
	eof = 1
} TokenState;

typedef enum
{
	numberType   = 666,
	operatorType = 777
} TokenType;

enum
{
	addition       = 1,
	substruction   = 1,
	multiplication = 2,
	devision       = 2
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
		TokenState state;
		int preced;
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
char parse_op(Buffer* buffer);
Token next_Token(Buffer* buffer);
Token evaluate(Token lhs, Token rhs, int op_value);
Token pratt_parser(int min_preced);
int get_input(Buffer* buffer);
int mainloop();
long long my_power(int base, int exponent);
TokenArray* lexer(Buffer* buffer);
TokenArray* tokenizer(Buffer* buffer);
#endif

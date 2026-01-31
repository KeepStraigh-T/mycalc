#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRECED_RAISE 5

// #define DEBUG

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
} TokenState; // flags

typedef enum
{
	number = 666, operator= 777 } TokenType;

enum
{
	addition       = 1,
	substruction   = 1,
	multiplication = 2,
	devision       = 2
};

typedef struct StringBuffer
{
		char* ptr;
		// const int8_t* it;
		int currentIdx;
		int capacity;
		int size;
} Buffer;

typedef struct
{
		TokenType type;
		union
		{
				long long numberValue;
				char charValue;
		};
		TokenState state;
		int preced;
} token;

char peek(int offset);
bool is_number(char input);
bool is_operator(char input);
void destructor();
token parse_int();
token parse_op();
token next_token();
token evaluate(token lhs, token rhs, int op_value);
token pratt_parser(int min_preced);
int get_line();
int mainloop();
long long my_power(int base, int exponent);

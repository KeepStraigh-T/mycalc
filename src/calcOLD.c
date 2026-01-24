#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INITIAL_CAPACITY 128
#define ALLOC_FAILED -1
#define ERR(str) fprintf(stderr, "Error: %s\n", str);
#define SYNTAX_ERR -25

#define PRECED_RAISE 5

char* string_buffer; int buf_pointer = 0; 
int buf_cap = INITIAL_CAPACITY; int buf_size = 0;

enum {add = 1, substruct = 2, multiply = 3, divide = 4, modulo, pleft, pright}; //operator value
enum {err = 0, ok = 1, eof, number, operator}; //flags
enum {left_right = 1, right_left = 2};
enum {addition = 1, substruction = 1, multiplication = 2, devision = 2};
typedef struct
{
  int value;
  int flag;
  int preced;
} token;

char peek(int offset)
{
  return string_buffer[buf_pointer + offset];
}

bool is_number(char input)
{
  if(input >= '0' && input <= '9') return true;
  return false;
}

bool is_operator(char input)
{
  if(input == '+' || input == '-' || input == '*' || input == '/' || input == '%') 
    return true;
  return false;
}

void destructor(char* buffer)
{
  free(buffer);
  buf_pointer = 0;
  buf_size = 0;
  buf_cap = INITIAL_CAPACITY;
}

token parse_int()
{
  token temp = {0};
  
  int num = 0;
  int digits = 0;
  bool negative = false; //if number is negative

  if(peek(0) == '-')
  {
    negative = true;
    buf_pointer++;
  }

  for(int i = 0; is_number(peek(i)); i++)
    if(peek(i) >= '0' && peek(i) <= '9')
      digits++;
  
  for(int i = digits - 1; i >= 0; i--)
    num += (string_buffer[buf_pointer++] - '0') * pow(10, i);

  if(negative)
    num *= -1;

  temp.value = num;
  temp.flag = number; 
  
  return temp;
}

token parse_op()
{
  token temp = {0};

  if(is_operator(peek(0)))
  {
    switch (peek(0)) 
    {
      case '+':
        temp.value = add;
        temp.preced = 1;
        break;
      case '-':   
        temp.value = substruct;
        temp.preced = 1;
        break;
      case '*':
        temp.value = multiply;
        temp.preced = 2;
        break;
      case '/':
        temp.value = divide;
        temp.preced = 2;
        break;
      case '%':
        temp.value = modulo; 
        temp.preced = 2;
        break;
      default:
        break;
    }
    buf_pointer++;
    temp.flag = operator;
    return temp;
  }

  return temp; 
}

token next_token()
{
  token temp = {0};

  if(is_number(peek(0)) || (buf_pointer == 0 && peek(0) == '-') /* || (peek(0) == '(' && peek(1) == '-' && is_number(peek(2)))*/)
    temp = parse_int();
  else if(is_operator(peek(0)))
    temp = parse_op();
  else if(peek(0) == '(')
  {
    buf_pointer++;
    temp = parse_int();
  }
  else if(peek(0) == ')')
  {
    buf_pointer++;
    temp.value = pright;
  }
  else if(peek(0) == '\n')
    temp.flag = eof;
  else if(string_buffer[0] == 'q')
  {
    destructor(string_buffer);
    puts("Quitting...");
    exit(0);
  }
  else
    temp.flag = err;

  return temp;
}

token evaluate(token lhs, token rhs, int op_value)
{
  token temp = {0};

  switch (op_value) 
  {
    case add:
      temp.value = lhs.value + rhs.value;
      break;
    case substruct:
      temp.value = lhs.value - rhs.value;
      break;
    case multiply:
      temp.value = lhs.value * rhs.value;
      break;
    case divide:
      if(rhs.value != 0)
        temp.value = lhs.value / rhs.value;
      else
      {
        temp.flag = err;
        ERR("Division by 0");
      }
      break;
    case modulo:
      if(rhs.value != 0)
        temp.value = lhs.value % rhs.value;
      else
      {
        temp.flag = err;
        ERR("Division (modulo) by 0");
      }
      break;
  }
  
  temp.flag = number;
  return temp;
}

 token pratt_parser(int min_preced)
{
  static int preced_raise = 0;

  if(peek(0) == '(')
    preced_raise += PRECED_RAISE;

  token lhs = next_token(); 
  if(lhs.flag == err)
    return lhs;

  while(true)
  {
    token op = next_token();

    if(op.value == pright)
    {
      if(preced_raise > 0)
        preced_raise -= PRECED_RAISE;
      return lhs;
    }

    op.preced += preced_raise;

    if(op.flag == err)
    { 
      lhs.flag = err;
      return lhs;
    }
    else if(op.preced < min_preced || op.preced == min_preced)
    {
      buf_pointer--;
      break;  
    }

    token rhs = pratt_parser(op.preced);
    if(rhs.flag == err)
    {
      lhs.flag = err;
      return lhs;
    }
    lhs = evaluate(lhs, rhs, op.value);
  } 
  
  return lhs;
}

void get_line()
{
  putchar('>');
  for(int i = 0; 1; i++)
  {
    int c = getchar();

    if(buf_size > buf_cap)
    {
      buf_cap *= 2;
      string_buffer = realloc(string_buffer, sizeof(char) * buf_cap);
      if(string_buffer == NULL)
        exit(ALLOC_FAILED); 
    }
    if(c == '\40') // is whitespace  
      i--;
    else if(c != '\n')
    {
      string_buffer[i] = c;  
      buf_size++;      
    }    
    else //should equal \n
    {
      string_buffer[i] = '\n';
      buf_size += 2;
      return;
    }
  }
}

void mainloop()
{
  while(true)
  {
    string_buffer = malloc(sizeof(char) * INITIAL_CAPACITY);
    if(string_buffer == NULL)
    {
      ERR("Memory allocation failed");
      continue;
    }

    get_line();
    token result = pratt_parser(0);
    if(result.flag == err)
      printf("Syntax error\n");
    else 
      printf("result: %d\n", result.value);

    puts("---------------------");
    destructor(string_buffer);
  }
}

int main()
{
  puts("Type a mathemetical expression");
  puts("or type \"q\" to quit");
  mainloop();
  return 0;
} 

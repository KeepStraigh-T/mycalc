#include "../Headers/calc.h"

Token pratt_parser(TokenArray* tokenArr, int min_bp)
{
  Token lhs = next_token(tokenArr); // default is digit

  if (lhs.charValue == '(') // open parentheses
    {
      lhs = pratt_parser(tokenArr, 0);
      assert(next_token(tokenArr).charValue == ')');
    }
  else if (lhs.type == operatorType) // prefix operator
    {
      Token prefix_op = prefix_binding_power(lhs);
      Token rhs = pratt_parser(tokenArr, prefix_op.r_bp);
      lhs = evaluate_tokens(prefix_op, lhs,
                            rhs); // group two tokens (prefix op and digit)
    }

  while (true)
    {
      Token op = peek_last(tokenArr);

      if (op.type == eof)
        break;

      // if(op.type != operatorType || op.type != parentheses)
      //     return (Token) {  }
      assert(op.type == operatorType || op.type == parentheses); // if digit - abort

      // asigns infix binding powers
      infix_binding_power(&op);

      if (op.l_bp > 0 && op.r_bp > 0) // infix operator
        {
          if (op.l_bp < min_bp)
            break;

          next_token(tokenArr);
          Token rhs = pratt_parser(tokenArr, op.r_bp);

          lhs = evaluate_tokens(op, lhs, rhs);
          continue;
        }

      // asigns postfix binding powers
      // postfix_binding_power(&op);
      //
      // if(op.l_bp > 0 && op.r_bp == 0)
      // {
      // 	if(op.l_bp < min_bp)
      // 		break;
      //
      // 	next_token(tokenArr);
      //
      // 	Token rhs = {0};
      // 	lhs       = evaluate_tokens(op, lhs, rhs);
      // 	continue;
      // }
      break;
    }
  return lhs;
}

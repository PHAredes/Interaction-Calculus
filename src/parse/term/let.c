#include <string.h>
#include <stddef.h>
#include "../../parse.h"

// Parse a let expression (syntax sugar for application of lambda)
void parse_term_let(Parser* parser, uint32_t loc) {
  expect(parser, "!", "for let expression");

  char* name = parse_name(parser);
  expect(parser, "=", "after name in let expression");

  // Allocate nodes for the application and lambda
  uint32_t app_node = ic_alloc(parser->ic, 2);
  uint32_t lam_node = ic_alloc(parser->ic, 1);

  // Set up the application structure
  uint32_t fun_loc = app_node;     // lambda function
  uint32_t arg_loc = app_node + 1; // value

  // Create variable term for the lambda parameter
  bind_var(parser, name, ic_make_term(VAR, 0, lam_node));

  // Parse the value into arg_loc
  parse_term(parser, arg_loc);

  expect(parser, ";", "after value in let expression");

  // Parse the body into lam_node
  parse_term(parser, lam_node);

  // Store the lambda at fun_loc
  store_term(parser, fun_loc, LAM, 0, lam_node);

  // Store the application at loc
  store_term(parser, loc, APP, 0, app_node);
}

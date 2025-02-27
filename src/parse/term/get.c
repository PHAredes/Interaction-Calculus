#include <stddef.h>
#include "../../parse.h"
#include "../../memory.h"

// Parse a sigma type elimination
void parse_term_get(Parser* parser, uint64_t loc) {
  expect(parser, "![", "for sigma elimination");

  char* name1 = parse_name(parser);
  expect(parser, ",", "between names in sigma elimination");

  char* name2 = parse_name(parser);
  expect(parser, "]", "after names in sigma elimination");
  expect(parser, "=", "after names in sigma elimination");

  uint64_t get_node = alloc_term(3);
  uint64_t val_loc = get_node;
  uint64_t bod_loc = get_node + 1;

  parse_term(parser, val_loc);
  expect(parser, ";", "after pair in sigma elimination");

  Term fst_var = make_term(VAR, 0, get_node + 2);
  Term snd_var = make_term(VAR, 0, get_node + 2);
  bind_var(parser, name1, fst_var);
  bind_var(parser, name2, snd_var);

  parse_term(parser, bod_loc);
  store_term(loc, GET, 0, get_node);
}

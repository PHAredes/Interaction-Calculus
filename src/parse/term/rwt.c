#include <stddef.h>
#include "../../parse.h"
#include "../../memory.h"

// Parse an equality elimination
void parse_term_rwt(Parser* parser, uint64_t loc) {
  expect(parser, "%", "for equality elimination");

  uint64_t rwt_node = alloc_term(2);
  uint64_t eq_loc = rwt_node;
  uint64_t bod_loc = rwt_node + 1;

  parse_term(parser, eq_loc);
  expect(parser, ";", "after equality proof");

  parse_term(parser, bod_loc);
  store_term(loc, RWT, 0, rwt_node);
}

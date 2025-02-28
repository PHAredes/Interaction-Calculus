#include <stddef.h>
#include "../../parse.h"
#include "../../memory.h"

// Parse an empty type elimination
void parse_term_efq(Parser* parser, uint64_t loc) {
  if (check_utf8(parser, 0xC2, 0xAC)) {
    consume_utf8(parser, 2);

    uint64_t efq_node = alloc(1);
    parse_term(parser, efq_node);

    store_term(loc, EFQ, 0, efq_node);
  } else {
    parse_error(parser, "Expected '¬' for empty type elimination");
  }
}

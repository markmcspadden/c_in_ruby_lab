#include "ruby.h"
#include <stdlib.h>
#include <string.h>

static VALUE c_to_words(VALUE self) {  
  // TODO: Downcase and remove puncuation
  return rb_str_split(self," ");
}

VALUE CFullTextSearch;

void Init_c_full_text_search() {
  CFullTextSearch = rb_define_module("CFullTextSearch");
  rb_define_method(CFullTextSearch, "to_words", c_to_words, 0);
}
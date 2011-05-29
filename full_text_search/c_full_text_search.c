#include "ruby.h"
#include "re.h"
#include <stdlib.h>
#include <string.h>

static VALUE
custom_rb_str_split_m(str)
    VALUE str;
{
    // VALUE limit;
    // int awk_split = Qfalse;
long beg, end; //, i = 0;
   
    // VALUE result, tmp;
    VALUE result;

    // if (rb_scan_args(argc, argv, "02", &spat, &limit) == 2) {
	// lim = NUM2INT(limit);
	// if (lim <= 0) limit = Qnil;
	// else if (lim == 1) {
	//     if (RSTRING(str)->len == 0)
	// 	return rb_ary_new2(0);
	//     return rb_ary_new3(1, str);
	// }
	// limit = Qnil;
	// i = 1;
    // }

	//     if (NIL_P(spat)) {
	// if (!NIL_P(rb_fs)) {
	//     spat = rb_fs;
	//     goto fs_set;
	// }
	// awk_split = Qtrue;
	//     }
	//     else {
      // fs_set:
	// if (TYPE(spat) == T_STRING && RSTRING(spat)->len == 1) {
	// 	puts("IF");
	//     if (RSTRING(spat)->ptr[0] == ' ') {
	// 	puts("IF IF");
	//	awk_split = Qtrue;
	//     }
	//     else {
	// 	puts("IF ELSE");
	// 	spat = rb_reg_regcomp(rb_reg_quote(spat));
	//     }
	// }
	// else {
	// 	puts("ELSE");
	//     spat = get_pat(spat, 1);
	// }
    // }

    result = rb_ary_new();
    beg = 0;
    // if (awk_split) {
	char *ptr = RSTRING(str)->ptr;
	long len = RSTRING(str)->len;
	char *eptr = ptr + len;
	int skip = 1;

	for (end = beg = 0; ptr<eptr; ptr++) {
	    if (skip) {
		if (ISSPACE(*ptr)) {
		    beg++;
		}
		else {
		    end = beg+1;
		    skip = 0;
		    // if (!NIL_P(limit) && lim <= i) break;
		}
	    }
	    else {
		if (ISSPACE(*ptr)) {
		    rb_ary_push(result, rb_str_substr(str, beg, end-beg));
		    skip = 1;
		    beg = end + 1;
		    // if (!NIL_P(limit)) ++i;
		}
		else {
		    end++;
		}
	    }
	}
    // }
	//     else {
	// long start = beg;
	// long idx;
	// int last_null = 0;
	// struct re_registers *regs;
	// 
	// while ((end = rb_reg_search(spat, str, start, 0)) >= 0) {
	//     regs = RMATCH(rb_backref_get())->regs;
	//     if (start == end && BEG(0) == END(0)) {
	// 	if (!RSTRING(str)->ptr) {
	// 	    rb_ary_push(result, rb_str_new("", 0));
	// 	    break;
	// 	}
	// 	else if (last_null == 1) {
	// 	    rb_ary_push(result, rb_str_substr(str, beg, mbclen2(RSTRING(str)->ptr[beg],spat)));
	// 	    beg = start;
	// 	}
	// 	else {
	// 	    start += mbclen2(RSTRING(str)->ptr[start],spat);
	// 	    last_null = 1;
	// 	    continue;
	// 	}
	//     }
	//     else {
	// 	rb_ary_push(result, rb_str_substr(str, beg, end-beg));
	// 	beg = start = END(0);
	//     }
	//     last_null = 0;
	// 
	//     for (idx=1; idx < regs->num_regs; idx++) {
	// 	if (BEG(idx) == -1) continue;
	// 	if (BEG(idx) == END(idx))
	// 	    tmp = rb_str_new5(str, 0, 0);
	// 	else
	// 	    tmp = rb_str_substr(str, BEG(idx), END(idx)-BEG(idx));
	// 	rb_ary_push(result, tmp);
	//     }
	//     if (!NIL_P(limit) && lim <= ++i) break;
	// }
	//     }
    // if (RSTRING(str)->len > 0 && (!NIL_P(limit) || RSTRING(str)->len > beg || lim < 0)) {
	// if (RSTRING(str)->len == beg)
	//     tmp = rb_str_new5(str, 0, 0);
	// else
	//     tmp = rb_str_substr(str, beg, RSTRING(str)->len-beg);
	// rb_ary_push(result, tmp);
	rb_ary_push(result, rb_str_substr(str, beg, RSTRING(str)->len-beg));
    // }
	//     if (NIL_P(limit) && lim == 0) {
	// while (RARRAY(result)->len > 0 &&
	//        RSTRING(RARRAY(result)->ptr[RARRAY(result)->len-1])->len == 0)
	//     rb_ary_pop(result);
	//     }

    return result;
}

VALUE
custom_rb_str_split(str)
    VALUE str;
{


    StringValue(str);
    return custom_rb_str_split_m(str);
}




static VALUE c_to_words(VALUE self) {  
  // TODO: Downcase and remove puncuation
  // return custom_rb_str_split(self);
  return custom_rb_str_split_m(self);
}

VALUE CFullTextSearch;

void Init_c_full_text_search() {
  CFullTextSearch = rb_define_module("CFullTextSearch");
  rb_define_method(CFullTextSearch, "to_words", c_to_words, 0);
}
#include "ruby.h"
#include "re.h"
#include <stdlib.h>
#include <string.h>

static VALUE
custom_rb_str_split_m(str)
    VALUE str;
{
	long beg, end;
   
    VALUE result;

    result = rb_ary_new();
    beg = 0;

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

    rb_ary_push(result, rb_str_substr(str, beg, RSTRING(str)->len-beg));

    return result;
}

static VALUE c_to_words(VALUE self) {  
    // TODO: Downcase and remove puncuation
    return custom_rb_str_split_m(self);
}

static VALUE c_document_frequency(VALUE self, VALUE documents) { 
    VALUE result;

	double t_count;
	t_count = 0;

	int d_count = RARRAY(documents)->len;
	
	VALUE *documents_arr = RARRAY(documents)->ptr;
	
	int i;
	for(i=0;i<d_count;i++) {
		int found=0;
		
		VALUE words = custom_rb_str_split_m(documents_arr[i]);
		int words_count = RARRAY(words)->len;
		// printf("Word Count: %d\n", words_count);
		
		VALUE *words_arr = RARRAY(words)->ptr;
		
		int j;
		for(j=0;j<words_count;j++) {
			// printf("j: %d\n", j);
			if(rb_str_cmp(words_arr[j], self)==0) {
				found = 1;
				break;
			}
		}
		
		if(found==1) {
			t_count++;
		}
	}

	// printf("t_count: %f \n d_count: %d\n", t_count, d_count);

	result = rb_float_new(t_count/d_count);
    return result;
}

VALUE CFullTextSearch;

void Init_c_full_text_search() {
    CFullTextSearch = rb_define_module("CFullTextSearch");
    rb_define_method(CFullTextSearch, "to_words", c_to_words, 0);
    rb_define_method(CFullTextSearch, "document_frequency", c_document_frequency, 1);
}
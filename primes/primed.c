#include "ruby.h"
#include <stdlib.h>
#include <math.h>
 
VALUE Primed;
 
VALUE method_prime(VALUE obj, VALUE args)
{
	register uint64_t n;
	n = NUM2INT(obj);
	if (n == 2)
		return Qtrue;
	if ((n & 1) == 0)
		return Qfalse;
 
	register uint64_t sqrt_n = ((uint64_t)sqrt(n)) + 1;
	register uint64_t i=3;
	for (i; i<= sqrt_n; i+=2) {
		if (n % i == 0)
			return Qfalse;
	}
	return Qtrue;
}
 
void Init_primed() {
	Primed = rb_define_module("Primed");
	rb_define_method(Primed, "prime?", method_prime, -2);
}
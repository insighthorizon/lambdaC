#include <stdio.h>
#include <stdarg.h>

/* black magic to unleash the demons */
typedef struct t_fun t_fun;
typedef struct t_fun {
    t_fun (*fun)(t_fun);
} t_fun;

/* 'pure' function definitions */
// def identity = λx.x
t_fun identity(t_fun x){
    return x;
}
// def self_apply = λs.(s s)
t_fun self_apply(t_fun s){
    return s.fun  (s);
}
// def apply = λfunc.λarg.(func arg)
t_fun apply(t_fun func){
    return func;
}
// def identity2 = λx.((apply identity) x)
t_fun identity2(t_fun x){
    return (
	apply
	((t_fun){identity}) // takes apply
	.fun(x) // applyes it to x
	); // result of evaluation is returned
}
// def self_apply2 = λs.((apply s) s)
t_fun self_apply2(t_fun s) {
    return (
	apply
	(s) // takes s
	.fun(s) // and applies it to s
	); // result of evaluation is returned
}
// def select_first = λfirst.λsecond.first
t_fun select_first(t_fun first){
	
}



// TEST CODE
int main(int argc, char *argv[]) {
    printf("Expecting: %p\nReceived:  %p\n", (void *)

	   
	   /* plug expected evaluation result in here >>> */ identity /* <<< */, (void *)
	   
	   /* ___EVALUATION OF FUNCTIONS down here:___*/
	   identity
	   ((t_fun){identity})
//	   .fun((t_fun){self_apply})

	   /* ___EVALUATION OF FUNCTIONS END___*/

	   
    .fun );
    return 0;
}

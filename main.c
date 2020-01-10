#include <stdio.h>
#include <stdarg.h>
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

/* black magic to unleash the demons */
typedef struct t_fun t_fun;
typedef struct t_fun {
    t_fun (*fun)(t_fun, ...);
} t_fun;

/* 'pure' function definitions */
// def identity = λx.x
t_fun identity(t_fun x){
    return x; }
// def self_apply = λs.(s s)
t_fun self_apply(t_fun s){
    return s.fun  (s); }
// def apply = λfunc.λarg.(func arg)
t_fun apply(t_fun func, t_fun arg){
    return func.fun (arg); }
// def identity2 = λx.((apply identity) x)
t_fun identity2(t_fun x){
    return
	apply
	((t_fun){identity}, // takes apply
	x // applyes it to x
	); // result of evaluation is returned
}
// def self_apply2 = λs.((apply s) s)
t_fun self_apply2(t_fun s) {
    return
	apply
	(s, // takes s
	s // and applies it to s
	); // result of evaluation is returned
}
// def select_first = λfirst.λsecond.first
t_fun select_first(t_fun first, t_fun second){
    return first; }
// def select_second = λfirst.λsecond.secod
t_fun select_second(t_fun first, t_fun second){
    return second; }
// def make_pair = λfirst.λsecond.λfunc.((func first) second) (* λfunc.((func first) second)
t_fun make_pair(t_fun first, t_fun second, t_fun func) {
    return func.fun(first, second); }
// def true = select_first
t_fun true(t_fun first, t_fun second){
    return first; }
//   def false = select second
t_fun false(t_fun first, t_fun second){
    return second; }
// def cond = λe1.λe2.λc.((c e1) e2) (* identical to make_pair )*
t_fun cond(t_fun e1, t_fun e2, t_fun c) {
    return c.fun(e1, e2); }
// def not = ((x false) true)
t_fun not(t_fun x){
    return x.fun((t_fun){false}, (t_fun){true}); }
// def and = λx.λy.((x y) false)
t_fun and(t_fun x, t_fun y){
    return x.fun(y, (t_fun){false}); }
// def or = λx.λy.((x true) y)
t_fun or(t_fun x, t_fun y){
    return x.fun((t_fun){true}, y); }

// def zero = identity
t_fun zero(t_fun s){
    return s; }
// def succ = λn.λs.((s false) n)
t_fun succ(t_fun n, t_fun s){
    return s.fun((t_fun){false}, n); }
// def iszero = λn.(n true)
t_fun iszero(t_fun n){
    return n.fun((t_fun){true}); }

t_fun one(t_fun s){
    return succ((t_fun){zero}, s); }
t_fun two(t_fun s){
    return succ((t_fun){one}, s); }
t_fun three(t_fun s){
    return succ((t_fun){two}, s); }


// def pred = λn.(((iszero n) zero) (n select_second))
t_fun pred(t_fun n){
    return iszero(n).fun( (t_fun){zero}, n.fun((t_fun){select_second}) ); }
/* def add2 f x y =
                if iszero y
		then x
		else f f (succ x) (pred y) */

t_fun add2(t_fun f, t_fun x, t_fun y){ // FAIL: Cannot have run-time succ function (pred works, because n contains reference to preexisting predecessor, but succ constructs completely new number)
    return cond(x, f.fun(f, succ(x,dsgasdg ), pred(y)), iszero(y));
}
// def add x y = add2 add2
t_fun add(t_fun x, t_fun y){
    return add2((t_fun){add2}, x, y); }


// TEST CODE
int main(int argc, char *argv[]) {
    void * result = (void *)
	/* ===EVALUATION OF FUNCTIONS down here:=== */
	
	pred
	((t_fun){zero})

	/* ===EVALUATION OF FUNCTIONS END=== */
	.fun;
    void * expected = (void *)

	/* plug expected evaluation result in here >>> */ zero /* <<< */;
    
    printf("Expecting: %p\nReceived:  %p\n", expected, result);
    printf("===============\n");
    if (expected == result)
	printf("SUCCESS\n");
    else
	printf("FAIL\n");
    printf("===============\n");    

    return 0;
}

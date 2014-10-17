/* Write a recursive version and a version with loops in Javascript.

1. function iterator: takes a function f and a nat n and
returns the nth iterate of f. 

 iterate: [[any? -> any?] nat?] -> [any? -> any?]

a. (iterate f 0) => a function equal to the identity function (lambda (x) x).
b. (iterate f n+1) => (f (iterate f n)), for n : nat?

Examples:
 ((iterate add1 3) 2) => 5
 ((iterate sqr 2) 3) => 81
 ((iterate D) 2)  => a function equivalent to the 2nd derivative 
  (D is the derivative function we did in class). 
*/
//=======================================================================================

//This is the recursive version of iterate
var iterate = function (f, n) {
	var iterator = function (x) {
		var iterateHelper = function (x, n) {
			if (n == 0) {
				return x;
			} else {
				return iterateHelper(f(x), n-1);
			}
		}
		return iterateHelper (x, n);
	}
	return iterator;
}

//=======================================================================================
//This is the loop version of iterate i.e non-recursive
var iterateLoop = function (f, m) {
	var iterator = function (x) {
		var n = m;
		while (n > 0) {
			x = f(x);
			n = n - 1;
		}
		return x;
	}
	return iterator;
}

//=======================================================================================

//Following are for testing the iterate and iterateLoop

var add1 = function (x) {
	return x + 1;
}

var sqr = function (x) {
	return x*x;
}

var main = function () {

	document.write("<p>======================================================================</p>");

	document.write("<p><h4>Testing recursive version of iterate: [[any -> any] nat] -> [any -> any]</h4></p>");
	document.write("<p>iterate(add1, 3)(2) = ");
	document.write(iterate(add1, 3)(2));

	document.write("<p>iterate(add1, 0)(10) = ");
	document.write(iterate(add1, 0)(10));

	document.write("<p>iterate(sqr, 2)(3) = ");
	document.write(iterate(sqr, 2)(3));

	document.write("<p>iterate(sqr, 1)(5) = ");
	document.write(iterate(sqr, 1)(5));

	document.write("<p>======================================================================</p>");

	document.write("<p><h4>Testing loop version of iterate: [[any -> any] nat] -> [any -> any]</h4></p>");
	document.write("<p>iterateLoop(add1, 3)(2) = ");
	document.write(iterateLoop(add1, 3)(2));

	document.write("<p>iterateLoop(add1, 0)(10) = ");
	document.write(iterateLoop(add1, 0)(10));

	document.write("<p>iterateLoop(sqr, 2)(3) = ");
	document.write(iterateLoop(sqr, 2)(3));

	document.write("<p>iterateLoop(sqr, 1)(5) = ");
	document.write(iterateLoop(sqr, 1)(5));

	document.write("<p>======================================================================</p>");
	
}

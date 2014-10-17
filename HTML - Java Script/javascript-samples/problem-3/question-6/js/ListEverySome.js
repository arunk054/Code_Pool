/* 6.  Define functions list-every and list-some that takes a
predicate p and a list ls, and returns #t if every
(respectively, some) element of ls satisfies p, #f
otherwise.  Be careful and rationalize about the choice of
your definition for the base case (when ls is empty).*/

//Here we only define the recursive versions of listSome and listEvery
//Following are the signature and definitions
//==============================================================

//The function takes in the predicate as the first parameter,
//The predicate is basically a function which returns a boolean, based on the
// parameter passed to the predicate

//The idea here is to call recursively, with initial value of accumulator
//being 'Empty-List.


//listEvery : [[any -> boolean] List] -> boolean OR 'Empty-List
//---------------------------------------------------------------
var listEvery = function (p, ls) {
	var f = function (ls, a) {
		if (ls.isNil()) {
			return a;
		} else if (!p(ls.hd())) {
			return false;
		} else {
			return f(ls.tl(), true);
		}
	}
	return f(ls, "Empty-List");
}


//listSome : [[any -> boolean] List] -> boolean OR 'Empty-List
//---------------------------------------------------------------

var listSome = function (p, ls) {
	var f = function (ls, a) {
		if (ls.isNil()) {
			return a;
		} else if (p(ls.hd())) {
			return true;
		} else {
			return f(ls.tl(), false);
		}
	}
	return f(ls, "Empty-List");
}

//=======================================================================================

//Following methods are for testing the listEvery and listSome functon

var printList = function(ls) {
	document.write("\'(");
	document.write (ls.display());
	document.write(") ");
}

var execAndPrint = function(ls, f, s) {
	document.write ("<h3><p>( "+s+" isNumber ");
	printList(ls);
	document.write (" ) = " + f(isNumber, ls));
	document.write ("</h3>");
}

var main = function () {
	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing recursive version of listEvery : [[any -> boolean] List] -> boolean OR 'Empty-List</h3></p>");
	var ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));

	execAndPrint(ls1, listEvery, "listEvery");

	ls1 = cons (1,cons (2,cons ('a', cons (4, Nil))));
	execAndPrint(ls1, listEvery, "listEvery");

	ls1 = Nil;
	execAndPrint(ls1, listEvery, "listEvery");

	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing recursive version of listSome : [[any -> boolean] List] -> boolean OR 'Empty-List</h3></p>");

	ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	execAndPrint(ls1, listSome, "listSome");

	ls1 = cons (1,cons (2,cons ('a', cons (4, Nil))));
	execAndPrint(ls1, listSome, "listSome");

	ls1 = cons ('c',cons ('a', cons ('b', Nil)));
	execAndPrint(ls1, listSome, "listSome");

	ls1 = Nil;
	execAndPrint(ls1, listSome, "listSome");

	document.write("<p>====================================================================================</p>");
}

//Function to check if the given identifier is a number or not
// isNumber : [any] -> boolean
//------------------------------
var isNumber = function(x) 
{ 
  return ( (x != null) && (typeof(x) === typeof(1.0)) && isFinite(x) );
}

//==========================================================
// Following is the definition of List from List.js
//==========================================================

var instantiate = function(o) {
    var F = function() {};
    F.prototype = o;
    return new F();
};


// ======
//   List
//   ----
// A List is either Nil or a  Pair

// List = Nil + Pair

var List = new Object();

List.isList = function() {
    return (this.isNil() || this.isPair());
}

// ======
//   Nil
// ======

var Nil = instantiate(List);

Nil.hd = function() {
    alert("Nil.hd -> error");
};

Nil.tl = function() {
    alert("Nil.tl -> error");
};

// =============
// Pair
// =============

var Pair = instantiate(List);

// cons : [Any List] -> Pair
var cons = function(h,t) {
    var a = instantiate(Pair);
    a.hd = function() {return h;};
    a.tl = function() {return t;};
    return a;
};


// isNil
// ------

Nil.isNil = function() {
    return true;
};

Pair.isNil = function() {
    return false;
};

// isPair
// ------
Nil.isPair = function() {
    return false;
};

Pair.isPair = function() {
    return true;
};

//Functions to display the contents of the list
Nil.display = function() {
    return "";
};

Pair.display = function() {
	var s =  this.hd() + " " + this.tl().display();
    return s;
};



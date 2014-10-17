/*3. Design the function rember-all (remberAll in Javascript)
that takes a list ls and an element x and returns a new list
which is equivalent to the old list except that all
occurrences of the elementx are removed.*/

//We first define the recursive version of rememberAll

//rememberAll : [List any] -> List
//----------------------------------
rememberAll = function (ls, x) {

	if (ls.isNil()) {
		return Nil;
	} else if (ls.hd() != x) {
		return cons(ls.hd(), rememberAll(ls.tl(), x));
	} else {
		return rememberAll(ls.tl(),x);
	}
}

//======================================================================================

//We now define the iterative version of rememberAll
//Here the logic is similar to the scheme version, but instead of list-ref we convert the list 
//to array and check each element of the array.

//rememberAllLoop : [List any] -> List
//---------------------------------------
rememberAllLoop = function (ls, x) {
	var count = ls.length() - 1;
	var arr = ls.toArray();
	var lsRet = Nil;
	for (var i = count; i >= 0; i--) {	
		if (arr[i] != x) {
			lsRet = cons (arr[i], lsRet);
		}
	}
	return lsRet;
}

//=======================================================================================

//Following methods are for testing the rememberAll functon

var printList = function(ls) {
	document.write("\'(");
	document.write (ls.display());
	document.write(") ");
}

var execAndPrint = function(ls1, x, f, s) {
	document.write ("<h3><p>( "+s+" ");
	printList(ls1);
	document.write (" "+x+" )");
	document.write (" = ");
	printList(f(ls1,x));
	document.write ("</h3>");
}

var main = function () {
	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing recursive version of rememberAll : [List any] -> List</h3></p>");
	var ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	var x = 3;

	execAndPrint(ls1, x, rememberAll, "rememberAll");

	ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	x = 8;
	execAndPrint(ls1, x, rememberAll, "rememberAll");

	ls1 = cons (1,cons (2,cons (3, cons (2, Nil))));
	x = 2;
	execAndPrint(ls1, x, rememberAll, "rememberAll");

	ls1 = cons (3,cons (3,cons (3, cons (3, Nil))));
	x = 3;
	execAndPrint(ls1, x, rememberAll, "rememberAll");

	document.write("<p>==================================================================================</p>");

	document.write("<p><h3>Testing iterative (non-recursive) version of rememberAll : [List any] -> List</h3></p>");
	var ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	var x = 3;

	execAndPrint(ls1, x, rememberAllLoop, "rememberAllLoop");

	ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	x = 8;
	execAndPrint(ls1, x, rememberAllLoop, "rememberAllLoop");

	ls1 = cons (1,cons (2,cons (3, cons (2, Nil))));
	x = 2;
	execAndPrint(ls1, x, rememberAllLoop, "rememberAllLoop");

	ls1 = cons (3,cons (3,cons (3, cons (3, Nil))));
	x = 3;
	execAndPrint(ls1, x, rememberAllLoop, "rememberAllLoop");

	document.write("<h3><p>=====================================================================</p>");

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

// Length
// ------
Nil.length = function() {
    return 0;
};

Pair.length = function() {
    return 1 + this.tl().length();
};

// toArray
// -------

Nil.toArray = function() {
    return [];
};

Pair.toArray = function() {
    var s =  [];
    s = this.tl().toArray();
    s.unshift(this.hd());
    return s; 
};


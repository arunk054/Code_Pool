/* 5. Define functions list-sum (and list-product, respectively) 
recursively that sum (and multiply, respectively) all the elements of a list of numbers.
Carefully choose the base cases (when ls is empty). 
*/

//Here we only define the recursive versions of listSum and listProduct
//Following are the signature and definitions
//==============================================================

//listSum : (list-of numbers) -> Number OR 'Empty-List
//--------------------------------------------------------
listSum = function (ls) {
	var f = function (ls, a) {
		if (ls.isNil()){
			return a;
		} else {
			return f(ls.tl(), a+ls.hd());
		}
	}
	if (ls.isNil()){
		return "Empty-List";
	} else {
		return f(ls, 0)
	}
}


//listProduct : (list-of numbers) -> Number OR 'Empty-List
//--------------------------------------------------------
listProduct = function (ls) {
	var f = function (ls, a) {
		if (ls.isNil()){
			return a;
		} else {
			return f(ls.tl(), a*ls.hd());
		}
	}
	if (ls.isNil()){
		return "Empty-List";
	} else {
		return f(ls, 1)
	}
}

//=======================================================================================

//Following methods are for testing the listSum and listProduct functon

var printList = function(ls) {
	document.write("\'(");
	document.write (ls.display());
	document.write(") ");
}

var execAndPrint = function(ls, f, s) {
	document.write ("<h3><p>( "+s+" ");
	printList(ls);
	document.write (" ) = " + f(ls));
	document.write ("</h3>");
}

var main = function () {
	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing recursive version of listSum : List -> Number</h3></p>");
	var ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));

	execAndPrint(ls1, listSum, "listSum");
	
	ls1 = Nil;
	execAndPrint(ls1, listSum, "listSum");

	ls1 = cons (-1,cons (2,cons (-3, cons (4, Nil))));
	execAndPrint(ls1, listSum, "listSum");


	document.write("<p>====================================================================================</p>");
	document.write("<p><h3>Testing recursive version of listProduct : List -> Number</h3></p>");

	ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	execAndPrint(ls1, listProduct, "listProduct");

	ls1 = Nil;
	execAndPrint(ls1, listProduct, "listProduct");

	ls1 = cons (2,cons (-3, cons (1, Nil)));
	execAndPrint(ls1, listProduct, "listProduct");

	document.write("<p>====================================================================================</p>");

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






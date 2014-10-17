//7. Define the function list-reduce which takes a seed value,
//a, binary function p, and a list ls of values and
//reduces the list to a value according to the following pattern.

//Also rewrite the problems 5 and 6 using list-reduce.

//(list-reduce seed p '()) = seed
//
//(list-reduce seed p '(a b c)) = (p a (p b (p c seed)))

//We define the recursive version of list-reduce
//Following is the signature and definition
//==============================================================


//listReduce : [any [[any any] -> any] List] -> any
//-----------------------------------------------------
var listReduce = function (a, p, ls) {

	if (ls.isNil()) {
		return a;
	} else {
		return p(ls.hd(), listReduce(a,p, ls.tl()));
	}

}

//Now rewrite the problems 5 and 6 using listReduce.

//First we define listSum and listProduct using listReduce

//But before that we need to define the binary functions + and *

//plus : [number number] -> number
var plus = function (x, y) {
	return x + y;
}

//mul : [number number] -> number
var mul = function (x,y){
	return x * y;
}

//listSum : (list-of numbers) -> Number OR 'Empty-List
//--------------------------------------------------------
listSum = function (ls) {
	if (ls.isNil()){
		return "Empty-List";
	} else {
		return listReduce(0, plus, ls);
	}
}


//listProduct : (list-of numbers) -> Number OR 'Empty-List
//--------------------------------------------------------
listProduct = function (ls) {
	if (ls.isNil()){
		return "Empty-List";
	} else {
		return listReduce(1, mul, ls);
	}
}

//We now define listEvery and listSome using listReduce

//listEvery : [[any -> boolean] List] -> Boolean OR 'Empty-List
//-------------------------------------------------------------------

var listEvery = function (p, ls) {
	if (ls.isNil())
		return "Empty-List";
	else {
		return listReduce(true, andPred(p), ls);
	}

}

var andPred = function (p) {
	return function (x, y) {
		return p(x) && y;
	}
}


//listSome : [[any -> boolean] List] -> Boolean OR 'Empty-List
//-------------------------------------------------------------------

var listSome = function (p, ls) {
	if (ls.isNil())
		return "Empty-List";
	else {
		return listReduce(false, orPred(p), ls);
	}

}

var orPred = function (p) {
	return function (x, y) {
		return p(x) || y;
	}
}

//=======================================================================================

//Following methods are for testing the listReduce and listEvery / listSome functons using listReduce

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

var execAndPrintLR = function (ls, a, p, s) {
	document.write ("<h3><p>( listReduce "+ a + " "+s+ " ");
	printList(ls);
	document.write (" ) = " + listReduce(a, p, ls));
	document.write("</h3>");

}

var execAndPrintSP = function(ls, f, s) {
	document.write ("<h3><p>( "+s+" ");
	printList(ls);
	document.write (" ) = " + f(ls));
	document.write ("</h3>");
}

//some binary functions for testing listReduce

//myAnd : [boolean boolean] -> boolean
var myAnd = function (x, y) {
	return x && y;
}

var main = function () {

	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing recursive version of listReduce : [any [[any any] -> any] List] -> any</h3></p>");

	var ls1 = cons (1, cons (2, cons (3, Nil)));

	execAndPrintLR(ls1, 1, plus, "plus");


	ls1 = Nil;
	execAndPrintLR(ls1, 1, plus, "plus");

	ls1 = cons (true, cons (false, cons (true, Nil)));
	execAndPrintLR(ls1, true, myAnd, "and");

	ls1 = cons (true, cons (true, cons (true, Nil)));
	execAndPrintLR(ls1, true, myAnd, "and");
	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing listSum function implemented using listReduce</h3></p>");
	var ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));

	execAndPrintSP(ls1, listSum, "listSum");
	
	ls1 = Nil;
	execAndPrintSP(ls1, listSum, "listSum");

	ls1 = cons (-1,cons (2,cons (-3, cons (4, Nil))));
	execAndPrintSP(ls1, listSum, "listSum");


	document.write("<p>====================================================================================</p>");
	document.write("<p><h3>Testing listProduct function implemented using listReduce</h3></p>");

	ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	execAndPrintSP(ls1, listProduct, "listProduct");

	ls1 = Nil;
	execAndPrintSP(ls1, listProduct, "listProduct");

	ls1 = cons (2,cons (-3, cons (1, Nil)));
	execAndPrintSP(ls1, listProduct, "listProduct");

	document.write("<p>====================================================================================</p>");


	document.write("<p><h3>Testing listEvery function implemented using listReduce</h3></p>");

	ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	execAndPrint(ls1, listEvery, "listEvery");

	ls1 = cons (1,cons (2,cons ('a', cons (4, Nil))));
	execAndPrint(ls1, listEvery, "listEvery");

	ls1 = Nil;
	execAndPrint(ls1, listEvery, "listEvery");

	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing listSome function implemented using listReduce</h3></p>");

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





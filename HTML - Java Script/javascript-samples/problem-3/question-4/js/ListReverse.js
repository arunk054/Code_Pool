//4. Define a function list-reverse that takes a list and reverses
//it. [Hint: use an accumulator.]

//Here we only define the recursive version of listReverse
//Following is the signature and definition
//==============================================================


//listReverse : List -> List
//-------------------------------
listReverse = function (ls) {
	var f = function (ls, lsAcc) {
		if (ls.isNil()) {
			return lsAcc;
		} else {
			return f(ls.tl(), cons(ls.hd(),lsAcc));
		}
	}
	return f(ls, Nil);
}

//=======================================================================================

//Following methods are for testing the listReverse functon

var printList = function(ls) {
	document.write("\'(");
	document.write (ls.display());
	document.write(") ");
}

var execAndPrint = function(ls) {
	document.write ("<h3><p>( listReverse ");
	printList(ls);
	document.write (" ) = ");
	printList(listReverse(ls));
	document.write ("</h3>");
}

var main = function () {
	document.write("<p>====================================================================================</p>");

	document.write("<p><h3>Testing recursive version of listReverse : List -> List</h3></p>");
	var ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));

	execAndPrint(ls1);
	
	ls1 = cons (5, cons (4,cons (3,cons (2, cons (1, Nil)))));
	execAndPrint(ls1);

	ls1 = cons (1,cons (2,cons (1, cons (2, Nil))));
	execAndPrint(ls1);


	ls1 = Nil;
	execAndPrint(ls1);

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


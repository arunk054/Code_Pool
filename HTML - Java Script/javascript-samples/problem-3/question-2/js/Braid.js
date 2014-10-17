/*;2. Design the function braid.  Braid takes two lists ls1 and
;ls2 and returns a new list whose elements are alternately
;taken from ls1 and ls2.  Elements remaining from the longer
;list after braiding are copied without change.  Remember to
;mention the signature of braid.
;
;Eg., 
;
;(braid '(1 2 3 4) '(a b)) => (1 a 2 b 3 4)
;(braid '(1 2) '(a b c d)) => (1 a 2 b c d)
*/

//We only define the recursive version of braid

//Following is the signature of braid
//=====================================

// braid : [(list-of any) (list-of any)] -> (list-of any)
//---------------------------------------------------------

var braid = function (ls1, ls2) {
	if (ls1.isNil() && ls2.isNil()) {
		return Nil;
	}else if (!ls1.isNil() && !ls2.isNil()) {
		return cons(ls1.hd(),cons(ls2.hd(),braid(ls1.tl(), ls2.tl())));
	}else if (!ls1.isNil()){
		return cons(ls1.hd(),braid(ls1.tl(), Nil));
	}else {
		return cons(ls2.hd(),braid(Nil, ls2.tl()));
	}
}

//=======================================================================================

//Following methods are for testing the braid functon

var printList = function(ls) {
	document.write("\'(");
	document.write (ls.display());
	document.write(") ");
}


var main = function () {
	document.write("<p>======================================================================</p>");

	document.write("<p><h3>Testing recursive version of braid : [(list-of any) (list-of any)] -> (list-of any)</p>");
	var ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	var ls2 = cons('a', cons ('b', Nil));
	document.write ("<h3><p>braid ");
	printList(ls1);
	printList(ls2);
	document.write (" = ");
	printList(braid(ls1,ls2));

	ls1 = cons (1, cons (2, Nil));
	ls2 = cons ('a',cons ('b',cons ('c', cons ('d', Nil))));
	document.write ("<p>braid ");
	printList(ls1);
	printList(ls2);
	document.write (" = ");
	printList(braid(ls1,ls2));

	ls1 = cons (1,cons (2,cons (3, cons (4, Nil))));
	ls2 = cons ('a',cons ('b',cons ('c', cons ('d', Nil))));
	document.write ("<p>braid ");
	printList(ls1);
	printList(ls2);
	document.write (" = ");
	printList(braid(ls1,ls2));

	ls1 = Nil;
	ls2 = cons ('a',cons ('b',cons ('c', cons ('d', Nil))));
	document.write ("<p>braid ");
	printList(ls1);
	printList(ls2);
	document.write (" = ");
	printList(braid(ls1,ls2));

	document.write("<p>==================================================</p>");
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


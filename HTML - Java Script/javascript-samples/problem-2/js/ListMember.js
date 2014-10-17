// Problem -2 : Implement listMember functionin javascript
//===============================================================
/*Implement the listMember function in Javascript using the
Find out the largest sized list for which the
Javascript program does the recursion without complaining of
stack overflow.  [Hint: you might first want to write a
program that builds a list of size n for any n.  The
elements of this shouldn't matter.]*/

//Define the instantiate method.
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
    alert("Error: Cannot access the head of a Nil datatype...");
};

Nil.tl = function() {
    alert("Error: Cannot access the tail of a Nil datatype...");
};

// =============
// Pair
// =============

var Pair = instantiate(List);

// pair : [Any List] -> Pair
var pair = function(head,tail) {
    var a = instantiate(Pair);
    a.hd = function() {return head;};
    a.tl = function() {return tail;};
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
//==========================================================================

// listMember
// --------

Nil.listMember = function(x)  {
    return false;
};

Pair.listMember = function(x) {
    if (this.hd() === x) {
        return true;
    }
    return this.tl().listMember(x);
};
//==========================================================================

//Functions to display the contents of the list
Nil.display = function() {
    return "()";
};

Pair.display = function() {
    var s =  "(" + this.hd() + " -> " + this.tl().display() + ")";
    return s;
};


//==========================================================================
//Find out the largest sized list for which the
//Javascript program does the recursion without complaining of
//stack overflow.

//Function to create a list of size argument
//createList : [size:int] -> List
//---------------------------------
var createList = function (size) {
	var ls = pair(size, Nil);
	size=size-1;
	while (size > 0) {
		ls = pair(size,ls);
		size--;
	}
	return ls;
}

var printList = function(ls) {
	document.write("<br>");
	document.write (ls.display());
	document.write("<br><br>");
}

var main = function () {
	document.write ("<p> Creating a list of size 10...</p>");
	ls = createList(10);

	document.write ("<p> Following are the contents of the list</p>");
	printList(ls);

	document.write ("<p>listMember(4) = ");
	document.write (ls.listMember(4));

	document.write ("<p>listMember(32) = ");
	document.write (ls.listMember(32));

	document.write ("<p>listMember(10) = ");
	document.write (ls.listMember(10));

	document.write ("<p>========================================================================</p>");

	document.write ("<p>Find the largest sized list for which it does the recursion without complaining.</p>");
	document.write ("<p>We do this by creating lists of size 1000, 2000 and so on...</p>");
	document.write("<p> Then check membership of last element, which will either return true or result in a stack overflow</p>");
	document.write ("<p>Using this method it has been found that, the largest sized list for which it does the recursion without complaining is,</p>");
	document.write ("<h2> MAX List size = 2998</h2>");

	document.write ("<p><h4>Create list of size = 2998 and check listMember(2998) = ");
	ls = createList(2998);
	document.write (ls.listMember(2998));
	document.write ("<p>====No Stack overflow=====</h4></p>");

	document.write("<p><u><i>Note: Creating a list of size <b>2999</b> will result in a stack overflow...</p>");

}




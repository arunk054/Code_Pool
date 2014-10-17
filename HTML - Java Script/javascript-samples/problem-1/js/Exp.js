//Problem  1: Inductive Data types
//--------------------------------
/*Implement abstract syntax and evaluation of a formula Javascript
A formula expression may be specified by the following abstract grammar:
Exp :: = numExp(n: Number) |  plusExp(operand1: Exp, operand2: Exp)

An Exp is either 
* a NumExp built from the constructor numExp that takes a
  number n.  n is also the name of the component of a NumExp
  instance.

OR 

* a PlusExp built from the constructor plusExp that takes
  two arguments operand1 and operand2, which are of type
  Exp.  Operand1 and Operand2 are also the names of the
  components of a PlusExp instance. 

Define datatype Exp, NumExp, PlusExp and the following constructors:
numExp : Number -> NumExp
plusExp  : [Exp Exp  ] -> PlusExp
Example: 
plusExp (numExp (5) ), (numExp (2) ))

Also we will need type predicates - isNumExp, isPlusExp
*/


//Define the instantiate method.
var instantiate = function(o) {
    var F = function() {};
    F.prototype = o;
    return new F();
};


//==================================================================================
//Define the exp datatype first
var Exp = new Object();

Exp.isExp = function () {
	this.isNumExp || this.isPlusExp;
};
//==================================================================================

//Now we define the Numexp which is a Exp
var NumExp = instantiate(Exp);

//Define type predicate for the same
NumExp.isNumExp = function () {
	return true;
}

//Since a numExp cannot be a plusExp, and vice versa, we define them
// as mutually exclusive using the isPlusExp and isNumExp
NumExp.isPlusExp = function () {
	return false;
}


//This is the constructor for NumExp
//numExp : isNumber -> NumExp
//-----------------------------
var numExp =  function (n) {
	var a = instantiate(NumExp);
	//Not defining any get-ters because n is a component
	// of numExp instance as per the question.
	a.n = n;
	return a;
};
//==================================================================================

// We now define PlusExp datatype

var PlusExp = instantiate (Exp);

//Define type predicates
PlusExp.isNumExp = function () {
	return false;
}

PlusExp.isPlusExp = function () {
	return true;
}
//=============================================================================


//The constructor
//plusExp : [Exp Exp] -> PlusExp
//--------------------------------
var plusExp =  function (op1, op2) {
	var a = instantiate (PlusExp);
	//Not defining any get-ters because op1, op2 is a component
	// of plusExp instance as per the question.
	a.operand1 = op1;
	a.operand2 = op2;
	return a;
}

//=====================================================================================

//Define the accessors for NumExp and PlusExp
NumExp.getNumber = function () {
	return this.n;
}

PlusExp.getOperand1 = function () {
	return this.operand1;
}

PlusExp.getOperand2 = function () {
	return this.operand2;
}
//====================================================================================

//2. Implement a function evaluate that evaluates an AST.

// We first define evaluate for NumExp
NumExp.evaluate = function () {
	return this.getNumber();
}

//We now define the evaluate function of PlusExp
PlusExp.evaluate = function () {
	return this.getOperand1().evaluate() + this.getOperand2().evaluate();
}

//======================================================================================
//FOllowing are only for testing

//Just define a print function for the sake of testing
NumExp.print = function () {
	document.write ("(numExp ");
	document.write (this.n);
	document.write(")");
}

PlusExp.print = function () {

	document.write ("(plusExp ");
	this.operand1.print();
	document.write (" ");
	this.operand2.print();
	document.write(")");
}

//evalAndDisplay : Exp -> void
var evalAndDisplay = function(o) {
	o.print();
	document.write("<br><br>Value after evaluate = ");
	document.write(o.evaluate());
	document.write ("<br><br><br>");
	
}
var main = function () {
	document.write ("<p>Constructing the following numExp objects and evaluating...</p>");
	var n1 = numExp(1);
//	evalAndDisplay(n1);

	var n2 = numExp (2);
	evalAndDisplay(n2);

	var n3 = numExp (3);
//	evalAndDisplay(n3);

	var n4 = numExp (4);
	evalAndDisplay(n4);

	document.write ("<p>Constructing the following plusExp objects and evaluating...</p>");
	var p1 = plusExp (n1, n2);
//	evalAndDisplay(p1);

	var p2 = plusExp (n3, n4);
	evalAndDisplay(p2);

	var p3 = plusExp (p1, p2);
	evalAndDisplay(p3);

	var p4 = plusExp (p3, p3);
	evalAndDisplay(p4);

}

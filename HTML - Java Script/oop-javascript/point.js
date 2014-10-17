/*
============================
     2-Dimensional Point
============================

This is an implementation of a mutable two-dimensional point datatype in java script.
Author: Arun K <arun.k@iiitb.net>
*/

//This is the tag that will be used to identify my point datatype
var myTag = "point2D"

// Constructor
//===============

// make_point : [isNumber isNumber] -> is_point
//---------------------------------------------
make_point = function(xVal, yVal) {
	var p = {tag : myTag, x : xVal, y : yVal };
	return p;
}

//Type Predicate
//==================

// is_point : [any] -> boolean
//------------------------------
is_point = function (p) {
	var i = 0;
	for(var v in p) {
		i++;
	}
	if(( i == 3) && (typeof(p) == "object") &&
	   ("tag" in p) && ("x" in p) && ("y" in p) &&
	   (p.tag == myTag) && (isNumber(p.x)) && (isNumber(p.y))) {
            return true;
	}else {
            return false;
	}
}

// Accessors
//=================

// Function to access the x co-ordinate in a point
// point_x : [ is_point ] -> isNumber
//---------------------------------------

point_x = function(p) {
	return p.x;
}


// Function to access the y co-ordinate in a point
// point_y : [ is_point ] -> isNumber
//---------------------------------------

point_y = function(p) {
	return p.y;
}


// Mutators
//===========

// Function to set the x coordinate
// set_point_x : [is_point isNumber] -> void
//----------------------------------------------
set_point_x = function(p, val) {
	p.x = val;
}

// Function to set the y coordinate
// set_point_y : [is_point isNumber] -> void
//----------------------------------------------
set_point_y = function(p, val) {
	p.y = val;
}

// Equality Predicate
//====================

// is_point-equal : [is_point is_point] -> boolean
// -------------------------------------------------

is_point_equal = function(p1, p2) {
	if( p1.x == p2.x && p1.y == p2.y)
		return true;
	else
		return false;
}

//Useful Points
//=================

//One useful point on the co-ordinate axes is the origin ==> (0,0)
origin = make_point(0,0);

//Predicae to identify the Origin
//is_point-origin : [is_point] -> boolean
//-----------------------------------------
is_point_origin = function(p) {
	return is_point_equal (p, origin);
}


//Some common operations performed on point(s).
//=============================================

//NOTE: The helper functions for these operations are defined below.

//This function returns distance (absolute value) between two points
//This will always return a non-negative number because we take the square
// point_distance : [is_point is_point] -> isNonNegative
//----------------------------------------------------

point_distance = function (p1, p2) {
	var xDiff = point_sub_x(p1, p2);
	var yDiff = point_sub_y(p1,p2);
	var ret = Math.pow(xDiff, 2) + Math.pow(yDiff,2);
	return Math.sqrt(ret);	
}


//This function returns a the distance between the point and origin
// point_distance_from_origin : [is_point] -> isNonNegative
//------------------------------------------------------

point_distance_from_origin = function(p) {
	return point_distance(p, origin);
}

// Takes a point and two numbers dx and dy.
// Updates the points x and y coordinates by the amounts
// dx and dy respectively. This is also a kind of mutator
// point_move :  [is_point isNumber isNumber] -> void
//----------------------------------------------------

point_move = function (p, dx, dy) {
    set_point_x(p, point_x(p) + dx);//First move the x co-ordinate
    set_point_y(p, point_y(p) + dy); //Then move the y co-ordinate.
}

//Following are some Helper Functions
//====================================

//Function to check if the given identifier is a number or not
// isNumber : [any] -> boolean
//------------------------------
function isNumber(x) 
{ 
  return ( (x != null) && (typeof(x) === typeof(1.0)) && isFinite(x) );
}

//Function to find the difference in x co-ordinate of two points

// point_sub_x : [is_point is_point] -> isNumber
//------------------------------------------
point_sub_x = function (p1, p2) {
	return (p1.x - p2.x);
}


//Function to find the difference in y co-ordinate of two points
// point_sub_y : [is_point is_point] -> isNumber
//------------------------------------------
point_sub_y = function(p1, p2) {
	return (p1.y - p2.y);
}

//Function to find which quadrant the point belongs to
// point_quadrant : [is_point] -> isNumber
//-----------------------------------------

point_quadrant = function (p) {
	var x = point_x(p);
	var y = point_y(p);

    	if (x >= 0) {
	        if (y >= 0) {
	            return 1; //implies first quadrant
		}else{
	            return 4;} // implies 4th quad, as y is negative and x positive
	}else{
	        if (y >= 0){
	            return 2; //implies x negative and y positive, 2nd quadrant
		}else{
	            return 3;} // implies 3rd quad, as x and y both negative
	}
}


/*
====================================================================
Consumer script for the 2D-Point datatype implemented in point.js
====================================================================

This is just an interface between point.html and point.js, it reads the input from the html
and invokes the methods in point.js and displays the output in the html page.
Author: Arun K <arun.k@iiitb.net>
*/


main = function () {
	var form = document.getElementById("form1");
	var evaluate = form.elements['compute'];
	var clear = form.elements['clear'];
	var output = form.elements['output'];

	evaluate.addEventListener("click", function() { onEvaluateClicked(form); },false);
	clear.addEventListener("click", function() { onClearClicked(form); },false);
}

//This method is invoked when Evaluate button is clicked
onEvaluateClicked = function (form){

	//Just subtract input values by zero inorder to convert it to numbers.
	var x1 = form.elements['x1'].value - 0;
	var y1 = form.elements['y1'].value - 0;
	var x2 = form.elements['x2'].value - 0;
	var y2 = form.elements['y2'].value - 0;
	var dx1 = form.elements['dx1'].value - 0;
	var dy1 = form.elements['dy1'].value - 0;
	var dx2 = form.elements['dx2'].value - 0;
	var dy2 = form.elements['dy2'].value - 0;

	var output = form.elements['output'];

	//Set the value back to the input box, so, that there is consistency in what the user sees.
	form.elements['x1'].value=x1;
	form.elements['y1'].value=y1;
	form.elements['x2'].value=x2;
	form.elements['y2'].value=y2;
	form.elements['dx1'].value=dx1;
	form.elements['dy1'].value=dy1;
	form.elements['dx2'].value=dx2;
	form.elements['dy2'].value=dy2;

	var str_p1 = getStrP1(x1,y1);
	var str_p2 = getStrP2(x2,y2);

	//First clear the textarea
	output.value="";
	output.value+="User input = "+str_p1+"\n";
	output.value+="User input = "+str_p2+"\n\n";

	//Create the point-1 and check type predicate
	output.value+="\n";
	output.value+="Invoking make_point & is_point on "+str_p1+"...\n";
	var p1 = make_point(x1, y1);
	str_p1 = getStrP1(point_x(p1), point_y(p1));
	var isp1 = is_point(p1);
	if (isp1) {
		output.value+="===> "+str_p1+" is a valid point.\n";
	} else {
		output.value+="===> !!! "+str_p1+" is an INVALID point. !!!\n";
	}

	//Create the point-2 and check type predicate
	output.value+="\n";
	output.value+="Invoking make_point & is_point on "+str_p2+"...\n";
	var p2 = make_point(x2, y2);
	str_p2 = getStrP2(point_x(p2), point_y(p2));
	var isp2 = is_point(p2);
	if (isp2) {
		output.value+="===> "+ str_p2+" is a valid point.\n";
	} else {
		output.value+="===> !!! "+str_p2+" is an INVALID point. !!!\n";
	}
	//Check Accessors
	if (isp1) {
		output.value+="\n";
		output.value+="Invoking accessors on "+str_p1+"...\n";
		output.value+="===> x-coordinate = "+point_x(p1)+" and y-coordinate = "+point_y(p1)+"\n";
	}
	if (isp2) {
		output.value+="\n";
		output.value+="Invoking accessors on "+str_p2+"...\n";
		output.value+="===> x-coordinate = "+point_x(p2)+" and y-coordinate = "+point_y(p2)+"\n";
	}

	//Checking if the points are equal
	if(isp1 && isp2) {
		output.value+="\n";
		output.value+="Invoking equality predicate on "+str_p1+" and "+str_p2+"...\n";
		if (is_point_equal(p1, p2))
			output.value+="===> %%% The points are equal %%%\n";
		else
			output.value+="===> !!! The points are NOT equal !!!\n";
	}

	if (isp1 || isp2) {
		output.value+="\n";
		output.value+="Performing few operations on the points...\n";
	}
	
	//Find the quadrant
	if (isp1) {
		output.value+="\n";
		output.value+="===> "+str_p1+" is in quadrant: "+point_quadrant(p1)+"\n";
	}

	if (isp2) {
		output.value+="\n";
		output.value+="===> "+str_p2+" is in quadrant: "+point_quadrant(p2)+"\n";
	}

	//Invoking the  operations
	if (isp1 && isp2) {
		output.value+="\n";
		var distance = point_distance(p1,p2);
		output.value+="Distance between "+str_p1+" and "+str_p2+" is:\n";
		output.value+="===> "+ distance +" units\n";
	}

	if (isp1) {
		output.value+="\n";
		var distance = point_distance_from_origin(p1);
		output.value+="Distance of "+str_p1+" from origin is:\n";
		output.value+="===> "+ distance +" units\n";
	}

	if (isp2) {
		output.value+="\n";
		var distance = point_distance_from_origin(p2);
		output.value+="Distance of "+str_p2+" from origin is:\n";
		output.value+="===> "+ distance +" units\n";
	}

	//Invoke point_move
	if (isp1) {
		output.value+="\n";
		output.value+="Moving "+str_p1+" by dx = "+dx1+" and dy = "+dy1+"\n";
		point_move(p1, dx1, dy1);
		str_p1 = getStrP1(point_x(p1),point_y(p1));
		output.value+="===> The modified point is "+str_p1+"\n";
		//Just check, if after modifying, whether it is still a valid point.
		if (!is_point(p1))
			output.value+="!!! "+str_p1+" is NO longer a valid point. !!!\n"
	}

	if (isp2) {
		output.value+="\n";
		output.value+="Moving "+str_p2+" by dx = "+dx2+" and dy = "+dy2+"\n";
		point_move(p2, dx2, dy2);
		str_p2 = getStrP2(point_x(p2), point_y(p2));
		output.value+="===> The modified point is "+str_p2+"\n";
		//Just check, if after modifying, whether it is still a valid point.
		if (!is_point(p2))
			output.value+="!!! "+str_p2+" is NO longer a valid point. !!!\n"
	}

	output.value+="\n======================= THE END =======================\n";
}

onClearClicked = function (form) {
	form.elements['output'].value="";
}

getStrP1 = function(x1, y1) {
	var s = "Point-1 ("+x1+", "+y1+")"; 
	return s;
}

getStrP2 = function(x2, y2) {
	var s = "Point-2 ("+x2+", "+y2+")" ;
	return s;
}

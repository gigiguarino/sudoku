

// important defines
var INVALID_COLOR = "red";
var VALID_COLOR = "#3e3e3e";
var NORMAL_FONT = "#3e3e3e";
var DARK_FONT = "black";
var DARK_BG = "#c5e2c5";
var LIGHT_BG = "#ebfdeb";
var NUM_BOARDS = 600;



// global arrays of spots
var current_board_spots = [];
var correct_board_spots = [];
var start_board_spots = [];
var current_active_spot;


$(document).ready(function(){
	errors_shown = 0;
	zeroize_board();
	generate_board();
	// set active box
	$(".box").on("click", set_active);
	// hover over buttons
	$(".button").on("mouseenter", set_dark);
	$(".button").on("mouseleave", set_light);
	// reset button
	$(".reset").on("click", reset_board);
	// new board button
	$(".new").on("click", new_board);
	// show solution button
	$(".show").on("click", show_solution);
	// check solution button
	$(".check").on("click", check_board);
	// help button
	$(".help").on("click", popup_help);
});






/////////////////////////////////////////////
/////////////////////////////////////////////
// BOARD GENERATION AND HANDLING
/////////////////////////////////////////////
/////////////////////////////////////////////

/////////////////////////////////////////////
// fill_board()
// fills the spots of the board
// with the values from current_board_spots
/////////////////////////////////////////////

function fill_board() {
	var current_row;
	var current_col;
	var current_class = "";
	for (i = 0; i < 81; i++)
	{
		current_row = Math.floor(i/9);
		current_col = i%9;
		current_row += 1;
		current_col += 1;
		current_class = ".r" + current_row.toString() + 
						".c" + current_col.toString();
		if (current_board_spots[i] == "0")
		{
			$(current_class).text(" ");
		}
		else
		{
			$(current_class).text(current_board_spots[i]);
		}
	}
}

function update_spots() {
	var current_row;
	var current_col;
	var current_class = "";
	for (i = 0; i < 81; i++)
	{
		current_row = Math.floor(i/9);
		current_col = i%9;
		current_row += 1;
		current_col += 1;
		current_class = ".r" + current_row.toString() + 
						".c" + current_col.toString();
		current_board_spots[i] = $(current_class).text();
	}
}

function zeroize_board() {
	for (i = 0; i < 81; i++)
	{
		current_board_spots.push("0");
		start_board_spots.push("0");
		correct_board_spots.push("0");
	}
}


/////////////////////////////////////////////
// in_row() in_col() in_square()
// helper functions for board generation
/////////////////////////////////////////////

function in_row(num, row, col){
	for (i = 0; i <= row; i++)
	{
		if (current_board_spots[i*9 + col] == num)
		{
			return true;
		}
	}
	return false;
}

function in_col(num, row, col){
	for (i = 0; i <= col; i++)
	{
		if (current_board_spots[row*9 + i] == num)
		{
			return true;
		}
	}
	return false;
}

function in_square(num, row, col){

	var small_r = 0;
	var big_r = 0;
	var small_c = 0;
	var big_c = 0;

	if (row >= 0 && row <= 2)
	{
		small_r = 0;
		big_r = 2;
	}

	else if (row >= 3 && row <= 5)
	{
		small_r = 3;
		big_r = 5;
	}

	else if (row >= 6 && row <= 8)
	{
		small_r = 6;
		big_r = 8;
	}

	if (col >= 0 && col <= 2)
	{
		small_c = 0;
		big_c = 2;
	}

	else if (col >= 3 && col <= 5)
	{
		small_c = 3;
		big_c = 5;
	}

	else if (col >= 6 && col <= 8)
	{
		small_c = 6;
		big_c = 8;
	}

	for (r = small_r; r <= big_r; r++)
	{
		for (c = small_c; c <= big_c; c++)
		{
			if (current_board_spots[r*9 + c] == num)
			{
				return true;
			}
		}
	}

	return false;
}



/////////////////////////////////////////////
// generate_board()
/////////////////////////////////////////////

function generate_board() {

	// random number between 0 and NUM_BOARDS
	var num = 0;
	var url1 = "";
	var url2 = "";
	while (num <= 0 || num > NUM_BOARDS)
	{
		num = Math.floor(Math.random() * (NUM_BOARDS));
		url1 = "boards/correct/" + num.toString() + ".txt";
		url2 = "boards/start/" + num.toString() + ".txt";
	}

	$.ajax({
	type: "GET",
    url: url1,
    success: function (data){
      	for (i = 0; i < 81; i++)
      	{
      		correct_board_spots[i] = data[i];
		}
    }
  	});
  	$.ajax({
	type: "GET",
    url: url2,
    success: function (data){
      	for (i = 0; i < 81; i++)
      	{
      		current_board_spots[i] = data[i];
      		start_board_spots[i] = data[i];
		}
		fill_board();
    }
  	});
}






/////////////////////////////////////////////
/////////////////////////////////////////////
// BOARD CHECKING FOR AFTER PLACEMENTS
/////////////////////////////////////////////
/////////////////////////////////////////////

/////////////////////////////////////////////
// check_square(#) check_row(#) check_col(#)
// these loop through the sq(1-9) r(1-9) c(1-9) 
// classes and check if there are more 
// than one instance of a number(#)
// returns: boolean (true/false)
/////////////////////////////////////////////

function check_square(num) {
	var current_name;
	var spot;
	var num_spots;
	var valid = true;
	for (x = 1; x <= 9; x++)
	{
		current_name = ".sq" + x.toString();
		num_spots = 0;
		$(current_name).each(function(){
			if ($(this).text() == num.toString())
			{
				num_spots++;
			}
			// can't be a win if a number isn't filled in
			if ($(this).text() == " ")
			{
				valid = false;
			}
		});
		if (num_spots > 1)
		{
			valid = false;
		}
	}
	return valid;
}

function check_row(num) {
	var current_name;
	var spot;
	var num_spots;
	var valid = true;
	for (x = 1; x <= 9; x++)
	{
		current_name = ".r" + x.toString();
		num_spots = 0;
		$(current_name).each(function(){
			if ($(this).text() == num.toString())
			{
				num_spots++;
			}
			// can't be a win if a number isn't filled in
			if ($(this).text() == " ")
			{
				valid = false;
			}
		});
		if (num_spots > 1)
		{
			valid = false;
		}
	}
	return valid;
}

function check_col(num) {
	var current_name;
	var spot;
	var num_spots;
	var valid = true;
	for (x = 1; x <= 9; x++)
	{
		current_name = ".c" + x.toString();
		num_spots = 0;
		$(current_name).each(function(){
			if ($(this).text() == num.toString())
			{
				num_spots++;
			}
			// can't be a win if a number isn't filled in
			if ($(this).text() == " ")
			{
				valid = false;
			}
		});
		if (num_spots > 1)
		{
			valid = false;
		}
	}
	return valid;
}


/////////////////////////////////////////////
// check_for_win()
// calls all the checking functions
// validity colors are set in the above
// checking functions
// every checking function has to return true
// for there to be a win
// returns: boolean (true/false)
/////////////////////////////////////////////

function check_for_win(){
	var win = true;
	for (i = 1; i <= 9; i++)
	{
		win = win && check_col(i,0) && check_row(i,0) && check_square(i,0);
	}
	return win;
}









/////////////////////////////////////////////
/////////////////////////////////////////////
// EVENT HANDLING
/////////////////////////////////////////////
/////////////////////////////////////////////

function set_active() {
	if ($(this).css("color") == DARK_FONT)
	{
		$(this).css("color", NORMAL_FONT);
		$(this).css("font-weight", normal);
		current_active_spot = 0;
		if ($(this).text() == ".")
		{
			$(this).text(" ");	
		}
	}
	else
	{
		$(".box").each(function(){
			$(this).css("color", NORMAL_FONT);
			$(this).css("font-weight", "normal");
			if ($(this).text() == ".")
			{
				$(this).text(" ");
			}
		});
		$(this).css("color", DARK_FONT);
		$(this).css("font-weight", "bold");
		if ($(this).text() == " ")
		{
			$(this).text(".");
		}
		current_active_spot = this;
	}
}

// button background change back to light
// after hover
function set_light() {
	$(this).css("background-color", LIGHT_BG);
	$(this).css("color", NORMAL_FONT);
	$(this).css("font-weight", "normal");
}

// button background change on hover
// goes darker
function set_dark() {
	$(this).css("background-color", DARK_BG);
	$(this).css("font-weight", "bold");
}


// reset board
// back to start board
function reset_board() {
	current_board_spots = start_board_spots.slice();
	fill_board();
}

function new_board() {
	generate_board();
	fill_board();
}

function show_solution() {
	current_board_spots = correct_board_spots.slice();
	fill_board();
}

function check_board() {
	if (check_for_win())
	{
		popup("You win!");
	}
	else
	{
		popup("Sorry, this is incorrect.");
	}
}


function popup_help(){
	$(".popup").css("width", "300px");
	$(".popup").css("margin-left", "-155px");
	$(".popup").css("height", "220px");
	$(".popup").css("margin-top", "-115px");
	$("#pu-p").css("width", "280px");
	$("#pu-div").css("width", "280px");
	$("#pu-div").css("margin-left", "-140px");
	$("#pu-div").css("height", "125px");
	$("#pu-p").html("Each row, column, and square contains the numbers 1-9.<br><br>Click to place a number.<br>Zero erases a number.");
	// attach events for the okay button
	$(".button.ok").on("click", remove_popup);
	// make popup visible
	$(".popup").css("visibility", "visible");
}

function remove_popup() {
	$(".popup").css("visibility", "hidden")
}

function popup(text) {
	$(".popup").css("width", "220px");
	$(".popup").css("margin-left", "-115px");
	$(".popup").css("height", "160px");
	$(".popup").css("margin-top", "-85px");
	$("#pu-p").css("width", "200px");
	$("#pu-div").css("width", "200px");
	$("#pu-div").css("margin-left", "-100px");
	$("#pu-div").css("height", "70px");
	$("#pu-p").html(text);
	// attach events for the okay button
	$(".button.ok").on("click", remove_popup);
	// make popup visible
	$(".popup").css("visibility", "visible");
}

// numbers
$(document).keyup(function(e){
	// 48 = 0
	// 49 = 1
	// ..
	// 57 = 9
	if (e.keyCode >= 48 && e.keyCode <= 57)
	{
		if (current_active_spot != 0)
		{
			if (e.keyCode != 48 || $(current_active_spot).text() != ".")
			{
				$(current_active_spot).text((e.keyCode - 48).toString());
			}
			update_spots();
			fill_board();
		}
	}
});






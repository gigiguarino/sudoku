

var INVALID_COLOR = "red";
var VALID_COLOR = "green";
var NUM_BOARDS = 400;

var current_board_spots = [];
var correct_board_spots = [];
var start_board_spots = [];
var cursor_row;
var cursor_col;

$(document).ready(function(){
	zeroize_board();
	start();
});



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
		$(current_class).text(current_board_spots[i]);
	}
}

function zeroize_board() {
	for (i = 0; i < 81; i++)
	{
		current_board_spots.push("0");
	}
}



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
	for (i = 1; i <= 9; i++)
	{
		current_name = ".sq" + num;
		num_spots = 0;
		$(current_name).each(function(){
			if ($(this).val() == num)
			{
				num_spots++;
			}
			// can't be a win if a number isn't filled in
			if ($(this).val() == 0)
			{
				valid = false;
			}
		});
		if (num_spots > 1)
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				$(this).css("color", INVALID_COLOR);
			}
		});
		}
		else 
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				$(this).css("color", VALID_COLOR);
			}
		});
		}
	}
	return valid;
}

function check_row(num) {
	var current_name;
	var spot;
	var num_spots;
	var valid = true;
	for (i = 1; i <= 9; i++)
	{
		current_name = ".r" + num;
		num_spots = 0;
		$(current_name).each(function(){
			if ($(this).val() == num)
			{
				num_spots++;
			}
			// can't be a win if a number isn't filled in
			if ($(this).val() == 0)
			{
				valid = false;
			}
		});
		if (num_spots > 1)
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				$(this).css("color", INVALID_COLOR);
			}
		});
		}
		else 
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				$(this).css("color", VALID_COLOR);
			}
		});
		}
	}
	return valid;
}

function check_col(num) {
	var current_name;
	var spot;
	var num_spots;
	var valid = true;
	for (i = 1; i <= 9; i++)
	{
		current_name = ".c" + num;
		num_spots = 0;
		$(current_name).each(function(){
			if ($(this).val() == num)
			{
				num_spots++;
			}
			// can't be a win if a number isn't filled in
			if ($(this).val() == 0)
			{
				valid = false;
			}
		});
		if (num_spots > 1)
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				$(this).css("color", INVALID_COLOR);
			}
		});
		}
		else 
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				$(this).css("color", VALID_COLOR);
			}
		});
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
		win = win && check_col(i) && check_row(i) && check_square(i);
	}
	return win;
}






/////////////////////////////////////////////
// win()
/////////////////////////////////////////////

function win(){

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
	var num = Math.floor(Math.random() * (NUM_BOARDS));
	var url = "boards/" + num.toString() + ".txt";

	$.ajax({
	type: "GET",
    url: url,
    success: function (data){
      	for (i = 0; i < 81; i++)
      	{
      		current_board_spots[i] = data[i];
		}
		fill_board();
    }
  	});
}




/////////////////////////////////////////////
// keydown
// checks for pressing of the arrow keys
// and numbers, letters
/////////////////////////////////////////////

$(document).on('keydown', function(e) {
	if (e.keyCode == 37)
	{
		// left
		if (cursor_col != 0)
		{
			cursor_col--;
		}
	}
	else if (e.keyCode == 38)
	{
		// up
		if (cursor_row != 0)
		{
			cursor_row--;
		}
	}
	else if (e.keyCode == 39)
	{
		// right
		if (cursor_col != 8)
		{
			cursor_col++;
		}
	}
	else if (e.keyCode == 40)
	{
		// down
		if (cursor_row != 8)
		{
			cursor_col++;
		}
	}
	else if (e.keyCode == 82)
	{
		// reset board
		current_board_spots = start_board_spots;
		if (check_for_win())
		{
			win();
		}
	}
	else if (e.keyCode == 78)
	{
		// new board
		generate_board();
		if (check_for_win())
		{
			win();
		}
	}
	else if (e.keyCode == 48)
	{
		// clear spot
		current_board_spots[cursor_row*9 + cursor_col] = 0;
		if (check_for_win())
		{
			win();
		}
	}
	else if (e.keyCode > 48 && e.keyCode < 58)
	{
		// number
		current_board_spots[cursor_row*9 + cursor_col] = e.keyCode - 48;
		if (check_for_win())
		{
			win();
		}

	}
	else if (e.keyCode == 81)
	{
		// give up
		// show correct solution
		current_board_spots = correct_board_spots;
		if (check_for_win())
		{
			win();
		}
	}
})


/////////////////////////////////////////////
// start()
/////////////////////////////////////////////

function start(){
	cursor_col = 0;
	cursor_row = 0;
	generate_board();
}



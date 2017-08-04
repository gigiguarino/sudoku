

var current_board_spots = [];
var correct_board_spots = [];
var start_board_spots = [];
var cursor_row;
var cursor_col;

$(document).ready(function(){
	start();
});

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
				// change to red
			}
		});
		}
		else 
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				// change to black
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
				// change to red
			}
		});
		}
		else 
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				// change to black
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
				// change to red
			}
		});
		}
		else 
		{
			$(current_name).each(function(){
			if ($(this).val() == num)
			{
				// change to black
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
	for (i = 0; i < row; i++)
	{
		if (correct_board_spots[i*9 + col] == num)
		{
			return true;
		}
	}
	return false;
}

function in_col(num, row, col){
	for (i = 0; i < col; i++)
	{
		if (correct_board_spots[row*9 + i] == num)
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
			if (correct_board_spots[r*9 + c] == num)
			{
				return true;
			}
		}
	}

	return false;
}

function shuffle(a){
    var j, x, i;
    for (i = a.length; i; i--) {
        j = Math.floor(Math.random() * i);
        x = a[i - 1];
        a[i - 1] = a[j];
        a[j] = x;
    }
}

/////////////////////////////////////////////
// generate_board()
// creates starting board
/////////////////////////////////////////////

function generate_board(){
	var numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9];
	var current_numbers = numbers;
	var num;

	var backtrack_rows = [];
	var backtrack_cols = [];
	var backtrack_nums = [];
	var backtrack_nums_to_try = [];

	var done = false;
	var go_back = false;
	var placed = false;

	while (current_numbers.length != 0)
	{
		if (current_numbers.length > 1)
		{
			shuffle(current_numbers);
		}
		num = current_numbers.pop();
		correct_board_spots[current_numbers.length] = num;
	}

	var row = 1;
	var col = 0;
	var current_num;

	while (!done)
	{
		if (go_back)
		{
			// backtrack
			current_numbers = backtrack_nums_to_try.pop();
			current_num = backtrack_nums.pop();
			row = backtrack_rows.pop();
			col = backtrack_cols.pop();
			correct_board_spots[row*9 + col] = 0;
			placed = false;
			go_back = false;
		}

		else
		{
			current_numbers = numbers;
			shuffle(current_numbers);
			placed = false;
		}

		// try all of remaining numbers
		while (!placed && current_numbers.length != 0)
		{
			current_num = current_numbers.pop();
			// check row
			if (!in_row(current_num, row, col) &&
				!in_col(current_num, row, col) &&
				!in_square(current_num, row, col))
			{
				backtrack_cols.push(col);
				backtrack_rows.push(row);
				backtrack_nums.push(current_num);
				backtrack_nums_to_try.push(current_numbers);
				correct_board_spots[row*9 + col] = current_num;
				placed = true;
			}
		}

		// valid spot
		if (placed)
		{
			if (row == 8 && col == 8)
			{
				done = true;
			}

			else if (col == 8)
			{
				row++;
				col = 0;
			}

			else 
			{
				col++;
			}
		}

		// backtrack
		if (!placed && current_numbers.length == 0)
		{
			go_back = true;
		}
	}
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



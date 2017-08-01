

var current_board_spots = [];
var correct_board_spots = [];
var start_board_spots = [];


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
			// mark all $current_name to red/invalid
			valid = false;
		}
		else 
		{
			// mark all $current_name to black/valid
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
			// mark all $current_name to red/invalid
			valid = false;
		}
		else 
		{
			// mark all $current_name to black/valid
		}
	}
	return valid;
}

function check_col(num) {
	vvar current_name;
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
			// mark all $current_name to red/invalid
			valid = false;
		}
		else 
		{
			// mark all $current_name to black/valid
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
// keydown
// checks for pressing of the arrow keys
// and numbers, letters
/////////////////////////////////////////////

$('html').keydown(function(e){
       $('#keydown_con').val(e.which);
    });
}





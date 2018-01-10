

NUM_BOARDS=800

make clean
make all

echo "making easy boards..."
./sudoku_generation $NUM_BOARDS 1 > all_easy.txt
echo "making medium boards..."
./sudoku_generation $NUM_BOARDS 2 > all_medium.txt
echo "making hard boards..."
./sudoku_generation $NUM_BOARDS 3 > all_hard.txt

./make_separate.sh

echo "done :-)"
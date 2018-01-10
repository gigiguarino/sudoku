
# create trash output
touch trash.txt

# EASY GENERATION
FILENAME="all_easy.txt"
n=0
t=1
while IFS= read -r line;
do
  if [ "$t" -eq 1 ]; then
    touch "easy/correct/$n.txt";
    echo $line > easy/correct/$n.txt;
    t=2;
  elif [ "$t" -eq 2 ]; then
    touch "easy/start/$n.txt";
    echo $line > easy/start/$n.txt;
    t=3;
  else
    echo $line > trash.txt;
    t=1;
    ((n++))
  fi
done < $FILENAME

# MEDIUM GENERATION
FILENAME="all_medium.txt"
n=0
t=1
while IFS= read -r line;
do
  if [ "$t" -eq 1 ]; then
    touch "medium/correct/$n.txt";
    echo $line > medium/correct/$n.txt;
    t=2;
  elif [ "$t" -eq 2 ]; then
    touch "medium/start/$n.txt";
    echo $line > medium/start/$n.txt;
    t=3;
  else
    echo $line > trash.txt;
    t=1;
    ((n++))
  fi
done < $FILENAME

# HARD GENERATION
FILENAME="all_hard.txt"
n=0
t=1
while IFS= read -r line;
do
  if [ "$t" -eq 1 ]; then
    touch "hard/correct/$n.txt";
    echo $line > hard/correct/$n.txt;
    t=2;
  elif [ "$t" -eq 2 ]; then
    touch "hard/start/$n.txt";
    echo $line > hard/start/$n.txt;
    t=3;
  else
    echo $line > trash.txt;
    t=1;
    ((n++))
  fi
done < $FILENAME


# remove trash output
rm trash.txt

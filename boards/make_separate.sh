

FILENAME="all.txt"
n=0
while IFS= read -r line;
do
  touch "$n.txt";
  echo $line > $n.txt;
  ((n++))
done < $FILENAME

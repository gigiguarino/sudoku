

FILENAME="all.txt"
n=0
t=1
while IFS= read -r line;
do
  if [ "$t" -eq 1 ]; then
    touch "correct/$n.txt";
    echo $line > correct/$n.txt;
    t=2;
  elif [ "$t" -eq 2 ]; then
    touch "start/$n.txt";
    echo $line > start/$n.txt;
    t=3;
  else
    echo $line > dummy.txt;
    t=1;
    ((n++))
  fi
done < $FILENAME

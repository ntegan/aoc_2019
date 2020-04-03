
PROG_NAME="./d2p2"
INPUT_FILE="input"

ANSWER_NOUN=""
ANSWER_VERB=""

re='.*output: ([0-9]*).*answer: ([0-9]*).*'
#ntegan@ntegan-ThinkPad-P51:~/aoc_2019.d/day02$ ./d2p2 input 1 2
#output: 490701
#answer: 102


for i in $(seq 0 99)      # noun
do
  for j in $(seq 0 99)    # verb
  do
    # Get prog output
    result="$($PROG_NAME $INPUT_FILE $i $j)"

    # Get output and answer
    if [[ $result =~ $re ]]
    then
      if [[ ${BASH_REMATCH[1]} == "19690720" ]]
      then
        echo "NOUN: " $i ", VERB: " $j
        echo "Correct answer: " ${BASH_REMATCH[2]}
      fi
    fi
  done
done


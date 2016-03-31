#!/bin/bash

for i in `seq 1 1000`;do

   COMMAND="grep -o "
   NUMB=$i
   NUMB_="'$NUMB'"
   COMMAND="$COMMAND $NUMB_ files | wc -l"
   RES=$(eval $COMMAND )
  # echo $COMMAND
  # echo $RES
   if [ "$RES" = "0" ]; then
       echo $NUMB
   fi

done

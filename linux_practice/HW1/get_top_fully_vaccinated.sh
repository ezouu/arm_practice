#!/bin/bash

FILE1=$1
k=$2

if [ $# -ne 2 ]; then
  echo "ERROR"
  exit 1
fi

# here we assign f4. f5 and f6 to each of their values from the data, respectively. 
# f4 Recip_County
# f5 Recip_State
# f6 Completeness_pct
# sort depending on the highest Completeness_pct value
sort -t, -k6,6nr $FILE1 | head -n $k | while read line; do #using head -n we can sort depending on highest f6 value, and k would refer to how many spaces we are looking for. 
  county=$(echo $line | cut -d, -f4) #extract each county and remove commas white returning it to f4
  state=$(echo $line | cut -d, -f5) #extract each state
  pct=$(echo $line | cut -d, -f6) #extract each perc

    #in the case of ties, resolve the ties by sorting them alphabetically. 
  if [[ $(echo $line | cut -d, -f6) == prev_pct ]]; then 
     sort -t, -k4,4 $FILE1 | head -n $k | while read line; do
       county=$(echo $line | cut -d, -f4)
       state=$(echo $line | cut -d, -f5)
       pct=$(echo $line | cut -d, -f6)
       echo "$county, $state, $pct"
     done
  else
  #if there are no ties, we can output the county state and percentage with the highest score
    prev_pct=$(echo $line | cut -d, -f6)
    echo "$county, $state, $pct"
  fi

done
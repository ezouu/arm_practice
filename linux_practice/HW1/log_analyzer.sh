#!/bin/bash

FILE1=$1
total_size=0
count=0
unique_codes=()

# Loop through log file
while read line; do

  # Extract fields, assign f9 and f10 to the values of the last two to get the values and unique codes. 
  code=$(echo $line | cut -d' ' -f9)
  size=$(echo $line | cut -d' ' -f10)

  # Treat "-" as 0 
  if [ "$size" = "-" ]; then
    size=0
  fi

  # add each size value to total_size
  total_size=$((total_size + size))
  #count the lines to calculate the average
  count=$((count + 1))

  # Track unique codes, we first check if the code is present within our unique codes.  If not, we can add code to unique codes array.
  if [[ ! " ${unique_codes[@]} " =~ " ${code} " ]]; then
    unique_codes+=("$code")
  fi

done < $FILE1

# Calculate average
avg=$((total_size / count))

# Print results
echo "$avg"
echo "${#unique_codes[@]}"
#!/bin/sh
time_wait=0.01
if [ -n "$1" ]; then
	time_wait=$1
else
	time_wait="0.01"
fi
tput init
clear
j=0
a=0
all_sym=()
max=0
while IFS= read -r line || [[ -n "$line" ]]; do
    for (( i=0; i < ${#line}; i++ )); do
		all_sym[$a]="$j $i ${line:$i:1}"
		a=$((a + 1))
    done
	max=${#line}
	j=$((j+1))
	printf "\n"
done
# echo $max
# sleep 10
# printf "\n\n"
# echo ${all_sym[@]}
#
# echo ${all_sym[4]}
shuffled_arr=()
while IFS= read -r -d '' item; do
    shuffled_arr+=("$item")
done < <(shuf -z -e "${all_sym[@]}")
# echo Исходный массив:
# printf "Элемент: %s\n" "${all_sym[@]}"
# echo Перемешанный:
# printf "Элемент: %s\n" "${shuffled_arr[@]}"
for i in "${shuffled_arr[@]}"; do
	args=($i)
	# printf "base: %d %d %d %s\n" $time_wait $i
	# printf "place: %d %d\n" ${args[0]} ${args[1]}
	# printf "char:%s\n" ${args[2]}
	tput cup ${args[0]} ${args[1]}
	printf "%s" ${args[2]}
	sleep $time_wait
done
tput cup ${max} $j
printf "\n"

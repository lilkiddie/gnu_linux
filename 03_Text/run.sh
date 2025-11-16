if [ "$#" -eq 1 ]; then
    pause=$1
elif [ "$#" -gt 1 ]; then
    echo "need exactly one argument"
    exit 1
fi

tput clear

declare -a positions=()
declare -a chars=()
j=-1
n=0

while IFS= read -r line; do
    for ((i = 0; i < ${#line}; i++)); do
        if [[ ${line:i:1} != ' ' && ${line:i:1} != '' ]]; then
            ((j++))
            positions+=("$n $i")
            chars[j]=${line:i:1}
        fi
    done
    ((n++))
done

perm=$(shuf -i 0-$j)
for ((i = 0; i <= j; i++)); do
    sleep $pause
    curr_pos=$(echo $perm | cut -d ' ' -f $((i + 1)))
    IFS=' ' read row column <<< "${positions[curr_pos]}"
    tput cup $row $column
    echo -n "${chars[curr_pos]}"
done

tput cup $n 0

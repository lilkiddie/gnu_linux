file ./range

set $counter = 0

break 40
commands
silent
set $counter = $counter + 1
if $counter >= 28 && $counter <= 35
printf "@@@ counter = %d\n", $counter
printf "@@@ start = %d\n", start
printf "@@@ end = %d\n", end
printf "@@@ step = %d\n", step
printf "@@@ current = %d\n", current
end
continue
end

run -100 100 3 > /dev/null
quit

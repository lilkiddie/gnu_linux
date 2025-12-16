file ./range

break 40
commands
silent
if current % 5 == 0
printf "@@@ start = %d\n", start
printf "@@@ end = %d\n", end
printf "@@@ step = %d\n", step
printf "@@@ current = %d\n", current
end
continue
end

run 1 12 > /dev/null
quit

set confirm off
set pagination off

file prog

break prog.c:41 if current % 5 == 0
commands
silent
printf "@@@ start=%ld, stop=%ld, step=%ld, current=%ld\n", start, stop, step, current
continue
end

run 1 12 > /dev/null
quit

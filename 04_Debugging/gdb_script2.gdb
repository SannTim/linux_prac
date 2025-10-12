set confirm off
set pagination off

file prog

set $iter = 0

break prog.c:41
commands
silent
set $iter = $iter + 1
if $iter >= 28 && $iter <= 35
    printf "@@@ start=%ld, stop=%ld, step=%ld, current=%ld, iter=%ld\n", start, stop, step, current, $iter
end
continue
end

run -100 100 3 > /dev/null
quit

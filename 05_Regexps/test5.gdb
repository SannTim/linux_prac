set args -c '(x)(y)' '\\1\\2' 'xy'
run
shell if ./esub -c '(x)(y)' '\\1\\2' 'xy' >/dev/null 2>&1; then echo "test5 (color mode): OK"; else echo "test5: FAIL (crashed or error)"; fi
quit

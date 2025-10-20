set args '[0-9]+' 'X' 'abc'
run
shell OUT_ESUB=$(./esub '[0-9]+' 'X' 'abc' 2>/dev/null); OUT_SED=$(echo 'abc' | sed -E 's/[0-9]+/X/'); if [ "$OUT_ESUB" = "$OUT_SED" ]; then echo "test2: OK"; else echo "test2: FAIL"; echo "esub: $OUT_ESUB"; echo "sed:  $OUT_SED"; fi
quit

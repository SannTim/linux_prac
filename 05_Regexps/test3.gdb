set args 'a(b)' '\\\\\\1' 'ab'
run
shell OUT_ESUB=$(./esub 'a(b)' '\\\\\\1' 'ab' 2>/dev/null); OUT_SED=$(echo 'ab' | sed -E 's/a(b)/\\\\\\1/'); if [ "$OUT_ESUB" = "$OUT_SED" ]; then echo "test3: OK"; else echo "test3: FAIL"; echo "esub: $OUT_ESUB"; echo "sed:  $OUT_SED"; fi
quit

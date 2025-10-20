set args '(a)(b)(c)' '\\3\\2\\1' 'abc'
run
shell OUT_ESUB=$(./esub '(a)(b)(c)' '\\3\\2\\1' 'abc' 2>/dev/null); OUT_SED=$(echo 'abc' | sed -E 's/(a)(b)(c)/\\3\\2\\1/'); if [ "$OUT_ESUB" = "$OUT_SED" ]; then echo "test4: OK"; else echo "test4: FAIL"; echo "esub: $OUT_ESUB"; echo "sed:  $OUT_SED"; fi
quit

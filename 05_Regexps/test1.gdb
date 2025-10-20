set args '([a-z]+)([0-9]+)' '\\2-\\1' 'hello123'
run
shell echo "=== Comparing with sed ==="
shell OUT_ESUB=$(./esub '([a-z]+)([0-9]+)' '\\2-\\1' 'hello123' 2>/dev/null); OUT_SED=$(echo 'hello123' | sed -E 's/([a-z]+)([0-9]+)/\\2-\\1/'); if [ "$OUT_ESUB" = "$OUT_SED" ]; then echo "test1: OK"; else echo "test1: FAIL"; echo "esub: $OUT_ESUB"; echo "sed:  $OUT_SED"; fi
quit

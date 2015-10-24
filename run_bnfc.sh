echo "--- Writing tex ---"
bnfc --latex Roller.cf
echo "
--- Writing sources ---"
bnfc -cpp -m -o src/ Roller.cf
echo "
--- Building ---
"
make -C src/
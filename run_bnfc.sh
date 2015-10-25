#!/bin/bash

# you might need to change the EOL characters to Unix style

set -e

echo "--- Writing docs ---"
bnfc --latex -o doc/ Roller.cf
pdflatex -output-directory=doc/ -quiet doc/Roller.tex

echo "
--- Writing sources ---"
bnfc --cpp -m -o src/ Roller.cf

if [ "$1" != "-nobuild" ]
then
	echo "
--- Building ---
"
	make -C src/
fi

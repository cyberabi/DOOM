#! /bin/bash

for file in *\.c; do
    [[ -e "$file" ]] || continue

    sed -i --debug -E 's/ >> FRACBITS/>>FRACBITS/g' $file
    sed -i --debug -E 's/ << FRACBITS/<<FRACBITS/g' $file
    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)->([a-zA-Z0-9_\\.]+)>>FRACBITS/FIXEDTOINT(\1->\2)/g' $file
    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)->([a-zA-Z0-9_\\.]+)<<FRACBITS/INTTOFIXED(\1->\2)/g' $file
    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)>>FRACBITS/FIXEDTOINT(\1)/g' $file
    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)<<FRACBITS/INTTOFIXED(\1)/g' $file
done
git status


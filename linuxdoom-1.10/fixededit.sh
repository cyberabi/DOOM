#! /bin/bash

for file in *\.c; do
    [[ -e "$file" ]] || continue

#    sed -i --debug -E 's/ >> FRACBITS/>>FRACBITS/g' $file
#    sed -i --debug -E 's/ << FRACBITS/<<FRACBITS/g' $file
#    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)->([a-zA-Z0-9_\\.]+)>>FRACBITS/FIXEDTOINT(\1->\2)/g' $file
#    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)->([a-zA-Z0-9_\\.]+)<<FRACBITS/INTTOFIXED(\1->\2)/g' $file
#    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)>>FRACBITS/FIXEDTOINT(\1)/g' $file
#    sed -i --debug -E 's/([a-zA-Z0-9_\\.]+)<<FRACBITS/INTTOFIXED(\1)/g' $file
done

for file in *\.[ch]; do
    [[ -e "$file" ]] || continue

#    sed -i --debug -E 's/= ([0-9]+)\*FRACUNIT/= INTTOFIXED(\1)/g' $file
#    sed -i --debug -E 's/= FRACUNIT\*([0-9]+)/= INTTOFIXED(\1)/g' $file
#    sed -i --debug -E 's/^\t([0-9]+)\*FRACUNIT,/\tINTTOFIXED(\1),/' $file
#    sed -i --debug -E 's/^\tFRACUNIT\*([0-9]+),/\tINTTOFIXED(\1),/' $file
#    sed -i --debug -E 's/FRACUNIT/INTTOFIXED(1)/g' $file
    sed -i --debug -E 's/> ([0-9]+)\*FIXEDUNIT/> INTTOFIXED(\1)/g' $file
    sed -i --debug -E 's/> FIXEDUNIT\*([0-9]+)/> INTTOFIXED(\1)/g' $file
    sed -i --debug -E 's/< ([0-9]+)\*FIXEDUNIT/< INTTOFIXED(\1)/g' $file
    sed -i --debug -E 's/< FIXEDUNIT\*([0-9]+)/< INTTOFIXED(\1)/g' $file
    sed -i --debug -E 's/FIXEDUNIT/INTTOFIXED(1)/g' $file
done

git status


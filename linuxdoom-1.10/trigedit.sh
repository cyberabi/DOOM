#! /bin/bash
# IMPORTANT: Order of execution matters

for file in *\.c; do
    [[ -e "$file" ]] || continue

#    sed -i --debug -E 's/finesine\[(.+)\]/FINESINE(\1)/g' $file
#    sed -i --debug -E 's/finecosine\[(.+)\]/FINECOSINE(\1)/g' $file
#    sed -i --debug -E 's/finetangent\[(.+)\]/FINETANGENT(\1)/g' $file
#    sed -i --debug -E 's/tantoangle\[(.+)\]/TANTOANGLE(\1)/g' $file
done

for file in *\.[ch]; do
    [[ -e "$file" ]] || continue

    sed -i --debug -E 's/FRACUNIT/FIXEDUNIT/g' $file
    sed -i --debug -E 's/FIXEDUNIT\*([0-9]+)/INTTOFIXED(\1)/g' $file
    sed -i --debug -E 's/([0-9]+)\*FIXEDUNIT/INTTOFIXED(\1)/g' $file

done

git status


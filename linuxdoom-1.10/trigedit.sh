#! /bin/bash

for file in *\.c; do
    [[ -e "$file" ]] || continue

    sed -i --debug -E 's/finesine\[(.+)\]/FINESINE(\1)/g' $file
    sed -i --debug -E 's/finecosine\[(.+)\]/FINECOSINE(\1)/g' $file
    sed -i --debug -E 's/finetangent\[(.+)\]/FINETANGENT(\1)/g' $file
    sed -i --debug -E 's/tantoangle\[(.+)\]/TANTOANGLE(\1)/g' $file
done
git status


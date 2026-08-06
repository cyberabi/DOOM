#! /bin/bash
# Check only the comments for incorrect changes
# NOTE: This awk script is imperfect and will display the
# entire line(s) for /* */ comments in the middle of lines
# awk 'match($0, /\/\//) {print "//"substr($0, RSTART + RLENGTH)}; /\/\*/ {blk=1}; {if(blk) print $0}; /\*\// {blk=0}' $file
for file in */*\.[ch]; do
    echo; echo $file:
    comments=$(awk 'match($0, /\/\//) {print "//"substr($0, RSTART + RLENGTH); next} /\/\*/,/\*\// {print "/*"substr($0, RSTART + RLENGTH)"*/"}' $file)
#    echo "$comments"
    grep CHAR8 <<< "$comments"
    grep CHAR8 <<< "$comments"
    grep SHORT16 <<< "$comments"
    grep SHORT16 <<< "$comments"
    grep INT32 <<< "$comments"
    grep LONG32 <<< "$comments"
    grep LONGLONG64 <<< "$comments"
done


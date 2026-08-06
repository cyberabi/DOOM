#! /bin/bash
# This script will change most generic type declarations (int, long)
# to macros that are explicit about the number of bits these types
# used on Intel 32-bit linux. For example, int becomes INT32 and
# long becomes LONG32. The order of these sed passes matters.
#
# NOTE: These sed scripts are imperfect and will occasionally change
# a comment or otherwise miss a type declaration (such as an untyped
# 'register' declaration). You have to manually change the 'rcsid'
# strings back to 'char'. Additional scripts such as 'comments.sh'
# help detect these issues for manual correction.

for file in */*\.[ch]; do
    [[ -e "$file" ]] || continue

    sed -i -E "s/(\(|^| |,|\t)signed long long( |,|\*|\t|\)|$)/\1LONGLONG64\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)signed long int( |,|\*|\t|\)|$)/\1LONG32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)signed long( |,|\*|\t|\)|$)/\1LONG32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)signed int( |,|\*|\t|\)|$)/\1INT32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)signed short int( |,|\*|\t|\)|$)/\1SHORT16\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)signed short( |,|\*|\t|\)|$)/\1SHORT16\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)signed char( |,|\*|\t|\)|$)/\1CHAR8\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)signed( |,|\*|\t|\)|$)/\1INT32\2/g" $file

    sed -i -E "s/(\(|^| |,|\t)unsigned long long( |,|\*|\t|\)|$)/\1ULONGLONG64\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)unsigned long int( |,|\*|\t|\)|$)/\1ULONG32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)unsigned long( |,|\*|\t|\)|$)/\1ULONG32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)unsigned int( |,|\*|\t|\)|$)/\1UINT32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)unsigned short int( |,|\*|\t|\)|$)/\1USHORT16\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)unsigned short( |,|\*|\t|\)|$)/\1USHORT16\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)unsigned char( |,|\*|\t|\)|$)/\1UCHAR8\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)unsigned( |,|\*|\t|\)|$)/\1UINT32\2/g" $file

    sed -i -E "s/(\(|^| |,|\t)long long( |,|\*|\t|\)|$)/\1LONGLONG64\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)long int( |,|\*|\t|\)|$)/\1LONG32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)long( |,|\*|\t|\)|$)/\1LONG32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)int( |,|\*|\t|\)|$)/\1INT32\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)short int( |,|\*|\t|\)|$)/\1SHORT16\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)short( |,|\*|\t|\)|$)/\1SHORT16\2/g" $file
    sed -i -E "s/(\(|^| |,|\t)char( |,|\*|\t|\)|$)/\1CHAR8\2/g" $file
done
git status


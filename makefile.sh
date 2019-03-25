#!/bin/bash

for num in 90 180 270
do
    mkdir ${num}
    cp input.dat a.out ${num}
    echo -e "Tranexamic_acid\n 26\n ${num}\n\n" | ./rotate
    mv new.dat ${num}
    cd ${num}
    sed '57,82d' "input.dat" > "c.dat"
    echo y | mv "c.dat" "input.dat"
    sed -i '56 r new.dat' "input.dat"
    dos2unix "input.dat"
    rm new.dat
    cd ..
done

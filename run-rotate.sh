#!/bin/bash

#创建文件夹并复制入所需文件，生成新坐标
for i in 12 17 22 27 32 37 42 47 
do
	mkdir ${i}
	cp "input.dat" "a.out" "r.out" ${i}
	cd ${i}
	echo ${i} | ./r.out
	sed '63,94d' "input.dat" > "r.dat"
	echo y | mv "r.dat" "input.dat"
	sed -i '62 r new.dat' "input.dat"
	dos2unix "input.dat"
    echo "This is ${name}"
    #./"a.out"
    rm r.out new.dat
	cd ..
done

echo $SECONDS > "time.dat"



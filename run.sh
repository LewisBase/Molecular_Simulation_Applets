#!/bin/bash

#创建文件夹并复制入所需文件，生成新坐标
for ((i=3; i<90; i+=5))
do
	mkdir ${i}
	cp "input.dat" "a.out" "c.out" ${i}
	cd ${i}
	ini=18
	increasement=`expr ${i} - ${ini}`
	echo ${increasement} | ./c.out
	sed '72,112d' "input.dat" > "c.dat"
	echo y | mv "c.dat" "input.dat"
	sed -i '71 r new.dat' "input.dat"
	dos2unix "input.dat"
	cd ..
done

#进入文件夹，取代坐标部分，开始计算
for name in `ls`
do
	if [ -d ${name} ]
	then
		cd ${name}
		echo This is NO.${name}
		./"a.out"
		rm new.dat c.out
		cd ..
	fi
done

echo $SECONDS > "time.dat"



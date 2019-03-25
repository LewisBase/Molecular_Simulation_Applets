#!/bin/bash

#整体处理计算流程：
#	运行脚本select.sh得到距离沿z轴的变化情况，从中以0.4为差值进行筛选，得到的结果写入list.sh
#	运行脚本run_USfinal.sh，进行最终的抽样计算

#	文件树
#	.top, .ndx位于总文件夹下(e.g. Acetylasticylic_acid)
#	distance.pl D.out select.sh list.dat run_USfinal.sh以及md_umbrella.mdp位于Pre/Pull下
#	注意: distance.pl中计算分子名称需改动
 
for name in `cat list.dat`
    do
        cd CON
        mkdir con${name}
        gmx_d grompp -f ../md_umbrella.mdp -c conf${name}.gro -p ../../../USbox.top -n ../../../index.ndx -o con${name}/md${name}.tpr
        cd con${name}
        gmx_d mdrun -v -deffnm md${name} -pf pull${name}.xvg -px pullx${name}.xvg
        cd ..
        cd ..
    done         

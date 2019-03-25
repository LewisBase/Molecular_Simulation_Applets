#!/bin/bash
echo "去除轨迹周期化"
sleep 2

echo 0 | gmx_d trjconv -f traj_comp.xtc -o md_noPBC.xtc -pbc mol -ur compact

echo "计算均方差位移RMSD"
sleep 2

echo 0 0 | gmx_d rms -f md_noPBC.xtc -o rmsd.xvg

echo "建立索引文件,自行选择组"
sleep 2

gmx_d make_ndx -f confout.gro -o index.ndx

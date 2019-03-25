#!/bin/bash
mkdir xvg

echo "Insert New Group Message"
read go
echo -e "a S\n a N\n a OW\n q\n\n" | gmx_d make_ndx -f confout.gro -n index.ndx -o index.ndx

echo "Pressure Message, input ENTER"
read go
echo -e "Pres-XX\n Pres-YY\n Pres-ZZ\n\n" | gmx_d energy -f ener.edr -o xvg/Pres.xvg

echo "Density Message, input ENTER"
read go
echo -e "System\n SDShead\n SDStail\n C4mimhead\n C4mimtail\n SOL\n HEX\n BR\n NA\n\n" | gmx_d density -f md_noPBC.xtc -s topol.tpr -n index.ndx -d z -ng 8 -symm -o xvg/density.xvg

echo "H bonds between SDS and SOL, input ENTER"
read go
echo -e "SDS\n SOL\n\n" | gmx_d hbond -f md_noPBC.xtc -s topol.tpr -n index.ndx -num xvg/hdSW.xvg

echo "Order parameter, input ENTER"
read go
echo "Input the group number to calculate"
read number
for((i=0;i<${number};i++))
do
    echo "Input the name of group"
    read name
    gmx_d order -f md_noPBC.xtc -s topol.tpr -n ${name}order.ndx -d z -od xvg/${name}order.xvg
done

echo "tilt angle, input ENTER"
read go
echo -e "SDS\n C4m\n\n" | gmx_d gangle -f md_noPBC.xtc -s topol.tpr -n tilt.ndx -g1 vector -group1 -g2 z -oav xvg/angleav.xvg -oall xvg/angleall.xvg -oh xvg/angleh.xvg

echo "Distance of tail, input ENTER"
read go
echo -e "SDS\n C4m\n\n" | gmx_d distance -f md_noPBC.xtc -s topol.tpr -n tilt.ndx -oav xvg/distav.xvg -oh xvg/disth.xvg -oall distall.xvg

echo "RDF Message, input ENTER"
read go
echo -e "S\n S\n N\n OW\n NA\n BR\n\n" | gmx_d rdf -f md_noPBC.xtc -s topol.tpr -n index.ndx -o xvg/rdfS.xvg
echo -e "N\n N\n OW\n NA\n BR\n\n" | gmx_d rdf -f md_noPBC.xtc -s topol.tpr -n index.ndx -o xvg/rdfN.xvg

echo "MSD Message, input ENTER"
read go
echo -e "SDS\n\n" | gmx_d msd -f md_noPBC.xtc -s topol.tpr -n index.ndx -lateral z -beginfit 1000 -endfit 4000 -ngroup 1 -o xvg/msdSDS.xvg
echo -e "C4m\n\n" | gmx_d msd -f md_noPBC.xtc -s topol.tpr -n index.ndx -lateral z -beginfit 1000 -endfit 4000 -ngroup 1 -o xvg/msdC4m.xvg

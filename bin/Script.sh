#!/bin/bash


echo "Début de traitement"
myArr=("3.0" "4.4" "4.6" "4.8" "5.0")
div=10
string1="Exp_"
string2="MeV_10M"

#for idx in ${!myArr[*]}
for ((idx=7; idx<=7; idx++))
do
    while [[ $(pgrep -x ENLCEDRICSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
        #Init
    #value=${myArr[$idx]}
    value=$(bc <<< "scale=1 ; $idx/$div")
    #value=$idx
    #n=1
    #value1=$(bc <<< "scale=1 ; $idx+1")
    #echo $value1
    #name="${string1}${value}${string2}" 
    #echo $name
    idx_fichier=$(($idx))
        echo Index : $idx / Fichier : $value
        # Creation du fichier a partir du fichier de base (fichier temporaire)
        cp vrml_base.mac base_$idx_fichier_bis.mac
        # Mise en place de la variable
        #sed -e "s/%energy1/$value/g" base_$idx_fichier_bis.mac > base_bis_$idx_fichier.mac
	#sed -e "s/%energy2/$value1/g" base_bis_$idx_fichier.mac > base_$idx_fichier.mac
        sed -e "s/%energy/$value/g" base_$idx_fichier_bis.mac > base_$idx_fichier.mac
        # Suppression fichier temporaire
        rm base_$idx_fichier_bis.mac
	rm base_bis_$idx_fichier.mac
	#./ENLCEDRICSim Electron_Uniform_${value}_MeV_1M 1000000 base_$idx_fichier.mac &
	./ENLCEDRICSim Electron_Exp_${value}MeV_100M 100000000 base_$idx_fichier.mac &
	#./ENLCEDRICSim $name 10000000 base_$idx_fichier.mac &
	#./ENLCEDRICSim Exp_${myArr[$idx]}MeV_100M 100000000 vrml.mac &
	sleep 5
done
echo "Fin de traitement"



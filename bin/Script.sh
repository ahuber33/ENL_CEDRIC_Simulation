 #!/bin/bash


echo "Début de traitement"
myArr=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10")

for idx in ${!myArr[*]}
do
    while [[ $(pgrep -x ENLCEDRICSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
        #Init
        value=${myArr[$idx]}
        idx_fichier=$(($idx))
        echo Index : $idx / Fichier : $value
        # Creation du fichier a partir du fichier de base (fichier temporaire)
        cp vrml_base.mac base_$idx_fichier_bis.mac
        # Mise en place de la variable
        sed -e "s/%energy/$value/g" base_$idx_fichier_bis.mac > base_$idx_fichier.mac
        # Suppression fichier temporaire
        rm base_$idx_fichier_bis.mac
	./ENLCEDRICSim Exp_${myArr[$idx]}MeV 100000000 base_$idx_fichier.mac &
	#./ENLCEDRICSim Exp_${myArr[$idx]}MeV_100M 100000000 vrml.mac &
	sleep 5
done
echo "Fin de traitement"



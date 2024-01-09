# ENLCEDRICSim for Studies of CEDRIC's electrons  spectrometer. [huber@ecnbg.in2p3.fr, huberarnaud@gmail.com]

# INSTRUCTIONS TO USE THE SIMULATION
# - Download the VMWare Geant4.11.0.1 from https://heberge.lp2ib.in2p3.fr/G4VM/index.html
# - Copy all the files from ENL_egn_Simulation folder (https://github.com/ahuber33/ENL_CEDRIC_Simulation)
# - Create a build folder in the ENL_CEDRIC_Simulation folder and go inside.
# - Use this command : "cmake -DGeant4_DIR=$G4COMP ../" and compile it with make
# - The executable ENLCEDRICSim will be add to your bin folder
# - If you want to have a visualization, launch this command : "./ENLCEDRICSim [name of ROOT file ]". It will generate 1 particle according to the vis.mac with QT and you will have a ROOT file with the name you gave in response located in the Resultats folder.
# - If you want to have statistics without the visualization, use this command : "./ENLCEDRICSim [name of ROOT file] [number of events generated] [name of macro]". Personnaly, I used the vrml.mac but you can create another one. Just to remember that you need to write the name of your macro when you launch the simulation.
# - An ENLCEDRICSim.cfg file is located in bin directory. All the dimensions necessary are in this file to avoid recompilation when you want to change some parameters. If you add some other dimensions, don't forget to add the variables in Geometry.cc.
# - Based on G4EmStandardPhysics_option3 with additional Photonuclear process pour gammas. All neutron interactions are also taken into account with HP data for neutrons.
# - DO NOT HESITATE TO REPORT BUGS OR ANY IDEAS THAT WILL IMPROVE THE SIMULATION !!!!

# Commit #1 [ENLCEDRICSim.0.0.0]
# - Structure from ENLegnSim with addition of Thomas Bonnet's code.
# - Add of photon nuclear process for gammas (process g,n)
# - Simulation's working for Thomas's code !!!
# - Need to work to implement some features on Trees (code adaptation)

# Commit #2 le 20/05/2022 [ENLCEDRICSim.0.1.0]
# - Changement de la nature du code (même géométrie) mais sous base de ficgiers ROOT contenant des Tree
# - Création de plusieurs variables permettant de débuguer correctement l'ensemble des interactions (e-/gamma/autres) par Stack
# - Histo du code base gardé pour affichage énergie déposée
# - Mise en application de l'atténuation des PSL détectés en fonction de la profondeur d'interaction de la particule.
# - Accès aux positions des particules dans le Stack via le pré et post step avec un générateur aléatoire de la position entre ces deux bornes.
# - Mise en place dans le SteppingAction d'un algo permettant de déterminer si un dépôt d'énergie est lié à la base à un électron ou à un gamma.
# - Supression de la fonction SetStepParams -> Utilisation uniquement de la fonction SetTrackingID
# - Adaptation de l'ensemble du code avec le fichier de config afin de pouvoir rapidement varier les épaisseurs de stack si besoin sans recompiler
# - Changement du matériau du disque en alu qui était en tantale à la base lors de la récupération du code.
# - Cut physique défini à 100 nm !!!
# - Lecture du fichier de config dans Geomety.cc et RunAction afin de pouvoir appeler les fonctions défini dans le RunAction au niveau du Steppping Action. Doublon donc pas optimale. Y réfléchir par la suite pour enlever ce doublon.
# - Vérifications de la bonne tenue du code avec des comparaisons de données e-/gamma/protons sur une IP seule
# - Nécessité de pousser encore les inverstigations sur la réponse du stack.

# Commit #3 le 09/01/2024 [ENLCEDRICSim.0.2.0]
# - Passage du code sur la version 11.2.0 de GEANT4
# - Passage de Atom vers Visual Code Studio avec notamment création d'une branche save permettant de push les changements d'une journée avant demerge sur la branche principale
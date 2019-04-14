# Prérequis

## Compilation du code
	sudo apt install make
	sudo apt install g++
## Installation de SDL2
	sudo apt install libsdl2-dev libsdl2-2.0-0 -y
	sudo apt install libjpeg9-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
    

# Commandes exécutables dans le répertoire courant

## make
		Compilation du code
## make clean
		Supprime les .o
## make veryclean
		Supprime les .o et le .out
## make run
		Compilation du code et lancement du jeu
## ./bin/PolyQuarto.out
		Lancement du jeu (nécessite le code compilé)


# Répertoires

## bin
		Contient l'exécutable
## src/core
		Contient tout le code du modèle
## src/sdl2
		Contient tout le code concernant l'affichage avec SDL2 (vue et contrôleur)
## data
		Contient les images
## obj
		Contient les .o

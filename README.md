# visu3D

Temps consacré : environ 3 à 4 soir par semaine, temps variable (maximum 2h30) et un week end (environ 8h sur le we)

La première semaine, j'ai plus perdu du temps car je ne me souvenais plus qu'il y avait qt creator, c'est quelqu'un du stage qui m'a un peu aidé à démarrer et m'a remis sur les rails.

Je me suis aidée du projet des tsi pour comprendre comment faire la "connexion" entre la fentre principale et le widget opengl, j'ai perdu pas mal de temps avant de trouver

Développement avec qt et sous windows


### pas fait
	- importer fichier cityjson -> item bloqué dans la séléction
	- scène centrée sur l'objet cad sur le milieu de la scène
	- supprimer couche ply cityjson et obj

### un peu commencé mais pas trop
	- zoomer/dezoomer avec la molette de la souris -> la fonction wheelEvent est implémentée mais la facteur de zoom n'est pas utilisé. J'ai voulu l'utiliser avec la matrice de projection mais je n'arrivais plus à visualiser la scène donc j'ai commenté la matrice de projection (et donc le zoom) donc pas de projection non plus
	- cacher et réafficher des couches -> normalement quand on les ajoute, on a une checkbox cochée qui apparait avec le nom du fichier. j'aurai certainement du stocker l'objet affiché dans une variable et utiliser un pointeur pour visible/non visible mais je n'ai pas eu le temps de me pencher plus dessus

### normalement ok
	- possibilité d'importer ply obj et cityjson
	- importation obj (la plupart du code ne vient pas de moi, j'ai voulu reprendre le projet opengl pour le chargement mais je n'ai pas réussi à l'adapter en qt)
	- importation ply
	- droite&gauche, haut&bas avec le clic droit de la souris
	- faire tourner la scène avec le clic gauche de la souris
	- changer la couleur d'affichage -> fait pour le fond, je ne sais pas si c'est bien  ça qui était demandé

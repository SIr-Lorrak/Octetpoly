# Octetpoly

Contributeurs :
	-Sebastien HOAREAU p1805503
	-Laëtitia LAPORTE p1804311
	-Guillaume COGONI p1800070
	-Jonathan BRESSAT p1802864


Octetpoly est un jeu de plateau génial dans lequel tu devras gérer ton flouze. 4 joueurs sans pitié s'affrontent pour ruiner leurs adversaires !! 

Octetpoly reprend les principes du Monopoly classique mais les arranges à sa sauce, par exemple les rues sont maintenant des entreprises et les gares, des banques.
À la place de payer des maisons vous investissez dans des activités pour chacunes de vos entreprises. Les investissements illégaux coûtent moins cher et rapportent plus.
Mais attention ils font baisser votre karma et les malus du jeu serons plus durs pour vous (plus cher pour sortir de prison, les impôts seront aussi plus cher, etc).

De plus, Octetpoly intègre une mécanique d'évènement : à la fin de chaque tour les joueurs en liberté auront une petite chance (ou malchance) de déclancher
un évènement, cet évènement pourras être bénéfique (bonus quand on gagne) ou maléfique (malus quand on perd), cela dépendra de votre karma.
Les évènements/mini-jeux sont au nombre de quatre :
-Hacking : Des voleurs te hack ! Vite ! Tapes les commandes indiquées pour déjouer leur plan machiavélique. Si tu prends trop de temps, ils te voleront tous tes sous !
-Clicker : C'est le moment d'envoyer des pubs ! Cliques le plus vite possible pour gagner de l'argent !
-Lucky : Quelle chance ! Vous trouvez deux cartes chance par terre ! Tu peux choisir une ou les jeter !
-Escape : Oh non ! La police vous a retrouvé, enfuyez vous vite ou vous serez jeté en prison ! Il ne fallait pas faire trop de mauvaises actions !



Version démo rendu final (version 1.0.0) :

Dans cette version toutes les fonctionnalités proposées au départ ont été réalisées !
cependant il n'est pas impossible que nous reprenions le projet à l'avenir pour ajouter un mode réseau, ajouter des animations lors de l'avancement des pions, etc.


Commandes : 
	-pour re-compiler placez vous à la racine du projet et faites "make clean" puis "make"
	-pour executer les programmes soit "bin/Octetpoly_TXT" pour la version textuelle, soit "bin/Octetpoly_SDL" pour la version graphique
	-pour générer la doc (toujours à la racine du projet) faites "doxygen doc/doxyfile"
	-pour afficher la doc faites "firefox doc/html/index.html"


Le code source se trouve dans le répertoire src/ et son arborescence.
Les exécutables sont dans le répertoire bin/ .
La documentation (diagrammes et présentation) est dans le répertoire doc/ et les assets se trouvent dans le dossier data/ .

compile sous linux

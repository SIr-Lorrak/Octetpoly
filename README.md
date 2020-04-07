# Octetpoly

Octetpoly est un jeu de plateau génial dans lequel tu devras gérer ton flouze. 4 joueurs sans pitiés s'affrontent pour ruiner leurs adversaires !! 

Octetpoly reprend les principes du Monopoly classique mais les arranges à sa sauce, par exemple les terrains sont maintenant des entreprises et les gares, des banques.
À la place de payer des maisons vous investissez dans des activités pour chaqu'unes de vos entreprises. Les investissements illégaux coûtent moins cher et rapportent un peu plus.
Mais attention ils font baisser votre karma et les malus du jeu serons plus durs pour vous (plus cher pour sortir de prison, les impots seront aussi plus cher, etc).

De plus, Octetpoly intègre une mécanique de minis jeux : à la fin de chaque tour les joueurs en liberté auront une petite chance (ou malchance) de déclancher
un mini jeu, ce mini jeu pourras être bénéfique (bonus quand on gagne) ou maléfique (malus quand on perd), cela dépendra de votre karma.
Les évennements/mini jeu sont au nombre de quatre :
-Hacking : Des voleurs te hack ! Vite ! Tape les commandes indiquées pour déjouer leur plan machiavélique. Si tu prends trop de temps, ils te volerons tous tes sous !
-Clicker : C'est le moment d'envoyer des pubs ! Clique le plus vite possible pour gagner de l'argent !
-Lucky : Quelle chance ! Vous trouvez une carte chance par terre ! Tu peux choisir de prendre son effet ou pas !
-Escape : Oh non ! La police vous a retrouvé, enfuyez vous vite ou vous serez jeté en prison ! Il ne fallait pas faire trop de mauvaise action !



Première démo (version 0.0.1) :

Dans la première démo d'Octetpoly, le nom de l'executable du jeu (en affichage txt seulement) est Octetpoly_TXT, il se trouve dans le répertoire bin/
make fera 3 executables mais seulement Octetpoly_TXT est joueable pour le moment.

Dans cette version vous pouvez faire une partie de 0 a 4 joueurs réels. Si vous ne jouez pas à quatre, les autres joueurs seront remplacés par des bots (Ordi ou IA).
Les bots ne peuvent qu'avancer et ne peuvent, pour l'instant, pas acheter ni investir.
Le jeu ne détecte pas encore les joueurs en faillite donc vous pouvez continuer à jouer alors que votre argent est négatif (=> facilement règlable).

Dans cette version il y a un mini jeu sur les quatre, le Hacking.

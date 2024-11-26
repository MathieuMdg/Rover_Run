# Rover_Run Project

Etudiants : Mathieu MENDOUGA, Noah GUICHARD, Gabriel GENIEZ

-Lien vers le dépot Gith : https://github.com/MathieuMdg/Rover_Run

## Cloner le dêpot
    git clone https://github.com/MathieuMdg/Rover_Run.git


## Présentation du projet
Le projet Rover_Run est un jeu où les joueurs guident un robot à travers le terrain accidenté de Mars, en essayant d’atteindre une station de base en toute sécurité. Le rover dispose de plusieurs mouvements pour se déplacer sur le sol martien. Il est contrôlé par des saisies utilisateur, ce qui allie prise de décisions stratégiques et mécaniques ludiques pour offrir une expérience de jeu divertissante.


## Contexte du jeu
MARC, un rover envoyé sur Mars, a perdu son autonomie à la suite de problèmes avec ses systèmes de navigation. Son seul moyen de se déplacer est d’exécuter les ordres envoyés par l’utilisateur. L’objectif est de permettre à MARC (le rover) d’atteindre une base située sur Mars. Pour ce faire, MARC dispose de plusieurs mouvements pour se déplacer sur le sol martien. Une partie se déroule en plusieurs phases :

- Durant chaque phase, un nombre de mouvements sera tiré au hasard parmi une liste de mouvements possibles.
- L’utilisateur devra choisir les mouvements les plus judicieux pour rapprocher MARC de la base.
- Cependant, le sol martien est très hostile, ce qui complique les déplacements. Il existe différents types de cases : PLAIN, ERG, ZONE_SOLAIRE, ZONE_MORTE, REG, CREVASSE, PENTE, BASE.

Chaque type de case présente des spécificités qui peuvent soit aider, soit désavantager MARC.


## Fonctionnalités
- Contrôle du rover via des saisies utilisateur.
- Simulation d’un environnement martien avec obstacles.
- Mode de navigation autonome.
- Options permettant de modifier les conditions de jeu.
- Chargement et création de cartes martiennes.


## Présentation des cases
- **PLAIN** : Les cases PLAIN n’ont aucune influence sur les mouvements de MARC.

- **ERG** : Si MARC commence son mouvement depuis une case ERG :
        - Son prochain mouvement est réduit :
            Avancer de 10 m et reculer ne produisent aucun déplacement.
            Avancer de 20 m n’avance que de 10 m.
            Avancer de 30 m n’avance que de 20 m.
        - Les rotations sont limitées :
            Un demi-tour permet de tourner à gauche ou à droite d’un quart de tour seulement.
  
- **REG** : Si MARC termine un mouvement sur une case REG :
        Le rover est secoué, ce qui dégrade ses performances.
        MARC ne pourra effectuer que 4 mouvements au total lors de cette phase.
  
- **CREVASSE** : Zone extrêmement dangereuse pour MARC :
        Si le rover passe sur une case CREVASSE, il y tombe et met fin à sa mission.
  
- **PENTE** : Lorsque MARC commence une phase sur une case PENTE :
        Il glisse automatiquement sur une case adjacente.
        La case sur laquelle il arrive est imprévisible à cause des perturbations de signal.
  
- **ZONE_MORTE** : Si MARC commence une phase sur une case ZONE_MORTE :
        Les interférences empêchent les instructions d’arriver correctement.
        MARC s’oriente aléatoirement dans une autre direction.
  
- **ZONE_SOLAIRE** : Si MARC commence une phase sur une case ZONE_SOLAIRE :
        L’afflux d’énergie solaire améliore temporairement ses capacités.
        MARC obtient un mouvement supplémentaire pour cette phase.

## Étude de Complexité

### Phase de construction de l'arbre

#### Méthode 1 
La complexité de la fonction **createTree** dépend de la complexité des fonctions countEltHList, addRoot et addNodeRec :
- countEltHList(*phase_move) : Cette fonction compte les éléments d'une liste, sa complexité est (O(n)), où (n) est le nombre d'éléments dans phase_move.  
- addRoot(tree, ROOT, nbMove, phase_move, loc, map) : Cette fonction ajoute une racine à l'arbre. Elle effectue des opérations constantes, sa complexité est (O(1)).  
- addNodeRec(tree, tree->root, map, max_depth) : Cette fonction est récursive et construit l'arbre. La complexité dépend de la profondeur maximale de l'arbre (max_depth) et du nombre de nœuds fils par nœud. Si chaque nœud a en moyenne (k) fils et que l'arbre a une profondeur maximale de (d), la complexité est (O(k^d)).  

En combinant ces éléments, la complexité globale de la fonction createTree est dominée par la complexité de addNodeRec, ce qui donne une complexité de (O(k^d)), où (k) est le nombre moyen de fils par nœud et (d) est la profondeur maximale de l'arbre.

Temps d'exécution de createTree: 0.001000 secondes (Test éfféctué avec les fonctions de la librairie <time.h>).

#### Méthode 2
La complexité de la fonction createTreeV2 peut être analysée comme suit :  
- Allocation mémoire pour l'arbre vide : "p_tree tree = (p_tree) malloc(sizeof(t_tree));" Cette opération est de compléxité (O(1)).  
- Initialisation de l'arbre vide : "*tree = createEmptyTree();" Cette opération est de complexité (O(1)).  
- Définition du nombre de noeuds fils de la racine :  "int nbMove = 1;" Cette opération est de compléxité (O(1)).  
- Ajout de la racine : "addRoot(tree, ROOT, nbMove, phase_move, loc, map);" Cette opération est (O(1)) car elle ne dépend pas de la taille de l'entrée.  
- Appel de la fonction récursive pour la création de tous les noeuds : "addNodeRecV2(tree, tree->root, map, max_depth);" La complexité de cette opération dépend de la complexité de addNodeRecV2.  
- Complexité de addNodeRecV2 : La fonction addNodeRecV2 est une fonction récursive qui parcourt tous les noeuds de l'arbre jusqu'à une profondeur maximale max_depth. Pour la méthode 2 chaque noeud possède 1 fils donx la complexité de cette fonction est (O(1^{max_depth})).

En combinant toutes ces opérations, la complexité totale de la fonction createTreeV2 est dominée par la complexité de addNodeRecV2, ce qui donne une complexité de (O(1)).

Temps d'exécution de createTreeV2: <0.000000 secondes (Test éfféctué avec les fonctions de la librairie <time.h>).

### La phase de recherche d’une feuille de valeur minimale parmi toutes les feuilles de l’arbre

#### Méthode 1
La complexité de la fonction "searchBetterPathNode" dépend de la structure de l'arbre.
- Boucle While :  La boucle "while(node != searchBetterNode(node))" parcourt les nœuds de l'arbre jusqu'à ce qu'un nœud feuille soit atteint. Dans le pire des cas, cette boucle traverse la hauteur de l'arbre en entier, qui est (O(h)), où (h) est la hauteur de l'arbre.
- Appel de fonction searchBetterNode : Dans la boucle while, "searchBetterNode(node") est appelé. Cette fonction parcourt tous les enfants d'un nœud pour trouver celui avec le coût minimum. Si un nœud a (k) enfants, la complexité de "searchBetterNode" est (O(k)).

Par conséquent, la complexité totale est (O(h * k)), où (h) est la hauteur de l'arbre et (k) est le nombre maximum d'enfants qu'un nœud peut avoir.

Temps d'exécution de searchBetterPathNode: <0.000000 secondes (Test éfféctué avec les fonctions de la librairie <time.h>).

#### Méthode 2
La fonction printLastNodeTreeV2 a une complexité de (O(d)), où (d) est la profondeur de l'arbre. La boucle while parcourt les nœuds de l'arbre jusqu'au dernier noeud (noeud fueille). Dans le pire des cas, cette boucle itère une fois pour chaque niveau de l'arbre, ce qui donne une complexité de (O(d)), où (d) est la profondeur de l'arbre.
Ainsi, la complexité totale de la fonction est (O(d)).

Temps d'exécution de printLastNodeTreeV2: <0.000000 secondes (Test éfféctué avec les fonctions de la librairie <time.h>).

### Calcul du chemin de la racine vers cette feuille

La complexité de la fonction findNode peut être analysée comme suit : 
La boucle for sur la profondeur s'exécute depth fois. À chaque itération de cette boucle, il y a une boucle interne qui parcourt les fils du noeud actuel. Cette boucle interne s'exécute nbSons fois, où nbSons est le nombre de fils du noeud actuel.
La boucle interne est imbriquée dans la boucle externe. Donc, la complexité de la boucle interne est (O(nbSons)) et celle de la boucle externe est (O(depth)).
La complexité totale de la fonction est donc (O(depth * nbSons)).

Temps d'exécution de findNode: <0.000000 secondes (Test éfféctué avec les fonctions de la librairie <time.h>).

### Un exemple complet de guidage de MARC depuis sa position d’origine vers la station de base

### Automatique

- La boucle principale "while" continue tant que le robot n'a pas atteint la base et que le signal du robot est actif. Sa complexité dépend du nombre de mouvements nécessaires pour atteindre la base.
- Boucle for pour sélectionner les mouvements. Cette boucle s'exécute nbMaxMove fois et est donc de complexité O(nbMaxMove).
- Appel de createTree ou createTreeV2, La complexité dépend de la profondeur maximale de l'arbre (max_depth), du nombre de mouvements disponibles (nbMoveSelect) et de la méthode de construction utilisée.
- Appel de searchBetterPathNode ou printLastNodeTreeV2, la complexité dépend de la taille de l'arbre.
La complexité totale du code est principalement déterminée par la boucle principale et les appels de fonctions récursives pour créer et parcourir l'arbre. Si d est la profondeur maximale de l'arbre et m est le nombre de mouvements disponibles, la complexité peut être approximée comme suit:  
Boucle principale: O(n) où n est le nombre de mouvements nécessaires pour atteindre la base.
Création de l'arbre: O(d * m)
Recherche du chemin: O(d * m)

Conclusion
La complexité totale du code est approximativement O(n * d * m), où n est le nombre de mouvements nécessaires pour atteindre la base, d est la profondeur maximale de l'arbre, et m est le nombre de mouvements disponibles.

9.107000 secondes total en comptant les saisies utilisateurs et les "_sleep" contenus dans le code (minimum 7 secondes) - une seule phase


### Manuel
  
La boucle "while(rep < new_nbMoveSelect && robot_signal == 1 && (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y))" dépend de new_nbMoveSelect, robot_signal, et la position du robot par rapport à la base. Supposons que cette boucle s'exécute N fois.
À l'intérieur de la boucle principale: 
- afficherMouvements(): O(M) où M est la taille de move_list
- isEltInList(): O(M) dans le pire des cas (parcours de la liste)
- removeElt(): O(M) dans le pire des cas (parcours de la liste)
- printPath(): O(D) où D est la profondeur du noeud

En résumé, la complexité de la boucle principale est dominée par les opérations sur move_list, ce qui donne une complexité de O(N * M) où N est le nombre d'itérations de la boucle principale et M est la taille de move_list.

Temps d'exécution : 13.845000 secondes - 2 phases avant fin d'execution
Temps d'exécution : 10.069000 secondes - 1 seule phase avec perte du signal à la fin

En comptant les saisies utilisateurs et les "_sleep" contenus dans le code (minimum 7 secondes).







  
  




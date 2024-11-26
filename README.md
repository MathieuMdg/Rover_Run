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
        Son prochain mouvement est réduit :
            Avancer de 10 m et reculer ne produisent aucun déplacement.
            Avancer de 20 m n’avance que de 10 m.
            Avancer de 30 m n’avance que de 20 m.
        Les rotations sont limitées :
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
- Complexité de addNodeRecV2 : La fonction addNodeRecV2 est une fonction récursive qui parcourt tous les noeuds de l'arbre jusqu'à une profondeur maximale max_depth. Si chaque noeud a en moyenne k fils, la complexité de cette fonction est (O(k^{max_depth})).

En combinant toutes ces opérations, la complexité totale de la fonction createTreeV2 est dominée par la complexité de addNodeRecV2, ce qui donne une complexité de (O(k^{\text{max_depth}})).

Temps d'exécution de createTreeV2: <0.000000 secondes (Test éfféctué avec les fonctions de la librairie <time.h>).




  
  




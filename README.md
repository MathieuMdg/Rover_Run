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


## Présentation des cases
- PLAIN : Les cases PLAIN n’ont aucune influence sur les mouvements de MARC.

- ERG : Si MARC commence son mouvement depuis une case ERG :
        Son prochain mouvement est réduit :
            Avancer de 10 m et reculer ne produisent aucun déplacement.
            Avancer de 20 m n’avance que de 10 m.
            Avancer de 30 m n’avance que de 20 m.
        Les rotations sont limitées :
            Un demi-tour permet de tourner à gauche ou à droite d’un quart de tour seulement.
  
- REG : Si MARC termine un mouvement sur une case REG :
        Le rover est secoué, ce qui dégrade ses performances.
        MARC ne pourra effectuer que 4 mouvements au total lors de cette phase.
  
- CREVASSE : Zone extrêmement dangereuse pour MARC :
        Si le rover passe sur une case CREVASSE, il y tombe et met fin à sa mission.
  
- PENTE : Lorsque MARC commence une phase sur une case PENTE :
        Il glisse automatiquement sur une case adjacente.
        La case sur laquelle il arrive est imprévisible à cause des perturbations de signal.
  
- ZONE_MORTE : Si MARC commence une phase sur une case ZONE_MORTE :
        Les interférences empêchent les instructions d’arriver correctement.
        MARC s’oriente aléatoirement dans une autre direction.
  
- ZONE_SOLAIRE : Si MARC commence une phase sur une case ZONE_SOLAIRE :
        L’afflux d’énergie solaire améliore temporairement ses capacités.
        MARC obtient un mouvement supplémentaire pour cette phase.


  
  




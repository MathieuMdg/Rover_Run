#include <stdio.h>
#include "map.h"
#include "tree.h"
#include <time.h>
#include "affichage.h"


// Prototype des fonctions
void jouer(t_map, int, int);
void instructions();
void options(int* nbMaxMove, int* nbMoveSelect);
void afficherProgression(int pourcentage);
void quitter();



void demanderNombreMouvements(int* nbMaxMove, int* nbMoveSelect) {
    printf("\t*******************************************\n");
    printf("\t*         Configuration des phases        *\n");
    printf("\t*******************************************\n");

    printf("Nombre de mouvements tirés (max) : ");
    scanf(" %d", nbMaxMove);
    printf("Nombre de mouvements disponibles : ");
    scanf(" %d", nbMoveSelect);

    printf("\n\033[1;32mConfiguration enregistrée !\033[0m\n\n");
}



void jouer(t_map map, int nbMaxMove, int nbMoveSelect) {

    // Numéro de la phase
    int numero_phase = 1;

    int running = 0;

    // Exemple de tableau d'éléments avec leurs pourcentages initiaux
        tabMove items[] = {
            {F_10, 20.0},
            {F_20, 15.0},
            {F_30, 20.0},
            {B_10, 15.0},
            {T_RIGHT, 10.0},
            {T_LEFT, 10.0},
            {U_TURN, 10.0}
        };

        // Nombre de mouvements au total
        int nbMove = 7;


    // Fonction d'affichage au démarrage du jeu
    afficherDemarrage();


    // Affiche la carte avec les coûts de cases
    afficherCarteAvecCouts(map);






        printf("\n\n\n");

        // Définition des données initiales
        int x_init = randomNumber(0, map.x_max-1);
        int y_init = randomNumber(0, map.y_max-1);
        t_orientation  orientation_init = randomNumber(0, 3);

        // Définition des coordonnées de base du robot
        t_localisation robot_loc = loc_init(x_init, y_init, orientation_init);



        // Position de la base
        t_position base_station_loc = getBaseStationPosition(map);



        printf("\n\n\n");

        t_localisation root_loc_auto = loc_init(x_init, y_init, orientation_init);

        t_localisation root_loc = loc_init(x_init, y_init, orientation_init);


    while (running == 0) {

        int robot_signal = 1;

        while ((robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) && robot_signal == 1) {

            afficherDebutPhase(numero_phase);



            afficherInfosRobot(robot_loc, base_station_loc);


            h_std_list *move_list = createListEmpty();

            // Sélectionner n éléments
            for (int i = 0; i < nbMaxMove; i++) {
                t_move selected = selectRandomMove(items, nbMove);
                addTailList(move_list, selected);
            }

            afficherMouvements(*move_list);

            char guidage;

            printf("\n\n\n\nActiver le systeme de guidage automatique ? [Y/n] : ");
            scanf(" %c", &guidage);
            printf("\n");

            if (guidage == 'Y') {

                // Création de l'arbre de phase (Méthode 1)
                p_tree ptr_phase_tree_auto = createTree(move_list, map, robot_loc, nbMoveSelect);

                //p_tree ptr_phase_tree_auto = createTreeV2(move_list, map, robot_loc, nbMoveSelect);

                // Détermination du noeud avec le chemin le moins coûteux
                p_node node = searchBetterPathNode(*ptr_phase_tree_auto);


                if (node->case_cost > 12999) {
                    printf("Aucun chemin ne mene a la base (perte de signal du robot ou destruction de celui-ci\n");
                    robot_signal = 0;
                } else {
                    printf("Le chemin le moins couteux est : ");

                    // Affichage du chemin
                    printPath(*node);

                    printf("\n\n");
                    printNodeSonV2(*node);

                    // Affichage de la suite de mouvement correspondante
                    printf("\n\nSoit la suite de mouvement : [");
                    for (int i = 0; i < node->depth; i++) {
                        printf("%s - ", getMoveAsString(node->path[i]));
                    }
                    printf("%s]\n\n\n", getMoveAsString(node->path[node->depth]));

                    // Affectation des nouvelles coordonnées pour le robot (coordonnées de la case de fin de phase)
                    robot_loc = loc_init(node->localisation.pos.x, node->localisation.pos.y, node->localisation.ori);
                }

                numero_phase++;

                if (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {
                    printf("----------------------------------------------------------------\n\n\n");
                }

            } else {
                printf("Activation negative... ");

                // Création de l'arbre de phase manuel
                t_tree phase_tree_manuel = createEmptyTree();
                addRoot(&phase_tree_manuel, ROOT, 1, move_list, robot_loc, map);

                p_node node = phase_tree_manuel.root;

                int rep = 0;
                while (rep < nbMoveSelect && robot_signal == 1) {
                    printf("Choisir un mouvement [numero du mouvement dans la liste] :");

                    int movement;
                    scanf(" %d", &movement);
                    printf("\n");

                    printf("aaaaaaaaaaaaaaaaa");
                    while (!(isEltInList(*move_list, movement))) {
                        printf("Mouvement pas dans la liste... Choisir un autre mouvement :");
                        scanf(" %d", &movement);
                        printf("\n");
                    }

                    printf("miam");
                    //while (movement < 0 || movement > countEltHList(*move_list)) {
                    //printf("Numero incompatible... Choisir un mouvement [numero du mouvement dans la liste] :");
                    //scanf(" %d", &movement);
                    //}

                    displayHList(*move_list);
                    printf("sluro");
                    addNodeV2(&phase_tree_manuel, node, movement, map, nbMoveSelect);
                    printf("aaaaaaaaaaaaaaaaa");



                    move_list = removeElt(*move_list, movement);
                    displayHList(*move_list);

                    node = node->sons[node->nbSons - 1];

                    if (node->case_cost > 10000) {
                        printf("Aucun chemin ne mene a la base (perte de signal du robot ou destruction de celui-ci)\n");

                        robot_signal = 0;

                    } else {
                        printf("Le chemin le moins couteux est : ");

                        // Affichage du chemin
                        printPath(*node);

                        printf("\n\n");
                        printNodeSonV2(*node);

                        // Affichage de la suite de mouvement correspondante
                        printf("\n\nSoit la suite de mouvement : [");
                        for (int i = 0; i < node->depth; i++) {
                            printf("%s - ", getMoveAsString(node->path[i]));
                        }
                        printf("%s]\n\n\n", getMoveAsString(node->path[node->depth]));

                        // Affectation des nouvelles coordonnées pour le robot (coordonnées de la case de fin de phase)
                        robot_loc = loc_init(node->localisation.pos.x, node->localisation.pos.y, node->localisation.ori);
                    }

                    rep++;



                }
            }

                if (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {
                    printf("----------------------------------------------------------------\n\n\n");
                }

            }


        displayMap(map);

        running = -1;

    }
}

void instructions() {
    printf("Instructions du jeu :\n");
    printf("- Guidez le rover MARC vers la station de base.\n");
    printf("- Évitez les terrains dangereux comme les crevasses.\n");
    printf("- Optimisez vos mouvements pour minimiser les coûts.\n\n");
    getchar(); // Pause
}

void options(int* nbMaxMove, int* nbMoveSelect) {
    printf("Options à personnaliser :\n");
    printf("- Modifier la difficulté.\n");
    printf("- Changer les paramètres visuels.\n");
    printf("- Réinitialiser le jeu.\n\n");

    demanderNombreMouvements(nbMaxMove, nbMoveSelect);
    getchar(); // Pause
}

void quitter() {
    printf("Merci d'avoir joué à Rover Run !\n");
    exit(0);
}

int main() {

    // Initialisation de la fonction aléatoire
    srand(time(NULL));

    // Déclaration d'une variable t_map
    t_map map;

    // Fonction pour créer une carte aléatoirement (peut faire crash le programme de temps en temps)
    createRandomMap("..\\maps\\example2.map", randomNumber(7, 16), randomNumber(6, 15));

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    printf("ouhzer");
    map = createMapFromFile("../maps/example1.map");
    printf("zfgqsegspjges");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    // Affiche la carte
    displayMap(map);

    printf("\n\n\n");

    // Nombre de mouvements tiré
    int nbMaxMove = 9;

    // Nombre de mouvement sélectionné
    int nbMoveSelect = 5;

    printf("\n\n\n");

    // Affiche le menu du jeu
    afficherMenu(map, &nbMaxMove, &nbMoveSelect);

    return 0;
}

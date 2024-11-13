#include <stdio.h>
#include "map.h"
#include "tree.h"
#include <time.h>

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("x_max : %d\n", map.x_max);
    printf("y_max : %d\n", map.y_max);




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
    displayMap(map);



    int running = 1;

    if (running == 1) {

        printf("\n\n\n");



        srand(time(NULL));


        // Exemple de tableau d'éléments avec leurs pourcentages initiaux
        tabMove items[] = {
            {F_10, 30.0},
            {F_20, 25.0},
            {F_30, 20.0},
            {B_10, 15.0},
            {T_RIGHT, 10.0},
            {T_LEFT, 10.0}
        };
        // Nombre de mouvements au total
        int nbMove = 6;

        // Nombre de mouvements tiré
        int nbMaxMove = 5;

        // Nombre de mouvement sélectionné
        int nbMoveSelect = 1;

        printf("Nombre de tirage pour les mouvement :");
        scanf(" %d", &nbMaxMove);

        printf("Nombre de mouvement disponible dans une phase :");
        scanf(" %d", &nbMoveSelect);

        h_std_list* move_list = createListEmpty();

        // Sélectionner n éléments
        for (int i = 0; i < nbMaxMove; i++) {
            t_move selected = selectRandomMove(items, nbMove);
            addTailList(move_list, selected);
            printf("Element selectionne : %d\n", selected);
        }

        printf("\n\n\n");

        // Définition des données initiales
        int x_init = randomNumber(0, map.x_max-1);
        int y_init = randomNumber(0, map.y_max-1);
        t_orientation  orientation_init = randomNumber(0, 3);

        // Définition des coordonnées de base du robot
        t_localisation robot_loc = loc_init(x_init, y_init, orientation_init);
        printf("robot x : %d\n", robot_loc.pos.x);
        printf("robot y : %d\n", robot_loc.pos.y);
        printf("robot orientation : %s\n", getOrientationAsString(robot_loc.ori));



        // Position de la base
        t_position base_station_loc = getBaseStationPosition(map);

        displayMap(map);

        // printf the costs, aligned left 5 digits
        for (int i = 0; i < map.y_max; i++)
        {
            for (int j = 0; j < map.x_max; j++)
            {
                printf("%-5d ", map.costs[i][j]);
            }
            printf("\n");
        }

        printf("\n\n\n");

        t_localisation root_loc = loc_init(x_init, y_init, orientation_init);

        p_tree ptr_phase_tree = createFullTreePhase(move_list, map, robot_loc, nbMoveSelect);

        printf("%d", ptr_phase_tree->depth);


        char guidage;

        printf("\n\n\n\nActiver le système de guidage automatique ? [Y/n] : ");
        scanf(" %c", &guidage);
        printf("\n");
        if (guidage == 'Y') {
            printPath(*searchBetterPathNode(*ptr_phase_tree));
        }
        else {
            printf("Tant pis...");
        }



    }

    while (running == 0) {
        displayMap(map);

    }
    return 0;
}

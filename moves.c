//
// Created by flasque on 19/10/2024.
//

#include "moves.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */





/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst = 0;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default:
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res;
    res.x = loc.pos.x;
    res.y = loc.pos.y;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
        return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc;
    new_loc = translate(loc, move);
    new_loc.ori = rotate(loc.ori, move);


    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m)
{
    *p_loc = move(*p_loc, m);
    return;
}


// Fonction pour sélectionner un élément en fonction des pourcentages
t_move selectRandomMove(tabMove move[], int size) {

    double sum = 0.0;

    // Calcul le pourcentage total des éléments
    for (int i = 0; i < size; i++) {
        sum += move[i].percentage;
    }

    // Générer un nombre aléatoire entre 0 et la somme des pourcentages
    double random = (double)rand() / RAND_MAX * sum;

    // Sélection de l'élément
    double cumulative = 0.0;
    for (int i = 0; i < size; i++) {
        cumulative += move[i].percentage;
        if (random <= cumulative) {

            // Réduire le pourcentage de l'élément sélectionné (encore à déterminer)
            move[i].percentage *= 0.9;
            return move[i].element;
        }
    }

    return -1; // Retourne -1 si aucun élément n'est sélectionné (ne devrait pas arriver)
}

t_move *getRandomMoves(int N)
{
    int nbmoves[]={22,15,7,7,21,21,7};
    int total_moves=100;
    t_move *moves = (t_move *)malloc(N * sizeof(t_move));
    for (int i = 0; i < N; i++)
    {
        int r = rand() % total_moves;
        int type=0;
        while (r >= nbmoves[type])
        {
            r -= nbmoves[type];
            type++;
        }
        nbmoves[type]--;
        total_moves--;
        moves[i] = (t_move )type;
    }
    return moves;
}

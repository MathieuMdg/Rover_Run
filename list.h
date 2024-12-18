//
// Created by ABuhl on 24/10/2024.
//

#ifndef UNTITLED1_LIST_H
#define UNTITLED1_LIST_H

#include "cell.h"


typedef struct s_std_list
{
    p_cell head;
} h_std_list;

// Ajouter une cellule en fin de liste
void addTailList(h_std_list* list, t_move move);

// Fonction d'affichage de la liste
void displayHList(h_std_list list);

// Supprimer un éléments de la liste
void Deleteelt(h_std_list* list, t_move move);

// Créer une nouvelle liste sans un élément donné
h_std_list* removeElt(h_std_list list, t_move move);

// Création d'une liste vide
h_std_list* createListEmpty();

// Fonction qui compte le nombre d'élément dans une liste
int countEltHList(h_std_list list);

// Trouver un élément en fonction de sa place dans la liste
t_move findElt(h_std_list list, int nb);

int isEltInList(h_std_list list, t_move move);

#endif //UNTITLED1_LIST_H

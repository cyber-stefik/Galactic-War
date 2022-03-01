// Copyright 2021 Stefanita Ionita
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "galactic_war.h"

/* Parcurge lista pana la nodul n si il returneaza. */
node_t*
get_nth_node(doubly_linked_list_t* galaxy, int n)
{	int i = 0;
	if (n >= galaxy->size) {
		n = n % galaxy->size;
	}
	node_t* tmp = galaxy->head;
	while (i < n) {
		tmp = tmp->next;
		i++;
	}
	return tmp;
}

/* Creeaza o lista si initializeaza head, data_size si size. */
doubly_linked_list_t*
create(unsigned int data_size)
{
	doubly_linked_list_t* list = malloc(sizeof(doubly_linked_list_t));
	if (!list) {
        printf("Could not allocate.\n");
    }
	list->data_size = data_size;
	list->size = 0;
    list->head = NULL;
	return list;
}

/* Printeaza valorile listei primite, acestea sunt intregi si functia este
folosita in show pentru a afisa scuturile. */
void
print_int_list(doubly_linked_list_t* list)
{
    int i = 0;
    node_t *tmp = list->head;
    for (i = 0; i < list->size; i++) {
        printf("%d ", *(int *)tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

/* Adauga un nod in lista primita ca parametru in mod eficient pe pozitia n. */
void
add_nth_node(doubly_linked_list_t* list, int n, const void* data)
{
    node_t *node = malloc(sizeof(node_t));
    node_t *tmp;
    node->data = malloc(list->data_size);
    memcpy(node->data, data, list->data_size);

    if (list->size == 0) {  // initializare head cand list->size e 0
        list->head = node;
        list->head->next = list->head;
        list->head->prev = list->head;
        list->size++;
        return;
    } else if (n == 0 && list->size != 0) {  // adaugare nod pe pozitia 0 in
                                    // cazul in care mai exista elemente in list
        tmp = list->head;
        node->prev = tmp->prev;
        node->next = tmp;
        node->next->prev = node;
        node->prev->next = node;
        list->head = node;
        list->size++;
        return;
    } else if (n == list->size && list->size != 0) {  // adaugare nod pe pozitia
                                            // n in in cazul in care mai exista
                                            // elemente in list
        tmp = list->head;
        node->prev = tmp->prev;
        node->next = tmp;
        node->prev->next = node;
        node->next->prev = node;
        list->size++;
        return;
    } else {  // adaugare nod pe pozitia n, cand n nu este pozitia head sau tail
        tmp = get_nth_node(list, n);
        node->prev = tmp->prev;
        node->next = tmp;
        node->next->prev = node;
        node->prev->next = node;
        list->size++;
    }
}

/* Returneaza pointer la nodul care trebuie sters. */
node_t*
remove_nth_node(doubly_linked_list_t* list, int n)
{
    node_t *rmv, *tmp;
    if (list->size == 0) {  // cazul in care nu exista elemente in list
        return NULL;
    }
    tmp = list->head;
    if (list->size == 1) {  // cazul in care exista un singur element in list
        list->head = NULL;
        list->size--;
        return tmp;
    }
    if (n == 0) {  // stergerea capului de lista
        rmv = list->head;
        rmv->prev->next = rmv->next;
        rmv->next->prev = rmv->prev;
        list->head = rmv->next;
        list->size--;
        return rmv;
    }
    if (n == list->size - 1) {  // stergerea ultimului element din lista,
                                // complexitate O(1)
        rmv = tmp->prev;
        rmv->prev->next = rmv->next;
        rmv->next->prev = rmv->prev;
        list->size--;
        return rmv;
    } else {  // stergerea nodului de pe pozitia n, cand n nu este pozitia
            // lui head sau tail
        rmv = get_nth_node(list, n);
        rmv->prev->next = rmv->next;
        rmv->next->prev = rmv->prev;
        list->size--;
        return rmv;
    }
}

/* Adauga o planeta in galaxie cu toate campurile necesare. */
void
add_command(doubly_linked_list_t* galaxy, char name[69], int planet_index,
            unsigned int no_shields)
{
    planet_t planet;
    if (planet_index > galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    planet.shield = create(sizeof(int));  // crearea listei de scuturi
    planet.name = malloc(strlen(name) + 1);  // alocare memorie pentru nume
    memcpy(planet.name, name, strlen(name) + 1);  // adaugarea numelui planetei
    planet.kills = 0;  // initializare kills pentru planeta
    unsigned int i;
	unsigned int val = 1;
	for (i = 0; i < no_shields; i++) {
		add_nth_node(planet.shield, 0, &val);  // adaugarea de scuturi pe
                                    // pozitia 0, complexitate O(1)
	}
    add_nth_node(galaxy, planet_index, &planet);  // adaugarea planetei in
                                                // galaxie
    printf("The planet %s has joined the galaxy.\n", planet.name);
}

/* Sterge o planeta din galaxie si ii elibereaza memoria alocata. */
void
blh_command(doubly_linked_list_t* galaxy, int p_index)
{
    if (p_index >= galaxy->size) {
		printf("Planet out of bounds!\n");
        return;
	}
    node_t *tmp = remove_nth_node(galaxy, p_index);  // planeta pe care trebuie
                                                    // sa o sterg
    printf("The planet %s has been eaten by the vortex.\n",
            ((planet_t *)tmp->data)->name);
    doubly_linked_list_t* rmv_shield = ((planet_t *)tmp->data)->shield;
    free_planet(rmv_shield, tmp);  // eliberarea memoriei alocata planetei
}

/* Creste valoarea scutului de pe pozitia s_index al planetei de pe pozitia
p_index cu valoarea value. */
void
upg_command(doubly_linked_list_t* galaxy, int p_index, int s_index, int value)
{
    node_t *planet = get_nth_node(galaxy, p_index);  // planeta pentru care
                                                    // fac upgrade scutului
    if (p_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    if (s_index >= ((planet_t *)planet->data)->shield->size) {
        printf("Shield out of bounds!\n");
        return;
    }
    node_t *tmp = get_nth_node(((planet_t *)planet->data)->shield, s_index);
    *((int*)tmp->data) += value;  // cresterea valorii scutului de pe pozitia
                            // s_index cu valoarea value
}

/* Adauga un scut la finalul listei de scuturi, acesta avand valoarea value. */
void
exp_command(doubly_linked_list_t* galaxy, int p_index, int value)
{
    node_t *planet = get_nth_node(galaxy, p_index);  // planeta pentru care
                                                    // adaug scutul
    if (p_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    add_nth_node(((planet_t*)planet->data)->shield,
                ((planet_t*)planet->data)->shield->size, &value);
}

/* Sterge scutul de pe pozitia s_index al planetei de pe pozitia p_index. */
void
rmv_command(doubly_linked_list_t* galaxy, int p_index, int s_index)
{
    node_t *planet = get_nth_node(galaxy, p_index);  // planeta de la care vreau
                                        // sa sterg scutul
    node_t *tmp;
    if (p_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    if (s_index > ((planet_t *)planet->data)->shield->size - 1) {
        printf("Shield out of bounds!\n");
        return;
    }
    if (((planet_t *)planet->data)->shield->size > 4) {
        // stergerea scutului de pe pozitia s_index si eliberarea memoriei
        tmp = remove_nth_node(((planet_t *)planet->data)->shield, s_index);
        free(tmp->data);
        free(tmp);
    } else {
        printf("A planet cannot have less than 4 shields!\n");
    }
}

/* Realizeaza coliziunea intre 2 planete si elibereaza memoria acestora
in functie de caz. */
void
col_command(doubly_linked_list_t* galaxy, int p_index1, int p_index2)
{
    if (p_index1 >= galaxy->size || p_index2 >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    // Planeta de pe pozitia p_index1
    node_t *planet1 = get_nth_node(galaxy, p_index1);
    // Planeta de pe pozitia p_index2
    node_t *planet2 = get_nth_node(galaxy, p_index2);
    // Punctul de coliziune al primei planete
    int s_index1 = (((planet_t*)planet1->data)->shield->size) / 4;
    // Punctul de coliziune al celei de-a doua planete
    int s_index2 = ((((planet_t*)planet2->data)->shield->size) / 4) * 3;
    node_t *shield1 = get_nth_node(((planet_t*)planet1->data)->shield,
                                    s_index1);
    node_t *shield2 = get_nth_node(((planet_t*)planet2->data)->shield,
                                    s_index2);
    int *val_1 = (int*)shield1->data;  // valoarea primului scut de coliziune
    int *val_2 = (int*)shield2->data;  // valoarea celui de-al doilea scut de
                                        // coliziune

    if (*val_1 != 0 && *val_2 != 0) {  // cazul in care planetele se pot ciocni
        *val_1 -= 1;
        *val_2 -= 1;
        return;
    }
    if (*val_1 == 0 && *val_2 > 0) {  // cazul in care planeta1 face implozie
                                    // BUBUIALA STANGA
        planet1 = remove_nth_node(galaxy, p_index1);
        printf("The planet %s has imploded.\n",
                ((planet_t*)planet1->data)->name);
        doubly_linked_list_t* rmv_shield = ((planet_t *)planet1->data)->shield;
        free_planet(rmv_shield, planet1);  // eliberez memoria pentru planet1
        ((planet_t*)planet2->data)->kills++;
        *val_2 -= 1;
        return;
    }
    if (*val_1 > 0 && *val_2 == 0) {  // cazul in care planeta2 face implozie
                                    // BUBUIALA DREAPTA
        planet2 = remove_nth_node(galaxy, p_index2);
        printf("The planet %s has imploded.\n",
                ((planet_t*)planet2->data)->name);
        doubly_linked_list_t* rmv_shield = ((planet_t *)planet2->data)->shield;
        free_planet(rmv_shield, planet2);  // eliberez memoria pentru planet2
        ((planet_t*)planet1->data)->kills++;
        *val_1 -= 1;
        return;
    }
    if (*val_1 == 0 && *val_2 == 0) {  // cazul in care ambele fac implozie
                                    // BUBUIALA MAREEEEEEEEEEEE
        planet2 = remove_nth_node(galaxy, p_index2);
        planet1 = remove_nth_node(galaxy, p_index1);
        printf("The planet %s has imploded.\n",
                ((planet_t*)planet1->data)->name);
        printf("The planet %s has imploded.\n",
                ((planet_t*)planet2->data)->name);
        doubly_linked_list_t* rmv_shield1 = ((planet_t *)planet1->data)->shield;
        doubly_linked_list_t* rmv_shield2 = ((planet_t *)planet2->data)->shield;
        // eliberez memoria pentru ambele planete
        free_planet(rmv_shield2, planet2);
        free_planet(rmv_shield1, planet1);
        return;
    }
}

/* Muta capul listei in functie de sens, mutarea realizandu-se eficient. */
void
rot_command(doubly_linked_list_t* galaxy, int p_index, char* orientation,
            int units)
{
    node_t *planet = get_nth_node(galaxy, p_index);
    node_t *new_head;
    if (p_index >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    int size = ((planet_t *)planet->data)->shield->size;
    switch (*orientation) {
        case 'c':  // sensul acelor de ceasornic
            new_head = get_nth_node(((planet_t *)planet->data)->shield,
                                    size - units % size);
            ((planet_t *)planet->data)->shield->head = new_head;
            break;
        case 't':  // sensul trigonometric
            new_head = get_nth_node(((planet_t *)planet->data)->shield,
                                    units % size);
            ((planet_t *)planet->data)->shield->head = new_head;
            break;
        default:
            printf("Not a valid direction!\n");
    }
}

/* Afiseaza informatii despre planeta aflata la pozitia p_index. */
void
shw_command(doubly_linked_list_t* galaxy, int p_index)
{
    if (p_index >= galaxy->size || galaxy->size == 0) {
        printf("Planet out of bounds!\n");
        return;
    }
    node_t *planet = get_nth_node(galaxy, p_index);
    printf("NAME: %s\n", ((planet_t*)planet->data)->name);
    if (galaxy->size == 1) {
        printf("CLOSEST: none\n");
    } else if (galaxy->size == 2) {
        printf("CLOSEST: %s\n", ((planet_t*)planet->next->data)->name);
    } else {
        printf("CLOSEST: %s and %s\n", ((planet_t *)planet->prev->data)->name,
                                    ((planet_t *)planet->next->data)->name);
    }
    printf("SHIELDS: ");
    print_int_list(((planet_t *)planet->data)->shield);
    printf("KILLED: %d\n", ((planet_t *)planet->data)->kills);
}

/* Elibereaza nodurile unei liste. */
void
dll_free(doubly_linked_list_t** pp_list)
{
    node_t *node = (*pp_list)->head;
    node_t *tmp;
    for (int i = 0; i < (*pp_list)->size; i++) {
        tmp = node->next;
        free(node->data);
        free(node);
        node = tmp;
    }
    free(*pp_list);
    *pp_list = NULL;
}

/* Elibereaza memoria alocata planetelor si scuturilor din galaxie. */
void
free_command(doubly_linked_list_t* galaxy)
{
    node_t *tmp = galaxy->head;
    for (int i = 0; i < galaxy->size; i++) {
        doubly_linked_list_t* rmv_shield = ((planet_t *)tmp->data)->shield;
        dll_free(&rmv_shield);  // eliberarea memoriei alocate fiecarei liste
                                // de scuturi
        free(((planet_t *)tmp->data)->name);  // eliberarea memoriei alocate
                                            // numelui
        tmp = tmp->next;
    }
}

/* Elibereaza memoria alocata planetei si scuturilor, fiind folosita
in col_command. */
void
free_planet(doubly_linked_list_t* rmv_shields, node_t* planet)
{
    dll_free(&rmv_shields);
    free(((planet_t *)planet->data)->name);
    free(planet->data);
    free(planet);
}

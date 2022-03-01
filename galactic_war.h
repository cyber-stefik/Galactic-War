// Copyright 2021 Stefanita Ionita
#ifndef _HOME_STEFIK_DESKTOP_GALACTIC_WAR_GALACTIC_WAR_H_
#define _HOME_STEFIK_DESKTOP_GALACTIC_WAR_GALACTIC_WAR_H_
#include <errno.h>

typedef struct node_t node_t;
struct node_t
{
    void* data;
    node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    node_t* head;
    unsigned int data_size;
    int size;
};

typedef struct planet_t planet_t;
struct planet_t
{
	char *name;
	int kills;
	doubly_linked_list_t *shield;
};

doubly_linked_list_t*
create(unsigned int data_size);

void
add_nth_node(doubly_linked_list_t* list, int n, const void* data);

node_t*
dll_remove_nth_node(doubly_linked_list_t* list, int n);

void
shield_init(doubly_linked_list_t* shield, unsigned int n);

void
add_command(doubly_linked_list_t* galaxy, char name[69], int planet_index,
            unsigned int no_shields);

void
blh_command(doubly_linked_list_t* galaxy, int p_index);

void
upg_command(doubly_linked_list_t* galaxy, int p_index, int s_index, int value);

void
exp_command(doubly_linked_list_t* galaxy, int p_index, int value);

void
rmv_command(doubly_linked_list_t* galaxy, int p_index, int s_index);

void
col_command(doubly_linked_list_t* galaxy, int p_index1, int p_index2);

void
rot_command(doubly_linked_list_t* galaxy, int p_index, char *orientation,
            int units);

void
print_int_list(doubly_linked_list_t* list);

doubly_linked_list_t*
rot_c(doubly_linked_list_t* list, int units);

void
shw_command(doubly_linked_list_t* galaxy, int p_index);

void
dll_free(doubly_linked_list_t** pp_list);

void
free_command(doubly_linked_list_t* galaxy);

void
free_planet(doubly_linked_list_t* rmv_shields, node_t* planet);

#endif  // _HOME_STEFIK_DESKTOP_GALACTIC_WAR_GALACTIC_WAR_H_

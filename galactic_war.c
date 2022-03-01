// Copyright 2021 Stefanita Ionita
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "galactic_war.h"

int main() {
	int M, i;
	doubly_linked_list_t *galaxy = create(sizeof(planet_t));
	char command[20], planet_name[69], orientation[2];
	int planet_index, planet_index2, shield_index,
		shield_value, upgrade_value, units;
	unsigned int no_shields;
	scanf("%d", &M);
	for (i = 0; i < M; i++) {  // M comenzi
		scanf("%s", command);
		if (strcmp(command, "ADD") == 0) {
			scanf("%s", planet_name);
			scanf("%d %d", &planet_index, &no_shields);
			add_command(galaxy, planet_name, planet_index, no_shields);
		}
		if (strcmp(command, "BLH") == 0) {
			scanf("%d", &planet_index);
			blh_command(galaxy, planet_index);
		}
		if (strcmp(command, "UPG") == 0) {
			scanf("%d %d %d", &planet_index, &shield_index, &upgrade_value);
			upg_command(galaxy, planet_index, shield_index, upgrade_value);
		}
		if (strcmp(command, "EXP") == 0) {
			scanf("%d %d", &planet_index, &shield_value);
			exp_command(galaxy, planet_index, shield_value);
		}
		if (strcmp(command, "RMV") == 0) {
			scanf("%d %d", &planet_index, &shield_index);
			rmv_command(galaxy, planet_index, shield_index);
		}
		if (strcmp(command, "COL") == 0) {
			scanf("%d %d", &planet_index, &planet_index2);
			col_command(galaxy, planet_index, planet_index2);
		}
		if (strcmp(command, "ROT") == 0) {
			scanf("%d", &planet_index);
			scanf("%s", orientation);
			scanf("%d", &units);
			rot_command(galaxy, planet_index, orientation, units);
		}
		if (strcmp(command, "SHW") == 0) {
			scanf("%d", &planet_index);
			shw_command(galaxy, planet_index);
		}
	}
	free_command(galaxy);
	dll_free(&galaxy);
	return 0;
}

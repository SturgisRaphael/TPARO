#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

#define STRINGLENGTH 30

int main(void)
{
	glp_prob *lp;
	const int nbr_rows = 5;
	const int nbr_columns = 5;
	const int nbr_coefs = 25;
	
	/* Tableau des coefficients de la matrice */
	double matrix_coefs[] = {0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, -0.03, 0.028, -0.021, 0.042, -0.024, 1, 1, 1, 1, 1};
	/* Position de chaque coefficient */
	int row_of_coef[] = {0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};
	int column_of_coef[] = {0, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
	
	/* matrix_coef[i] est le coefficient de la matrice en ligne
	   row_of_coefs[i] et en colonne column_of_coefs[i].*/
	
	const double row_bounds[] = {0, 50000, 50000, 40000, 0, 100000};
	const int row_bounds_bis[] = {0, 1, 2, 1, 1, 0};
	const double obj_coefs[] = {0, 0.1, 0.04, 0.07, 0.06, 0.08};
	
	/* création d'un programme linéaire */
	lp = glp_create_prob();
	glp_set_prob_name(lp, "example"); /* Nommer le problème est obligatoire */
	glp_set_obj_dir(lp, GLP_MAX); /* Détermine l'objectif MIN ou MAX */

	/* Initialisation du problème */

	/* ajoute des lignes (contraintes) */
	glp_add_rows(lp, nbr_rows);
	for(int row_index = 1; row_index <= nbr_rows; row_index++) {
		char constraint_name[STRINGLENGTH];
		sprintf(constraint_name, "contrainte %d", row_index);
		/* nomme la contrainte */
		glp_set_row_name(lp, row_index, constraint_name);
		if(row_bounds_bis[row_index] == 0)
		{
			/* definit une borne =*/
			glp_set_row_bnds(lp, row_index, GLP_FX, row_bounds[row_index], row_bounds[row_index]);
			
		}
		else if(row_bounds_bis[row_index] == 1)
		{
			/* définit une borne sup de 2 */
			glp_set_row_bnds(lp, row_index, GLP_LO, row_bounds[row_index], 0.0);
		}
		else if(row_bounds_bis[row_index] == 2)
		{
			/* définit une borne sup de 2 */
			glp_set_row_bnds(lp, row_index, GLP_UP, 0.0, row_bounds[row_index]);
		}
	}

	/* Ajoute des variables */
	glp_add_cols(lp, nbr_columns);
	for (int column_index = 1 ; column_index <= nbr_columns; column_index++){
		char variable_name[STRINGLENGTH];
		sprintf(variable_name, "x_%d", column_index);
		glp_set_col_bnds(lp, column_index, GLP_LO, 0.0, 0.0);
		/* définit le coefficient de la variable dans l'objectif */
		glp_set_obj_coef(lp, column_index, obj_coefs[column_index]);
	}

	/* Chargement de la matrice */
	glp_load_matrix (lp,
	nbr_coefs,
	row_of_coef,
	column_of_coef,
	matrix_coefs);

	/* Lancer la résolution du problème */
	glp_simplex(lp, NULL);

	/* récupération du résultat */
	double optimum = glp_get_obj_val(lp);
	double variable_value[1+nbr_columns];
	for (int column_index = 1; column_index <= nbr_columns; column_index ++) {
		variable_value[column_index] = glp_get_col_prim(lp, column_index);
	}

	/* affichage */
	printf("Best solution objective value z = %lf", optimum);
	for(int column_index = 1 ; column_index <= nbr_columns; column_index ++){
		char variable_name[STRINGLENGTH];
		sprintf(variable_name, "x_%d", column_index);
		printf("%s = %lf\n", variable_name, variable_value[column_index]);
	}

	/* libération du problème */
	glp_delete_prob(lp);
	glp_free_env();
	return 0;
}

//
// Created by raphael on 2/2/18.
//

#include "orderSolver.h"
#include "order.h"

#define STRINGLENGHT 80

/*
 * Solve an order
 *
 * return: array[n][m]
 */

int **solveOrder(order o) {

	int ** patterns = malloc(o.numberSizes * sizeof(int*));
	int sizeOfPatterns = o.numberSizes;
	for(int i = 0; i < sizeOfPatterns; i++){
		patterns[i] = malloc(o.numberSizes * sizeof(int));
		for(int j = 0; j < o.numberSizes; j++){
			if(i = j)
				patterns[i][j] = 1;
			else
				patterns[i][j] = 0;
		}
	}

	glp_prob *lp;

	do{
		//Creating problem
		lp = glp_create_prob();
		glp_set_prob_name(lp, "order");
		glp_set_obj_dir(lp, GLP_MIN);

        //Creating Constraints
        glp_add_rows(lp, o.numberSizes);
		for(int i = 0; i < o.numberSizes; i++){
            char constraint_name[STRINGLENGHT];
            sprintf(constraint_name, "constraint %d", i);
            glp_set_row_name(lp, i, constraint_name); //naming constraints

            glp_set_row_bnds(lp, i, GLP_FX, o.array[i][0], o.array[i][0])
        }

        //Creating Variables
        glp_add_cols(lp, sizeOfPatterns);
        for(int i = 0; i < sizeOfPatterns; i++)
        {
            char variables_names[STRINGLENGHT];
            sprintf(variables_names, "x_%d", i);

            glp_set_row_bnds(lp, i, GLP_LO, 0.0, 0.0);

            glp_set_obj_coef(lp, i, 1);
        }

        

	}while(true) //todo:



	for(int i = 0; i < sizeOfPatterns; i++)
		free(patterns[i]);
	free(patterns);

	return NULL;
}

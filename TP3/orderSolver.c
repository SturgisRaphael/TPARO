//
// Created by raphael on 2/2/18.
//

#include "orderSolver.h"
#include "order.h"

#define STRINGLENGHT 80

bool add_new_pattern(glp_prob *pProb, double **pDouble, order o, int i);

/*
 * Solve an order
 *
 * return: array[n][m]
 */

/*
 * sebastien.ratel@lis-lab.fr
 * objet: [M1ARO] NOM1-NOM2
 * rendu archive compressée nommée NOM1-NOM2 avec README et makefile
 * Avant le 14/02
 */

double* patternsConvertor(double ** patterns, int p, int q){
    double * result = malloc(p*q* sizeof(double));

    for(int i = 0; i < p; i++){
        for (int j = 0; j < q; j++) {
            result[(i*p)+j] = patterns[i][j];
        }
    }

    return result;
}

int **solveOrder(order o) {

    double **patterns = malloc(o.numberSizes * sizeof(double *));
    int sizeOfPatterns = o.numberSizes;
    for (int i = 0; i < sizeOfPatterns; i++) {
        patterns[i] = malloc(o.numberSizes * sizeof(double));
        for (int j = 0; j < o.numberSizes; j++) {
            patterns[i][j] = i == j ? 1.0 : 0.0;
        }
    }

    glp_prob *lp;

    do {
        int *row_coef = malloc(sizeOfPatterns * o.numberSizes * sizeof(int));
        for(int i = 0; i < sizeOfPatterns; i++){
            for(int j = 0; j < o.numberSizes; j++)
                row_coef[i+j] = i;
        }

        int *col_coef = malloc(sizeOfPatterns * o.numberSizes * sizeof(int));
        for(int i = 0; i < sizeOfPatterns; i++){
            for(int j = 0; j < o.numberSizes; j++)
                col_coef[i+j] = j;
        }

        //Creating problem
        lp = glp_create_prob();
        glp_set_prob_name(lp, "order");
        glp_set_obj_dir(lp, GLP_MIN);

        //Creating Constraints
        glp_add_rows(lp, o.numberSizes);
        for (int i = 0; i < o.numberSizes; i++) {
            char constraint_name[STRINGLENGHT];
            sprintf(constraint_name, "constraint %d", i);
            glp_set_row_name(lp, i, constraint_name); //naming constraints

            glp_set_row_bnds(lp, i, GLP_FX, o.array[i][0], o.array[i][0]);
        }

        //Creating Variables
        glp_add_cols(lp, sizeOfPatterns);
        for (int i = 0; i < sizeOfPatterns; i++) {
            char variables_names[STRINGLENGHT];
            sprintf(variables_names, "x_%d", i);

            glp_set_row_bnds(lp, i, GLP_LO, 0.0, 0.0);

            glp_set_obj_coef(lp, i, 1);
        }

        double* matrix = patternsConvertor(patterns, sizeOfPatterns, o.numberSizes);

        //loading matrix
        glp_load_matrix(lp, o.numberSizes * sizeOfPatterns, row_coef, col_coef, matrix);

        glp_simplex(lp, NULL);

        free(matrix);
        free(row_coef);
        free(col_coef);

    } while (add_new_pattern(lp, patterns, o, sizeOfPatterns)); //todo:



    for (int i = 0; i < sizeOfPatterns; i++)
        free(patterns[i]);
    free(patterns);

    return NULL;
}

bool add_new_pattern(glp_prob *pProb, double **pDouble, order o, int sizeOfPattern) {
    glp_prob *s;

    //Creating problem
    s = glp_create_prob();
    glp_set_prob_name(s, "Sac a dos");
    glp_set_obj_dir(s, GLP_MAX);

    //Creating Constraints
    glp_add_rows(s, 1);

    glp_set_row_name(s, 0, "contraint"); //naming constraints

    glp_set_row_bnds(s, 0, GLP_UP, 0.0, o.initWidth);

    //Creating Variables
    glp_add_cols(s, o.numberSizes);
    for (int i = 0; i < o.numberSizes; i++) {
        char variables_names[STRINGLENGHT];
        sprintf(variables_names, "a_%d", i);

        glp_set_row_bnds(s, i, GLP_LO, 0.0, 0.0);

        glp_set_obj_coef(s, i, glp_get_row_dual(pProb, i));
    }

    int *row_coef = malloc((o.numberSizes + 1) * sizeof(int));
    row_coef[0] = 0;
    for(int j = 1; j <= o.numberSizes; j++)
        row_coef[j] = 1;

    int *col_coef = malloc((o.numberSizes + 1) * sizeof(int));
    for(int j = 0; j <= o.numberSizes; j++)
        col_coef[j] = j;

    int *matrix = malloc((o.numberSizes + 1) * sizeof(int));
    matrix[0] = 0;
    for(int i = 1; i < o.numberSizes + 1; i++)
        matrix[i] = o.array[i][1];

    glp_load_matrix(s, o.numberSizes, row_coef, col_coef, matrix);

    glp_simplex(s, NULL);

    if(glp_get_obj_val(s) <= 1)
        return false;

    pDouble = realloc(pDouble, (sizeOfPattern + 1) * sizeof(double*));
    pDouble[sizeOfPattern + 1] = malloc(o.numberSizes * sizeof(double));
    for(int i = 0; i < o.numberSizes; i++)
    {
        pDouble[sizeOfPattern + 1][i] = glp_get_col_prim(s, i);
    }

    return true;
}

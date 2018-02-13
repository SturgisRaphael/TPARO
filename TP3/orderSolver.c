//
// Created by raphael on 2/2/18.
//

#include <zconf.h>
#include "orderSolver.h"
#include "order.h"

#define STRINGLENGHT 80


/*
 * Solve an order
 *
 * return: array[n][m]
 */

#define TAUX_ERREUR 0.00001

bool add_new_pattern(double *dualSolution, order o, int **patterns, int sizeOfPattern);

void printIntSolution(glp_prob *p, int nbColumns) ;

void printTab(int **patterns, int p, int q){
    for(int i = 0; i < q; i++)
    {
        for(int j = 0; j < p; j++)
        {
            printf("%d|", patterns[j][i]);
        }
        printf("\n");
    }
}

void printList(int* list, int p)
{
    for(int i = 0; i < p; i++){
        printf("%d|", list[i]);
    }
    printf("\n");
}

void printDoubleTab(double *matrix, int p)
{
    printf("first = %f\n", matrix[0]);
    for(int i = 0; i < p; i++)
    {
        printf("%f|", matrix[i + 1]);
    }
    printf("\n");
}

double* patternsConvertor(int ** patterns, int p, int q){
    double * result = malloc(((p*q)+1)* sizeof(double));
    result[0] = 0.0;
    int index = 1;
    for(int i = 0; i < p; i++){
        for (int j = 0; j < q; j++) {
            result[index] = patterns[i][j];
            index++;
        }
    }

    return result;
}

void printSolution(glp_prob *p, int nbColumns){
    printf("Best solution objective value z = %lf\n", glp_get_obj_val(p));
    for(int i = 1; i < nbColumns; i++){
        printf("%s = %lf\n", glp_get_col_name(p, i), glp_get_col_prim(p, i));
    }
}

int **solveOrder(order o) {

    int **patterns = malloc(o.numberSizes * sizeof(int *));
    int sizeOfPatterns = o.numberSizes - 1;
    for (int i = 0; i <= sizeOfPatterns; i++) {
        patterns[i] = malloc(o.numberSizes * sizeof(int));
        for (int j = 0; j < o.numberSizes; j++) {
            patterns[i][j] = i == j ? 1 : 0;
        }
    }

    int index = 0;
    glp_prob *lp;

    int *row_coef;
    int *col_coef;
    bool flag;

    double* dualSolution;
    int limit = 10000;

    do {
        index = 0;
        sizeOfPatterns++;
        row_coef = malloc(((sizeOfPatterns * o.numberSizes) + 1) * sizeof(int));
        col_coef = malloc(((sizeOfPatterns * o.numberSizes) + 1) * sizeof(int));
        for(int i = 0; i < sizeOfPatterns; i++){
            for(int j = 0; j < o.numberSizes; j++)
            {
                index++;
                row_coef[index] = j + 1;
                col_coef[index] = i + 1;

            }
        }
        row_coef[0] = 0;
        col_coef[0] = 0;

        //Creating problem
        lp = glp_create_prob();
        glp_term_out(GLP_OFF);
        glp_set_prob_name(lp, "order");
        glp_set_obj_dir(lp, GLP_MIN);

        //Creating Constraints
        glp_add_rows(lp, o.numberSizes);
        for (int i = 0; i < o.numberSizes; i++) {
            char constraint_name[STRINGLENGHT];
            sprintf(constraint_name, "constraint %d", i);
            glp_set_row_name(lp, i + 1, constraint_name); //naming constraints

            glp_set_row_bnds(lp, i + 1, GLP_FX, o.array[i][0], o.array[i][0]);
        }

        //Creating Variables
        glp_add_cols(lp, sizeOfPatterns);
        for (int i = 0; i < sizeOfPatterns; i++) {
            char variables_names[STRINGLENGHT];
            sprintf(variables_names, "x_%d", i);

            glp_set_col_bnds(lp, i + 1, GLP_LO, 0.0, 0.0);

            glp_set_obj_coef(lp, i + 1, 1);
        }

        double* matrix = patternsConvertor(patterns, sizeOfPatterns, o.numberSizes);

        //loading matrix
        glp_load_matrix(lp, (o.numberSizes * sizeOfPatterns), row_coef, col_coef, matrix);

        glp_simplex(lp, NULL);

        free(matrix);
        free(row_coef);
        free(col_coef);

        //get Dual solutions
        dualSolution = malloc(o.numberSizes * sizeof(double));
        for (int i = 1; i <= o.numberSizes; i++) {
            dualSolution[i - 1] = glp_get_row_dual(lp, i);
        }

        patterns = realloc(patterns, (sizeOfPatterns + 1) * sizeof(int*));//Making room for extra line
        flag = add_new_pattern(dualSolution, o, patterns, sizeOfPatterns);

        free(dualSolution);

        glp_delete_prob(lp);
        glp_free_env();
        limit--;
    } while (flag && limit > 0);//add_new_pattern(lp, patterns, o, sizeOfPatterns)

    if(limit == 0)
        printf("ERROR: limit atteinte\n");

    printf("z = %lf\n", glp_get_obj_val(lp));

    printTab(patterns, sizeOfPatterns, o.numberSizes);

    printf("fait en %d itaration\n", 10000 - limit);

    for (int i = 0; i < sizeOfPatterns; i++)
        free(patterns[i]);
    free(patterns);

    return NULL;
}

void printIntSolution(glp_prob *p, int nbColumns) {
    printf("Best solution objective value z = %lf\n", glp_mip_obj_val(p));
    for(int i = 1; i <= nbColumns; i++){
        printf("%s = %d\n", glp_get_col_name(p, i), (int) glp_mip_col_val(p, i));
    }
}

bool add_new_pattern(double *dualSolution, order o, int **patterns, int sizeOfPattern) {

    glp_prob *s;

    //Creating problem
    s = glp_create_prob();
    glp_term_out(GLP_OFF);
    glp_set_prob_name(s, "Sac a dos");
    glp_set_obj_dir(s, GLP_MAX);



    //Creating Constraints
    glp_add_rows(s, 1);

    glp_set_row_name(s, 1, "constraint"); //naming constraints
    glp_set_row_bnds(s, 1, GLP_UP, 0.0, o.initWidth);

    //Creating Variables
    glp_add_cols(s, o.numberSizes);
    for (int i = 1; i <= o.numberSizes; i++) {
        char variables_names[STRINGLENGHT];
        sprintf(variables_names, "a_%d", i);
        glp_set_col_name(s, i, variables_names);
        glp_set_col_bnds(s, i, GLP_LO, 0.0, 0.0);

        glp_set_obj_coef(s, i, dualSolution[i - 1]);

        glp_set_col_kind(s, i, GLP_IV);
    }

    int *row_coef = malloc((o.numberSizes + 1) * sizeof(int));
    row_coef[0] = 0;
    for (int j = 1; j <= o.numberSizes; j++)
        row_coef[j] = 1;

    int *col_coef = malloc((o.numberSizes + 1) * sizeof(int));
    for (int j = 1; j <= o.numberSizes; j++)
        col_coef[j] = j;
    col_coef[0] = 0;

    double *matrix = malloc((o.numberSizes + 1) * sizeof(double));
    matrix[0] = 0.0;
    for (int i = 1; i < o.numberSizes + 1; i++)
        matrix[i] = o.array[i - 1][1];

    glp_load_matrix(s, o.numberSizes, row_coef, col_coef, matrix);

    glp_simplex(s, NULL);
    glp_intopt(s, NULL);

    free(col_coef);
    free(row_coef);
    free(matrix);

    if (glp_mip_obj_val(s) <= 1.0 + TAUX_ERREUR) //Neccessaire car erreur d'arrondi
        return false;

    patterns[sizeOfPattern] = malloc(o.numberSizes * sizeof(int));
    for (int i = 0; i < o.numberSizes; i++) {
        patterns[sizeOfPattern][i] = (int) glp_mip_col_val(s, i + 1);
    }

    glp_delete_prob(s);

    return true;
}
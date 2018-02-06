//
// Created by raphael on 2/2/18.
//

#include "orderSolver.h"

/*
 * Solve an order
 *
 * return: array[n][m]
 */

int **solveOrder(order o) {

    glp_prob *lp;

    //Creating problem
    lp = glp_create_prob();
    glp_set_prob_name(lp, "order");
    glp_set_obj_dir(lp, GLP_MIN);



    return NULL;
}

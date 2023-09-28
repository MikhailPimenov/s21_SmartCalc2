#include "view/view.h"
#include "model/model.h"
#include "controller/controller.h"

/**
*@mainpage  Smart Calc
* Smart Calc using C++, Qt and MVC pattern
*
*/


/*!
\file
\brief Entry point to calculator. This file contains main function

*/

/**
 * @brief 
 * The first function to be executed
 * @param argc Number of command line arguments (not used)
 * @param argv Command line arguments (not used)
 * @return int Error code (not used)
 */
int main(int argc, char *argv[]) {
    s21::Model model;
    s21::Controller controller(&model);

    return s21::main_view(argc, argv, &controller);
}
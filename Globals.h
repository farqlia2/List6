//
// Created by julia on 1/10/2023.
//

#ifndef LIST6_GLOBALS_H
#define LIST6_GLOBALS_H

# define DEBUG false

#include "string"

const std::string INSTANCES_DIR = R"(C:\Users\julia\CLionProjects\List6_\data)";
const std::string SOLUTIONS_DIR = R"(C:\Users\julia\CLionProjects\List6_\optimum)";
const std::string RESULTS_DIR = R"(C:\Users\julia\CLionProjects\List6_\results)";

const vector<string> LOW_DIM_PROBLEMS = {"f1_l-d_kp_10_269",
                                   "f2_l-d_kp_20_878",
                                   "f3_l-d_kp_4_20",
                                   "f4_l-d_kp_4_11",
                                   "f5_l-d_kp_15_375",
                                   "f6_l-d_kp_10_60",
                                   "f7_l-d_kp_7_50",
                                   "f8_l-d_kp_23_10000",
                                   "f9_l-d_kp_5_80",
                                   "f10_l-d_kp_20_879"};

const vector<string> LARGE_PROBLEMS = {
        "knapPI_1_100_1000_1",
        "knapPI_1_200_1000_1",
        "knapPI_2_100_1000_1",
        "knapPI_2_200_1000_1"
};

#endif //LIST6_GLOBALS_H

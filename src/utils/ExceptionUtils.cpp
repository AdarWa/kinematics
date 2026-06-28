//
// Created by adarw on 6/28/26.
//

#include "ExceptionUtils.hpp"

#include <iostream>
#include <ostream>

void kinematics::printException(std::exception& exception, bool hasDetails, const char* file, const char* func,
                                int line) {
    std::cerr << "Exception caught: " << exception.what();
    if (hasDetails) {
        std::cerr << ". " << file << ", " << func << ", line " << line;
    }
    std::cerr << std::endl;
}

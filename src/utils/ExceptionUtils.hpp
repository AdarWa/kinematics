//
// Created by adarw on 6/28/26.
//

#ifndef KINEMATICS_EXCEPTIONUTILS_HPP
#define KINEMATICS_EXCEPTIONUTILS_HPP
#include <exception>

#define KINEMATICS_TRY try {
#define KINEMATICS_CATCH } catch (std::exception e){ kinematics::printException(e, true, __FILE__, __func__, __LINE__); }

namespace kinematics {
    void printException(std::exception exception, bool hasDetails = false, const char* file = "", const char* func = "", int line = -1);
}

#endif //KINEMATICS_EXCEPTIONUTILS_HPP
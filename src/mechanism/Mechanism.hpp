//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_MECHANISM_HPP
#define KINEMATICS_MECHANISM_HPP
#include <memory>
#include <vector>

#include "joint/Joint.hpp"

namespace kinematics {
    class Mechanism {
    private:
        std::vector<std::unique_ptr<Joint>> joints;
    public:
        void addJoint(std::unique_ptr<Joint> joint);

    };
} // kinematics

#endif //KINEMATICS_MECHANISM_HPP
//
// Created by adarw on 6/8/26.
//

#include "RevoluteJoint.hpp"

namespace kinematics {
    Twist3d RevoluteJoint::calculateTwist() {
        Eigen::Vector3d omega = axis.normalized();
        Eigen::Vector3d linear = -omega.cross(origin);
        Twist3d twist;
        twist << linear, omega;
        return twist;
    }
} // kinematics
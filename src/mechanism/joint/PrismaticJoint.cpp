//
// Created by adarw on 6/8/26.
//

#include "PrismaticJoint.hpp"

namespace kinematics {
    Twist3d PrismaticJoint::calculateTwist() {
        Eigen::Vector3d linear = axis.normalized();
        Eigen::Vector3d omega = Eigen::Vector3d::Zero();
        Twist3d twist;
        twist << linear, omega;
        return twist;
    }
} // kinematics
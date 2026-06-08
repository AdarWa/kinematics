//
// Created by adarw on 6/7/26.
//

#include "rotations.hpp"
#include <Eigen/Eigen>

namespace kinematics::rotation {
    Eigen::Matrix3d hat(const Eigen::Vector3d& v) {
        Eigen::Matrix3d vHat;
        vHat <<   0,  -v(2),  v(1),
                v(2),     0, -v(0),
               -v(1),  v(0),     0;
        return vHat;
    }

    Eigen::Matrix3d rotationMatrix(const Eigen::Vector3d& uUnit, double theta) {
        // Using Rodrigues’ Formula
        Eigen::Matrix3d identity = Eigen::Matrix3d::Identity(3,3);
        Eigen::Matrix3d uHat = hat(uUnit);
        return identity + uHat*sin(theta) + uHat*uHat*(1-cos(theta));
    }

    Eigen::Vector3d rotateAround(const Eigen::Vector3d& input, const Eigen::Vector3d& axis, double theta) {
        Eigen::Vector3d uUnit = axis.normalized();
        Eigen::Matrix3d rotMatrix = rotationMatrix(uUnit, theta);
        return rotMatrix*input;
    }
}
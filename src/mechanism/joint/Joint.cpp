//
// Created by adarw on 6/8/26.
//

#include "Joint.hpp"
#include <unsupported/Eigen/MatrixFunctions>

namespace kinematics {
    Pose3d Joint::calculatePose() {
        if (!twist) {
            twist = calculateTwist();
        }

        Eigen::Vector3d v = twist->head<3>();
        Eigen::Vector3d omega = twist->tail<3>();

        Eigen::Matrix3d I = Eigen::Matrix3d::Identity();

        Eigen::Matrix3d omega_skew;
        omega_skew <<   0.0,     -omega.z(),  omega.y(),
                      omega.z(),   0.0,      -omega.x(),
                     -omega.y(),  omega.x(),   0.0;

        Eigen::Matrix3d omega_skew_sq = omega_skew * omega_skew;

        Eigen::Matrix3d G = I * theta +
                            (1.0 - std::cos(theta)) * omega_skew +
                            (theta - std::sin(theta)) * omega_skew_sq;
        Eigen::Vector3d p = G * v;

        Pose3d pose;

        Eigen::Matrix3d R = I +
                            std::sin(theta) * omega_skew +
                            (1.0 - std::cos(theta)) * omega_skew_sq;

        Eigen::Vector3d euler = R.eulerAngles(0, 1, 2);
        pose << p, euler;

        return pose;
    }

    void Joint::setTheta(double theta) {
        this->theta = theta;
    }

    double Joint::getTheta() const {
        return theta;
    }
} // kinematics
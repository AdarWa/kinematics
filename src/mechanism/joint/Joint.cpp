//
// Created by adarw on 6/8/26.
//

#include "Joint.hpp"
#include <unsupported/Eigen/MatrixFunctions>

namespace kinematics {
    Transform Joint::calculateTransformation() {
        if (!twist) {
            twist = calculateTwist();
        }

        Eigen::Vector3d linear = twist->head<3>(); // linear component of twist
        Eigen::Vector3d omega = twist->tail<3>(); // angular component of twist

        Eigen::Matrix3d I = Eigen::Matrix3d::Identity();

        Eigen::Matrix3d omega_skew; // omega_hat
        omega_skew <<   0.0,     -omega.z(),  omega.y(),
                      omega.z(),   0.0,      -omega.x(),
                     -omega.y(),  omega.x(),   0.0;

        Eigen::Matrix3d omega_skew_sq = omega_skew * omega_skew;

        Eigen::Matrix3d G = I * theta +
                            (1.0 - std::cos(theta)) * omega_skew +     // Translation matrix
                            (theta - std::sin(theta)) * omega_skew_sq; // Integration over rodrigues formula with respect to theta, same as e^(twist_hat*theta)


        Eigen::Matrix3d R = I +
                            std::sin(theta) * omega_skew +           // Rotation matrix
                            (1.0 - std::cos(theta)) * omega_skew_sq; // Rodrigues formula, same as e^(omega_hat*theta)
        Transform transform;
        transform.translation = G;
        transform.rotation = R;
        return transform;
    }

    Pose3d Joint::calculatePose() {
        Transform transform = calculateTransformation(); // twist is guaranteed to be initialized

        Eigen::Vector3d linear = twist->head<3>(); // linear component of twist

        Eigen::Vector3d p = transform.translation * linear; // position after transformation
        Eigen::Vector3d euler = transform.rotation.eulerAngles(0, 1, 2); // rotation after transformation

        Pose3d pose;
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
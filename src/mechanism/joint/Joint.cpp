//
// Created by adarw on 6/8/26.
//

#include "Joint.hpp"

#include "../../utils/MathUtils.hpp"

namespace kinematics {
    Transform Joint::calculateTransformation() {
        if (!twist) {
            twist = calculateTwist();
        }

        const Eigen::Vector3d linear = twist->head<3>(); // linear component of twist
        const Eigen::Vector3d omega = twist->tail<3>(); // angular component of twist

        const Eigen::Matrix3d I = Eigen::Matrix3d::Identity();

        const Eigen::Matrix3d omega_skew = makeSkewSymmetric(omega); // omega_hat

        const Eigen::Matrix3d omega_skew_sq = omega_skew * omega_skew;

        const Eigen::Matrix3d G = I * theta +
                            (1.0 - std::cos(theta)) * omega_skew +     // Translation matrix
                            (theta - std::sin(theta)) * omega_skew_sq; // Integration over rodrigues formula with respect to theta, same as e^(twist_hat*theta)


        const Eigen::Matrix3d R = I +
                            std::sin(theta) * omega_skew +           // Rotation matrix
                            (1.0 - std::cos(theta)) * omega_skew_sq; // Rodrigues formula, same as e^(omega_hat*theta)
        Transform transform;
        transform.translation = G * linear;
        transform.rotation = R;
        return transform;
    }

    void Joint::setTheta(const double newTheta) {
        this->theta = newTheta;
    }

    double Joint::getTheta() const {
        return theta;
    }

    Translation3d& Joint::getOrigin() {
        return origin;
    }
} // kinematics
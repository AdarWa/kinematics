//
// Created by adarw on 6/8/26.
//

#include "Mechanism.hpp"

#include "utils/MathUtils.hpp"

namespace kinematics {
    Mechanism::Mechanism(Pose3d& homePose) {
        homeState = makeStateMatrix(homePose);
    }

    void Mechanism::addJoint(std::unique_ptr<Joint> joint) {
        joints.push_back(std::move(joint));
    }

    Transform Mechanism::calculateTransform() const {
        Eigen::Matrix4d transform = Eigen::Matrix4d::Identity(); // T = T1*T2*...*Tn*g_st(0) PoE rule
        for (const auto& joint : joints) {
            transform *= joint->calculateTransformation().toMatrix();
        }
        transform *= homeState;
        return Transform::fromMatrix(transform);
    }

    Pose3d Mechanism::calculatePose() const {
        Transform t = calculateTransform();
        return makePose3dFromTransform(t);
    }
} // kinematics
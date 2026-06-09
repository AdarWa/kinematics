//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_MECHANISM_HPP
#define KINEMATICS_MECHANISM_HPP
#include <memory>
#include <vector>

#include "joint/Joint.hpp"

namespace kinematics {
    class Mechanism : public Transformable {
    private:
        std::vector<std::unique_ptr<Joint>> joints;
        Eigen::Matrix4d homeState;
    public:
        explicit Mechanism(Pose3d& homePose);
        void addJoint(std::unique_ptr<Joint> joint);
        Transform calculateTransformation() override;
    };
} // kinematics

#endif //KINEMATICS_MECHANISM_HPP
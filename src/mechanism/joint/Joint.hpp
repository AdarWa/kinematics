//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_JOINT_HPP
#define KINEMATICS_JOINT_HPP
#include <optional>
#include <utility>

#include "Transform.hpp"
#include "../../defs.hpp"
#include "mechanism/Transformable.hpp"

namespace kinematics {
    class Joint : public Transformable {
    protected:
        Translation3d origin;
        std::optional<Twist3d> twist;
        double theta;
    public:
        explicit Joint(Translation3d  origin_pose = Translation3d(), const double theta = 0) : origin(std::move(origin_pose)), theta(theta) {}
        virtual Twist3d calculateTwist() = 0;
        Transform calculateTransformation() override;
        void setTheta(double newTheta);
        [[nodiscard]] double getTheta() const;
        Translation3d& getOrigin();

    };
} // kinematics

#endif //KINEMATICS_JOINT_HPP
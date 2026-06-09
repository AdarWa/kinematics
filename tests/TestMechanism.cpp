//
// Created by adarw on 6/9/26.
//

#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "mechanism/Mechanism.hpp"
#include "mechanism/joint/PrismaticJoint.hpp"
#include "mechanism/joint/RevoluteJoint.hpp"

using namespace kinematics;

class MechanismTest : public ::testing::Test {
protected:
    Pose3d homePose;

    void SetUp() override {
        homePose << 0, 0, 0, 0, 0, 0; // Identity home pose
    }
};

TEST_F(MechanismTest, EmptyMechanism) {
    Mechanism robot(homePose);

    Transform t = robot.calculateTransform();

    EXPECT_TRUE(t.translation.isApprox(Eigen::Vector3d::Zero(), 1e-6));
    EXPECT_TRUE(t.rotation.isApprox(Eigen::Matrix3d::Identity(), 1e-6));
}

TEST_F(MechanismTest, SinglePrismaticJoint) {
    Mechanism robot(homePose);

    // Move 10 units along the Y axis
    auto joint = std::make_unique<PrismaticJoint>(
        Translation3d(0, 0, 0),
        Eigen::Vector3d(0, 1, 0),
        10.0
    );
    robot.addJoint(std::move(joint));

    Transform t = robot.calculateTransform();

    EXPECT_TRUE(t.translation.isApprox(Eigen::Vector3d(0, 10.0, 0), 1e-6));
    EXPECT_TRUE(t.rotation.isApprox(Eigen::Matrix3d::Identity(), 1e-6));
}

TEST_F(MechanismTest, MultiJointPoE) {
    Mechanism robot(homePose);

    // 1st Joint: Rotate 90 deg around Z
    auto rev_joint = std::make_unique<RevoluteJoint>(
        Translation3d(0, 0, 0),
        Eigen::Vector3d(0, 0, 1),
        M_PI / 2.0
    );

    // 2nd Joint: Translate 5 units along X (relative to previous joint's frame)
    auto pris_joint = std::make_unique<PrismaticJoint>(
        Translation3d(0, 0, 0),
        Eigen::Vector3d(1, 0, 0),
        5.0
    );

    robot.addJoint(std::move(rev_joint));
    robot.addJoint(std::move(pris_joint));

    Transform t = robot.calculateTransform();

    // Since the first joint rotated the frame 90 degrees around Z,
    // translating along the X axis actually translates along the global Y axis.
    Eigen::Vector3d expected_translation(0, 5.0, 0);
    EXPECT_TRUE(t.translation.isApprox(expected_translation, 1e-6));

    Eigen::Matrix3d expected_rotation = Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    EXPECT_TRUE(t.rotation.isApprox(expected_rotation, 1e-6));
}
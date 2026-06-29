//
// Created by adarw on 6/28/26.
//


#include "transform/AssetFactory.hpp"
#include "transform/TransformUtils.hpp"
#include "world/World.hpp"

int main(int argc, char* argv[]) {
    using namespace kinematics::viewer;
    World world;
    // world.loadModel("model_0.glb");
    utils::Entity entity = AssetFactory::getInstance().createCuboid(BasicMaterialType::METALLIC_GOLD, {0.5,0.5,0.5});
    auto rotation = transforms::makeEulerAngleTransform(0,0,transforms::deg2rad(20));
    transformEntity(world.getEngine(),entity, rotation);
    world.injectEntity(entity);
    world.run();
}

//
// Created by adarw on 6/29/26.
//

#include "AssetFactory.hpp"

#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/VertexBuffer.h>
#include <filament/IndexBuffer.h>
#include <filament/RenderableManager.h>
#include <utils/EntityManager.h>

#include <fstream>
#include <iostream>
#include <vector>

namespace kinematics::viewer {

    void AssetFactory::initialize(filament::Engine* enginePtr, const std::string& baseMaterialPath) {
        if (this->engine != nullptr) {
            std::cerr << "[AssetFactory] Already initialized!" << std::endl;
            return;
        }
        this->engine = enginePtr;

        std::ifstream file(baseMaterialPath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            std::cerr << "[AssetFactory] Failed to open material at: " << baseMaterialPath << std::endl;
            return;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        if (!file.read(buffer.data(), size)) {
            std::cerr << "[AssetFactory] Failed to read material bytes!" << std::endl;
            return;
        }

        masterMaterial = filament::Material::Builder()
            .package(buffer.data(), buffer.size())
            .build(*engine);

        setupMaterials();
    }

    void AssetFactory::setupMaterials() {
        if (!masterMaterial) return;

        auto createInstance = [&](BasicMaterialType type, filament::math::float4 color, float metallic, float roughness) {
            filament::MaterialInstance* inst = masterMaterial->createInstance();
            inst->setParameter("baseColor", color);
            inst->setParameter("metallic", metallic);
            inst->setParameter("roughness", roughness);
            inst->setParameter("reflectance", 0.6f);
            materials[type] = inst;
        };

        // Standard sRGB colors
        createInstance(BasicMaterialType::DEFAULT_WHITE, {0.85f, 0.85f, 0.85f, 1.0f}, 0.0f, 0.6f);
        createInstance(BasicMaterialType::DEBUG_RED,     {0.90f, 0.10f, 0.10f, 1.0f}, 0.0f, 0.4f);
        createInstance(BasicMaterialType::DEBUG_GREEN,   {0.10f, 0.90f, 0.10f, 1.0f}, 0.0f, 0.4f);
        createInstance(BasicMaterialType::DEBUG_BLUE,    {0.10f, 0.10f, 0.90f, 1.0f}, 0.0f, 0.4f);
        createInstance(BasicMaterialType::METALLIC_GOLD, {1.00f, 0.76f, 0.33f, 1.0f}, 0.8f, 0.8f);
    }

    utils::Entity AssetFactory::createCuboid(BasicMaterialType matType, filament::math::float3 size) {
        if (!engine) return {};

        float hx = size.x * 0.5f;
        float hy = size.y * 0.5f;
        float hz = size.z * 0.5f;

        // Heap-allocated because the coordinates change dynamically based on size
        auto* rawVerts = new filament::math::float3[8]{
            {-hx, -hy,  hz}, { hx, -hy,  hz}, {-hx,  hy,  hz}, { hx,  hy,  hz},
            {-hx, -hy, -hz}, { hx, -hy, -hz}, {-hx,  hy, -hz}, { hx,  hy, -hz}
        };

        // Static because cuboid topology never changes
        static const uint16_t CUBOID_INDICES[36] = {
            0,1,2, 2,1,3,  1,5,3, 3,5,7,  5,4,7, 7,4,6,
            4,0,6, 6,0,2,  2,3,6, 6,3,7,  4,5,0, 0,5,1
        };

        auto* vb = filament::VertexBuffer::Builder()
            .vertexCount(8).bufferCount(1)
            .attribute(filament::VertexAttribute::POSITION, 0, filament::VertexBuffer::AttributeType::FLOAT3)
            .build(*engine);

        vb->setBufferAt(*engine, 0, filament::VertexBuffer::BufferDescriptor(
            rawVerts, 8 * sizeof(filament::math::float3),
            [](void* buf, size_t, void*) { delete[] static_cast<filament::math::float3*>(buf); }
        ));

        auto* ib = filament::IndexBuffer::Builder()
            .indexCount(36).bufferType(filament::IndexBuffer::IndexType::USHORT)
            .build(*engine);

        ib->setBuffer(*engine, filament::IndexBuffer::BufferDescriptor(CUBOID_INDICES, sizeof(CUBOID_INDICES)));

        allocatedBuffers.emplace_back(vb, ib);

        utils::Entity entity = utils::EntityManager::get().create();
        filament::RenderableManager::Builder(1)
            .boundingBox({{-hx, -hy, -hz}, {hx, hy, hz}})
            .geometry(0, filament::RenderableManager::PrimitiveType::TRIANGLES, vb, ib)
            .material(0, materials[matType])
            .build(*engine, entity);

        return entity;
    }

    utils::Entity AssetFactory::createSphere(BasicMaterialType matType, float radius) {
        if (!engine) return {};

        constexpr uint32_t SLICES = 24;
        constexpr uint32_t STACKS = 16;

        std::vector<filament::math::float3> tempVerts;
        std::vector<uint16_t> tempIndices;

        for (uint32_t i = 0; i <= STACKS; ++i) {
            float v = static_cast<float>(i) / STACKS;
            float phi = v * filament::math::F_PI;
            for (uint32_t j = 0; j <= SLICES; ++j) {
                float u = static_cast<float>(j) / SLICES;
                float theta = u * (filament::math::F_PI * 2.0f);

                tempVerts.push_back({
                    std::cos(theta) * std::sin(phi) * radius,
                    std::cos(phi) * radius,
                    std::sin(theta) * std::sin(phi) * radius
                });
            }
        }

        for (uint32_t i = 0; i < STACKS; ++i) {
            for (uint32_t j = 0; j < SLICES; ++j) {
                uint16_t first = (i * (SLICES + 1)) + j;
                uint16_t second = first + SLICES + 1;

                tempIndices.push_back(first);
                tempIndices.push_back(second);
                tempIndices.push_back(first + 1);

                tempIndices.push_back(second);
                tempIndices.push_back(second + 1);
                tempIndices.push_back(first + 1);
            }
        }

        auto* rawVerts = new filament::math::float3[tempVerts.size()];
        std::copy(tempVerts.begin(), tempVerts.end(), rawVerts);

        auto* rawIndices = new uint16_t[tempIndices.size()];
        std::copy(tempIndices.begin(), tempIndices.end(), rawIndices);

        auto* vb = filament::VertexBuffer::Builder()
            .vertexCount(tempVerts.size()).bufferCount(1)
            .attribute(filament::VertexAttribute::POSITION, 0, filament::VertexBuffer::AttributeType::FLOAT3)
            .build(*engine);

        vb->setBufferAt(*engine, 0, filament::VertexBuffer::BufferDescriptor(
            rawVerts, tempVerts.size() * sizeof(filament::math::float3),
            [](void* buf, size_t, void*) { delete[] static_cast<filament::math::float3*>(buf); }
        ));

        auto* ib = filament::IndexBuffer::Builder()
            .indexCount(tempIndices.size()).bufferType(filament::IndexBuffer::IndexType::USHORT)
            .build(*engine);

        ib->setBuffer(*engine, filament::IndexBuffer::BufferDescriptor(
            rawIndices, tempIndices.size() * sizeof(uint16_t),
            [](void* buf, size_t, void*) { delete[] static_cast<uint16_t*>(buf); }
        ));

        allocatedBuffers.emplace_back(vb, ib);

        utils::Entity entity = utils::EntityManager::get().create();
        filament::RenderableManager::Builder(1)
            .boundingBox({{-radius, -radius, -radius}, {radius, radius, radius}})
            .geometry(0, filament::RenderableManager::PrimitiveType::TRIANGLES, vb, ib)
            .material(0, materials[matType])
            .build(*engine, entity);

        return entity;
    }

    void AssetFactory::shutdown() {
        if (!engine) return;

        for (auto& [vb, ib] : allocatedBuffers) {
            engine->destroy(vb);
            engine->destroy(ib);
        }
        allocatedBuffers.clear();

        for (auto& [type, inst] : materials) {
            engine->destroy(inst);
        }
        materials.clear();

        if (masterMaterial) {
            engine->destroy(masterMaterial);
            masterMaterial = nullptr;
        }

        engine = nullptr;
    }

}

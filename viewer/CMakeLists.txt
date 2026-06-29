file(GLOB_RECURSE VIEWER_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_executable(viewer ${VIEWER_SOURCES})

target_link_libraries(viewer PRIVATE kinematics_core)

set(FILAMENT_DIR "${SOURCE_ROOT}/filament")

# more clang shit
target_compile_options(viewer PRIVATE "-stdlib=libc++")
target_link_options(viewer PRIVATE "-stdlib=libc++")

target_include_directories(viewer PRIVATE "${FILAMENT_DIR}/include"
        "${FILAMENT_DIR}/include/geometry")

target_link_directories(viewer PRIVATE "${FILAMENT_DIR}/lib/x86_64")

target_link_libraries(viewer PRIVATE
        # --- High-Level GLTF & Materials ---
        gltfio
        gltfio_core
        filamat
        shaders       # <--- ADD THIS: Filament's raw shader package

        # --- 3D Model & Image Compression Dependencies ---
        image
        basis_transcoder
        dracodec
        meshoptimizer
        ktxreader
        stb

        # --- Core Engine ---
        filament
        backend
        bluegl
        bluevk
        filabridge
        filaflat
        geometry
        smol-v
        utils

        # --- System & Standard Libraries ---
        zstd
        c++
        c++abi
        pthread
        dl
)

find_package(SDL2 REQUIRED)

target_include_directories(viewer PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(viewer PRIVATE ${SDL2_LIBRARIES})

# Compile all materials

set(MATC_EXE "${CMAKE_CURRENT_SOURCE_DIR}/../filament/bin/matc")

file(GLOB_RECURSE MAT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/materials/*.mat")

set(FILAMAT_OUTPUTS "")

foreach(MAT_FILE ${MAT_SOURCES})
    get_filename_component(MAT_NAME ${MAT_FILE} NAME_WE)

    set(OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/materials/${MAT_NAME}.filamat")

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/materials")

    add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${MATC_EXE} -a all -o ${OUTPUT_FILE} ${MAT_FILE}
            DEPENDS ${MAT_FILE}
            COMMENT "Compiling Filament material: ${MAT_NAME}.mat -> ${MAT_NAME}.filamat"
    )
    list(APPEND FILAMAT_OUTPUTS ${OUTPUT_FILE})
endforeach()

add_custom_target(compile_all_materials DEPENDS ${FILAMAT_OUTPUTS})

add_dependencies(viewer compile_all_materials)
file(GLOB_RECURSE VIEWER_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_executable(viewer ${VIEWER_SOURCES})

target_link_libraries(viewer PRIVATE kinematics_core)

set(FILAMENT_DIR "${SOURCE_ROOT}/filament")

# more clang shit
target_compile_options(viewer PRIVATE "-stdlib=libc++")
target_link_options(viewer PRIVATE "-stdlib=libc++")

target_include_directories(viewer PRIVATE "${FILAMENT_DIR}/include")

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
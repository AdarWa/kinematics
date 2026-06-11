//
// Created by adarw on 6/11/26.
//

#ifndef KINEMATICS_WINDOWUTILS_HPP
#define KINEMATICS_WINDOWUTILS_HPP
#include <SDL_video.h>

namespace kinematics::viewer{
    void* setupNativeWindow(const char* title, int w, int h, SDL_Window** sdl_window);
    void destroyWindow(SDL_Window* window);
}

#endif //KINEMATICS_WINDOWUTILS_HPP
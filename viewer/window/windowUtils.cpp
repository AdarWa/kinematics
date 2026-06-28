//
// Created by adarw on 6/11/26.
//

#include "windowUtils.hpp"

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_video.h>

namespace kinematics::viewer {
    static void* getNativeWindow(SDL_Window* window) {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        SDL_GetWindowWMInfo(window, &wmi);
#if defined(SDL_VIDEO_DRIVER_X11)
        return (void*)wmi.info.x11.window;
#elif defined(SDL_VIDEO_DRIVER_WAYLAND)
        return (void*)wmi.info.wl.surface;
#endif
        return nullptr;
    }

    void* setupNativeWindow(const char* title, int w, int h, std::shared_ptr<SDL_Window*> sdl_window) {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        *sdl_window = window;
        return getNativeWindow(window);
    }

    void destroyWindow(SDL_Window* window) {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

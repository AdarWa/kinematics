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
        if (!SDL_GetWindowWMInfo(window, &wmi)) {
            return nullptr;
        }

        switch (wmi.subsystem) {
#if defined(SDL_VIDEO_DRIVER_X11)
        case SDL_SYSWM_X11:
            return (void*)wmi.info.x11.window;
#endif
#if defined(SDL_VIDEO_DRIVER_WAYLAND)
        case SDL_SYSWM_WAYLAND:
            return (void*)wmi.info.wl.surface;
#endif
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
        case SDL_SYSWM_WINDOWS:
            return (void*)wmi.info.win.window;
#endif
#if defined(SDL_VIDEO_DRIVER_COCOA)
        case SDL_SYSWM_COCOA:
            return (void*)wmi.info.cocoa.window;
#endif
        default:
            return nullptr;
        }
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

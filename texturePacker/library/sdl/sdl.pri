HEADERS +=  $$PWD/include/SDL2/begin_code.h \
            $$PWD/include/SDL2/close_code.h \
            $$PWD/include/SDL2/SDL.h \
            $$PWD/include/SDL2/SDL_assert.h \
            $$PWD/include/SDL2/SDL_atomic.h \
            $$PWD/include/SDL2/SDL_audio.h \
            $$PWD/include/SDL2/SDL_bits.h \
            $$PWD/include/SDL2/SDL_blendmode.h \
            $$PWD/include/SDL2/SDL_clipboard.h \
            $$PWD/include/SDL2/SDL_config.h \
            $$PWD/include/SDL2/SDL_config_android.h \
            $$PWD/include/SDL2/SDL_config_iphoneos.h \
            $$PWD/include/SDL2/SDL_config_macosx.h \
            $$PWD/include/SDL2/SDL_config_minimal.h \
            $$PWD/include/SDL2/SDL_config_pandora.h \
            $$PWD/include/SDL2/SDL_config_psp.h \
            $$PWD/include/SDL2/SDL_config_windows.h \
            $$PWD/include/SDL2/SDL_config_winrt.h \
            $$PWD/include/SDL2/SDL_config_wiz.h \
            $$PWD/include/SDL2/SDL_copying.h \
            $$PWD/include/SDL2/SDL_cpuinfo.h \
            $$PWD/include/SDL2/SDL_egl.h \
            $$PWD/include/SDL2/SDL_endian.h \
            $$PWD/include/SDL2/SDL_error.h \
            $$PWD/include/SDL2/SDL_events.h \
            $$PWD/include/SDL2/SDL_filesystem.h \
            $$PWD/include/SDL2/SDL_gamecontroller.h \
            $$PWD/include/SDL2/SDL_gesture.h \
            $$PWD/include/SDL2/SDL_haptic.h \
            $$PWD/include/SDL2/SDL_hints.h \
            $$PWD/include/SDL2/SDL_joystick.h \
            $$PWD/include/SDL2/SDL_keyboard.h \
            $$PWD/include/SDL2/SDL_keycode.h \
            $$PWD/include/SDL2/SDL_loadso.h \
            $$PWD/include/SDL2/SDL_log.h \
            $$PWD/include/SDL2/SDL_main.h \
            $$PWD/include/SDL2/SDL_messagebox.h \
            $$PWD/include/SDL2/SDL_mouse.h \
            $$PWD/include/SDL2/SDL_mutex.h \
            $$PWD/include/SDL2/SDL_name.h \
            $$PWD/include/SDL2/SDL_opengl.h \
            $$PWD/include/SDL2/SDL_opengles.h \
            $$PWD/include/SDL2/SDL_opengles2.h \
            $$PWD/include/SDL2/SDL_pixels.h \
            $$PWD/include/SDL2/SDL_platform.h \
            $$PWD/include/SDL2/SDL_power.h \
            $$PWD/include/SDL2/SDL_quit.h \
            $$PWD/include/SDL2/SDL_rect.h \
            $$PWD/include/SDL2/SDL_render.h \
            $$PWD/include/SDL2/SDL_revision.h \
            $$PWD/include/SDL2/SDL_rwops.h \
            $$PWD/include/SDL2/SDL_scancode.h \
            $$PWD/include/SDL2/SDL_shape.h \
            $$PWD/include/SDL2/SDL_stdinc.h \
            $$PWD/include/SDL2/SDL_surface.h \
            $$PWD/include/SDL2/SDL_system.h \
            $$PWD/include/SDL2/SDL_syswm.h \
            $$PWD/include/SDL2/SDL_test.h \
            $$PWD/include/SDL2/SDL_test_assert.h \
            $$PWD/include/SDL2/SDL_test_common.h \
            $$PWD/include/SDL2/SDL_test_compare.h \
            $$PWD/include/SDL2/SDL_test_crc32.h \
            $$PWD/include/SDL2/SDL_test_font.h \
            $$PWD/include/SDL2/SDL_test_fuzzer.h \
            $$PWD/include/SDL2/SDL_test_harness.h \
            $$PWD/include/SDL2/SDL_test_images.h \
            $$PWD/include/SDL2/SDL_test_log.h \
            $$PWD/include/SDL2/SDL_test_md5.h \
            $$PWD/include/SDL2/SDL_test_random.h \
            $$PWD/include/SDL2/SDL_thread.h \
            $$PWD/include/SDL2/SDL_timer.h \
            $$PWD/include/SDL2/SDL_touch.h \
            $$PWD/include/SDL2/SDL_types.h \
            $$PWD/include/SDL2/SDL_version.h \
            $$PWD/include/SDL2/SDL_video.h


macx: LIBS += -F$$PWD/libs/mac/ -framework SDL2
#unix: LIBS += -L$$PWD/libs/linux_64/ -lSDL2

INCLUDEPATH += $$PWD/libs
INCLUDEPATH += $$PWD/libs/include

DEPENDPATH += $$PWD/libs

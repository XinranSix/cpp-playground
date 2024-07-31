add_includedirs(
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui",
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/backends",
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/misc/cpp",
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/misc/freetype"
    )

target("imgui")
    set_kind("static")
    add_files(
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/*.cpp",
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/backends/imgui_impl_glfw.cpp",
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/backends/imgui_impl_opengl3.cpp",
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/backends/imgui_impl_sdl2.cpp",
    "$(projectdir)/3rdparty/imgui/3rdparty/imgui/misc/cpp/*.cpp"
    -- "$(projectdir)/3rdparty/imgui/3rdparty/imgui/misc/freetype/*.cpp"
    )
    add_packages("libsdl", "opengl", "glfw", "glad")
  
includes("imgui")

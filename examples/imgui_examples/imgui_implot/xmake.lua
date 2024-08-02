for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('imgui_implot_' .. path.basename(filepath))
    add_files(filepath)
    add_deps("imgui", "implot")
    add_packages("libsdl", "opengl", "glfw", "glad")
end

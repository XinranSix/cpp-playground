for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('imgui_examples_imgui_' .. path.basename(filepath))
    add_files(filepath)
    add_deps("imgui")
    add_packages("libsdl", "opengl", "glfw", "glad")
end

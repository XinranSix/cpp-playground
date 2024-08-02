for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('imgui_markdown_examples_' .. path.basename(filepath))
    add_files(filepath)
    add_deps("imgui")
    add_packages("opengl", "glfw", "glad")
end

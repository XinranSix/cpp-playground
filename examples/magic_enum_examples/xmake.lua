for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('magic_enum_examples_' .. path.basename(filepath))
    add_files(filepath)
    add_packages("catch2", "boost", "fmt", "magic_enum")
end

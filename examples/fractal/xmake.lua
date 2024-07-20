for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('fractal_' .. path.basename(filepath))
    add_files(filepath)
    add_packages("fmt", "boost", "sfml")
end

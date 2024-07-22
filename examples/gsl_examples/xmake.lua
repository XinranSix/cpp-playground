for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('gsl_examples_' .. path.basename(filepath))
    add_files(filepath)
    add_packages("fmt", "microsoft-gsl")
end

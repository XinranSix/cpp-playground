for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('fmt_examples_' .. path.basename(filepath))
    add_files(filepath)
    add_packages("fmt", "boost")
end

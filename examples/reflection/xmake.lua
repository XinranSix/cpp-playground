add_includedirs("include")

for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('reflection_' .. path.basename(filepath))
    add_files(filepath)
    add_packages("fmt", "boost")
end

for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('type_traits_' .. path.basename(filepath))
    add_files(filepath)
end

for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('coroutines_' .. path.basename(filepath))
    add_files(filepath)
end

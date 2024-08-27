for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('multithreading_' .. path.basename(filepath))
    add_files(filepath)
end

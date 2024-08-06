for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('thread_' .. path.basename(filepath))
    add_files(filepath)
end

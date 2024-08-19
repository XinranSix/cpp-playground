for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('design_pattern_crtp_' .. path.basename(filepath))
    add_files(filepath)
end

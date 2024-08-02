for _, filepath in ipairs(os.files("./src/**.cpp")) do
target('cppguidebook_' .. path.basename(filepath))
    add_files(filepath)
    add_packages("boost", "fmt", "range-v3", "magic_enum", "robin-map", "backward-cpp", "iguana", "utfcpp", "rapidjson", "nlohmann_json",
    "highway", "eigen")
end

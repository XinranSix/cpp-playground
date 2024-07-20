set_project("cpp-playground")
set_version("1.0.0")

add_rules("mode.debug", "mode.release")

set_languages("c++23")

if is_plat("windows") then
    add_cxflags("/utf-8")
end

-- add_includedirs("include")

includes("examples")

add_requires("fmt") 
add_requires("boost", {configs = {all = true}}) 
add_requires("sfml") 
add_requires("boost_ut") 
add_requires("imgui docking") 
add_requires("libsdl", "libsdl_ttf", "libsdl_net", "libsdl_mixer", "libsdl_image") 

-- add_requires("range-v3") 
-- add_requires("joltphysics") 

target("main")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("libsdl", "libsdl_image")
  
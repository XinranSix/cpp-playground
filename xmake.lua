set_project("cpp-playground")
set_version("1.0.0")

add_rules("mode.debug", "mode.release")

set_languages("c++23")

if is_plat("windows") then
    add_cxflags("/utf-8")
end

add_includedirs("include")

includes("examples")
includes("tests")

add_requires("fmt") 
add_requires("boost", {configs = {all = true}}) 
add_requires("boost_ut") 
add_requires("microsoft-gsl") 
add_requires("sfml") 
add_requires("libsdl", "libsdl_ttf", "libsdl_net", "libsdl_mixer", "libsdl_image") 
add_requires("box2d") 
add_requires("catch2")
add_requires("rttr")
add_requires("magic_enum")
add_requires("nameof")
-- add_requires("imgui docking") 
-- add_requires("range-v3") 
-- add_requires("joltphysics") 

target("main")
    set_kind("binary")
    add_files("src/*.cpp")
    -- add_tests("default")
    add_packages("catch2", "boost", "fmt")
  
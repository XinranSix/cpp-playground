set_project("cpp-playground")
set_version("1.0.0")

add_rules("mode.debug", "mode.release")

set_languages("c++23")

if is_plat("windows") then
    add_cxflags("/utf-8")
    -- add_cxflags("/P")
end

add_includedirs("include")

includes("examples")
includes("tests")

-- rttr 一个反射库
package("rttr")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "3rdparty/rttr"))
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        table.insert(configs, "-DBUILD_UNIT_TESTS=OFF")
        table.insert(configs, "-DBUILD_BENCHMARKS=OFF")
        table.insert(configs, "-DBUILD_BENCHMARKS=OFF")
        table.insert(configs, "-DBUILD_EXAMPLES=OFF")
        import("package.tools.cmake").install(package, configs)
    end)
package_end()

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
add_requires("glfw") 
add_requires("glad") 
add_requires("opengl") 
add_requires("range-v3") 
add_requires("robin-map") 
add_requires("backward-cpp") 
add_requires("iguana") 
add_requires("utfcpp") 
add_requires("rapidjson") 
add_requires("nlohmann_json") 
add_requires("highway") 
add_requires("eigen") 
add_requires("yalantinglibs") 
add_requires("onetbb") 

-- add_requires("amgcl") 
-- add_requires("numcpp") 
-- add_requires("joltphysics") 

target("main")
    set_kind("binary")
    add_files("src/*.cpp") 
    add_packages("catch2", "boost", "fmt", "rttr", "yalantinglibs")
  
-- xmake project -k compile_commands
-- xmake project -k makefile
-- xmake project -k cmakelists

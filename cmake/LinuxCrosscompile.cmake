set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER clang-cl)
set(CMAKE_CXX_COMPILER clang-cl)
set(CMAKE_LINKER lld-link)

set(CMAKE_C_COMPILER_FRONTEND_VARIANT MSVC)
set(CMAKE_CXX_COMPILER_FRONTEND_VARIANT MSVC)

# rm: locate winsysroot via the msbuild.exe path
find_program(_msbuild_exe msbuild)
if(_msbuild_exe)
    get_filename_component(_msbuild_bin ${_msbuild_exe} DIRECTORY)   # .../bin/x64
    get_filename_component(_candidate   "${_msbuild_bin}/.."  ABSOLUTE) # .../bin
    if(NOT IS_DIRECTORY "${_candidate}/vc")
        get_filename_component(_candidate "${_candidate}/.." ABSOLUTE)  # .../<root>
    endif()
    set(MSVC_WINSYSROOT ${_candidate})
else()
    # rm: assume /opt/msvc as a fallback (which is usually the default path)
    set(MSVC_WINSYSROOT /opt/msvc)
endif()

# rm: detect msvc version
file(GLOB _msvc_versions LIST_DIRECTORIES true ${MSVC_WINSYSROOT}/VC/Tools/MSVC/*)
list(GET _msvc_versions 0 _msvc_dir)

# rm: detect window sdk version
file(GLOB _winsdk_versions LIST_DIRECTORIES true ${MSVC_WINSYSROOT}/kits/10/Include/*)
list(GET _winsdk_versions 0 _winsdk_dir)
get_filename_component(_winsdk_ver ${_winsdk_dir} NAME)

add_compile_options(
    --target=x86_64-pc-windows-msvc
    -fms-compatibility
    -fms-extensions
    -fdelayed-template-parsing
    # rm: paths to msvc and windows sdk headers
    "-imsvc${_msvc_dir}/include"
    "-imsvc${_msvc_dir}/atlmfc/include"
    "-imsvc${MSVC_WINSYSROOT}/kits/10/Include/${_winsdk_ver}/ucrt"
    "-imsvc${MSVC_WINSYSROOT}/kits/10/Include/${_winsdk_ver}/um"
    "-imsvc${MSVC_WINSYSROOT}/kits/10/Include/${_winsdk_ver}/shared"
    "-imsvc${MSVC_WINSYSROOT}/kits/10/Include/${_winsdk_ver}/winrt"
)

add_link_options(/winsysroot:${MSVC_WINSYSROOT})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

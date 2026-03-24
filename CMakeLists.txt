cmake_minimum_required(VERSION 3.20)
project(Anaglifator)

set(CMAKE_CXX_STANDARD 17)

#static linking
set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)

#disable not used
set(wxBUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(wxBUILD_TESTS OFF CACHE BOOL "" FORCE)
set(wxBUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

# subprojects
add_subdirectory(libs/wxWidgets-3.2.8)
add_subdirectory(libs/SFML-3.0.2-sources/SFML-3.0.2/)

#executable
add_executable(anaglifator 
    MyApp.cpp 
    MainFrame.cpp      
    SFMLCanvas.cpp 
    Object3D.cpp 
    Vector4.cpp 
    Matrix.cpp 
)

# Linkowanie
target_link_libraries(anaglifator
    wx::core
    wx::base
    sfml-graphics
    sfml-window
    sfml-system
)

# Windows Subsystem (brak konsoli w tle)
if(MSVC)
    set_target_properties(anaglifator PROPERTIES
        WIN32_EXECUTABLE ON
    )
endif()
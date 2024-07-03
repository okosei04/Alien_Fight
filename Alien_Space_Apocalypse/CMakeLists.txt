# CMakeList.txt : CMake project for Alien_Fight, include source and define
# project specific logic here.
#

set(CMAKE_TOOLCHAIN_FILE "C:/Users/papak/OneDrive/Documents/GitHub/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "C:/Users/papak/OneDrive/Documents/GitHub/vcpkg/installed/x64-windows")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Allegro CONFIG REQUIRED)


# Add source to this project's executable.
add_executable (Alien_Space_Apocalypse "Alien_Space_Apocalypse.cpp" "Background.cpp"  "Game.cpp" "Player.h" "Player.cpp" "Bullet.h" "Bullet.cpp" "Villains.h" "Villains.cpp")
	
	target_link_libraries(Alien_Space_Apocalypse Allegro::allegro Allegro::allegro_ttf Allegro::allegro_font Allegro::allegro_main Allegro::allegro_image Allegro::allegro_primitives)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Alien_Space_Apocalypse PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

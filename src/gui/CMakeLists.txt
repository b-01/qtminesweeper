# set the paths for windows
IF(WIN32)
	SET(CMAKE_PREFIX_PATH 	"C:\\Qt\\Qt5.2.1\\5.2.1\\msvc2012_64_opengl"
							"C:\\Program Files (x86)\\Windows Kits\\8.0\\Lib\\win8\\um\\x64")
	SET(app_icon_resource_file "${CMAKE_SOURCE_DIR}/resources/win_appicon.rc")
ENDIF()

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)
# source-files list
SET(minesweeper_gui_srcs 	game_area/button_manager.cpp
							game_area/game_area_widget.cpp
							game_area/game_board_widget.cpp
							game_area/game_header_widget.cpp
							game_area/mine_pushbutton.cpp
							main.cpp 
							mainwindow.cpp 
							preferences_dialog.cpp)
# resource files							
SET(qt_resource_files "${CMAKE_SOURCE_DIR}/resources/resources.qrc")

# Find the QtCore library (needed for Widgets and the Qt5:WinMain target)
FIND_PACKAGE(Qt5Core)

# "Compile" the resources
QT5_ADD_RESOURCES(qt_resources ${qt_resource_files})

IF(UNIX)
	ADD_EXECUTABLE(minesweeper_gui ${qt_resources} ${minesweeper_gui_srcs})
	TARGET_LINK_LIBRARIES(minesweeper_gui minesweeper)
	
ELSEIF(WIN32)
	ADD_EXECUTABLE(minesweeper_gui WIN32 ${qt_resources} ${app_icon_resource_file} ${minesweeper_gui_srcs})
	TARGET_LINK_LIBRARIES(minesweeper_gui minesweeper Qt5::WinMain)
ENDIF()

QT5_USE_MODULES(minesweeper_gui Widgets)

SET_TARGET_PROPERTIES(minesweeper_gui
                      PROPERTIES OUTPUT_NAME qtminesweeper
                      PREFIX "")

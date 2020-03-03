SET(minesweeper_cli_srcs cli.cpp)

ADD_EXECUTABLE(minesweeper_cli ${minesweeper_cli_srcs})

TARGET_LINK_LIBRARIES(minesweeper_cli minesweeper)

#ifndef CUSTOM_MINESWEEPER_GUI_GLOBAL_CONSTANTS_HPP_
#define CUSTOM_MINESWEEPER_GUI_GLOBAL_CONSTANTS_HPP_

namespace GlobalConstants {
	namespace Settings {
		const char* const FILE_NAME = "settings.ini";

		const char* const BOARD_HEIGHT = "board/height";
		const char* const BOARD_WIDTH = "board/width";
		const char* const BOARD_MINECOUNT = "board/minecount";

		const char* const WINDOW_SIZE = "window/size";
		const char* const WINDOW_POS = "window/pos";
	}

	namespace Icons {
		const int SIZE = 15;
		const char* const FLAG = ":images/flag.png";
		const char* const FLAG_OK = ":images/flag_ok.png";
		const char* const FLAG_ERROR = ":images/flag_error.png";
		const char* const MINE = ":images/mine.png";
		const char* const SMILEY_HAPPY = ":images/happy_smiley.png";
		const char* const SMILEY_SAD = ":images/sad_smiley.png";
	}

	namespace NumberStyles {
		const char* const DEFAULT = "font-weight:bold; color: black";
		const char* const NUMBER_1 = "font-weight:bold; color: blue";
		const char* const NUMBER_2 = "font-weight:bold; color: green";
		const char* const NUMBER_3 = "font-weight:bold; color: red";
		const char* const NUMBER_4 = "font-weight:bold; color: darkblue";
		const char* const NUMBER_5 = "font-weight:bold; color: brown";
		const char* const NUMBER_6 = "font-weight:bold; color: cyan";
		const char* const NUMBER_7 = "font-weight:bold; color: black";
		const char* const NUMBER_8 = "font-weight:bold; color: gray";
	}
}

#endif /* CUSTOM_MINESWEEPER_GUI_GLOBAL_CONSTANTS_HPP_ */

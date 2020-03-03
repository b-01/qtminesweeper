#!/bin/sh

case "$1" in
	Debug)
		mkdir -p build/linux/debug
		cd build/linux/debug
		cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D _ECLIPSE_VERSION=4.3.1 ../../../src
		;;
	Release)
		mkdir -p build/linux/release
		cd build/linux/release
		cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D _ECLIPSE_VERSION=4.3.1 ../../../src
		;;
	*)
		echo "Usage: $0 Debug|Release"
		exit 1
esac

exit 0


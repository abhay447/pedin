all:
	sudo apt-get install cmake make unzip g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev	build-dep glfw3
	wget https://github.com/glfw/glfw/releases/download/3.1.2/glfw-3.1.2.zip
	unzip glfw-3.1.2.zip
	cd glfw-3.1.2 && cmake -G "Unix Makefiles" && make && sudo make install && cd ..
	rm -rf glfw-3.1.2*


all:
	sudo apt-get install cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev xorg-dev libglu1-mesa-dev libglew-dev libglm-dev
	git clone https://github.com/glfw/glfw
	cd glfw && cmake -G "Unix Makefiles" && make && sudo make install && cd ..
	rm -rf glfw


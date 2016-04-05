all:
	sudo apt-get install cmake make git g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev	
	git clone https://github.com/glfw/glfw
	cd glfw && make && sudo make install
	


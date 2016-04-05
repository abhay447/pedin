all:
	sudo apt-get install g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev	
	cd glfw-3.1.2 && make && sudo make install
	


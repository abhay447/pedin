rm -rf forceStats/*
g++ first.cpp -lglfw3 -lGL -lGLEW -lm -ldl -lXinerama -lXrandr -lXi -lXcursor -lX11 -lXxf86vm -lpthread -std=c++11
./a.out $1


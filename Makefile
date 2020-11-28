CXX = g++

SRC = ./src/

INCLUDE_PATH = D:/opencv-440/opencv-440-mingw-release/include

LIBS_PATH = D:/opencv-440/opencv-440-mingw-release/x64/mingw/bin

LIBS = -lopencv_imgproc440 -lopencv_core440 -lopencv_imgcodecs440 -lopencv_highgui440 \
	   -lopencv_calib3d440 -lopencv_xfeatures2d440 -lopencv_features2d440 -lopencv_flann440 \
	   -lopencv_videoio440

all: main.o advertisement_detector.o transformer.o video_captor.o
	$(CXX) -o AdDetector main.o advertisement_detector.o transformer.o video_captor.o -L$(LIBS_PATH) $(LIBS)

main.o: main.cpp 
	$(CXX) -c main.cpp -I$(INCLUDE_PATH)

advertisement_detector.o: $(SRC)advertisement_detector.cpp 
	$(CXX) -c $(SRC)advertisement_detector.cpp -I$(INCLUDE_PATH)

transformer.o: $(SRC)transformer.cpp
	$(CXX) -c $(SRC)transformer.cpp -I$(INCLUDE_PATH)

video_captor.o: $(SRC)video_captor.cpp
	$(CXX) -c $(SRC)video_captor.cpp -I$(INCLUDE_PATH)

clean: AdDetector.exe main.o advertisement_detector.o transformer.o 
	del AdDetector.exe main.o advertisement_detector.o transformer.o video_captor.o


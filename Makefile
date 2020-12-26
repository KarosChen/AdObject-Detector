CXX = g++

SRC = ./src/
GUI_SRC = ./gui/

INCLUDE_PATH = D:/opencv-440/opencv-440-mingw-release/include

LIBS_PATH = D:/opencv-440/opencv-440-mingw-release/x64/mingw/bin

LIBS = -lopencv_imgproc440 -lopencv_core440 -lopencv_imgcodecs440 -lopencv_highgui440 \
	   -lopencv_calib3d440 -lopencv_xfeatures2d440 -lopencv_features2d440 -lopencv_flann440 \
	   -lopencv_videoio440

all: main.o detector_gui.o model.o advertisement_detector.o transformer.o video_captor.o image_process.o thread_pool.o 
	$(CXX) -o AdDetector main.o detector_gui.o model.o advertisement_detector.o transformer.o video_captor.o image_process.o thread_pool.o -L$(LIBS_PATH) $(LIBS)
	
main.o: main.cpp 
	$(CXX) -c main.cpp -I$(INCLUDE_PATH)

detector_gui.o: $(GUI_SRC)detector_gui.cpp
	$(CXX) -c $(GUI_SRC)detector_gui.cpp -I$(INCLUDE_PATH)

model.o: $(SRC)model.cpp
	$(CXX) -c $(SRC)model.cpp -I$(INCLUDE_PATH)

advertisement_detector.o: $(SRC)advertisement_detector.cpp 
	$(CXX) -c $(SRC)advertisement_detector.cpp -I$(INCLUDE_PATH)

transformer.o: $(SRC)transformer.cpp
	$(CXX) -c $(SRC)transformer.cpp -I$(INCLUDE_PATH)

video_captor.o: $(SRC)video_captor.cpp
	$(CXX) -c $(SRC)video_captor.cpp -I$(INCLUDE_PATH)

image_process.o: $(SRC)image_process.cpp
	$(CXX) -c $(SRC)image_process.cpp -I$(INCLUDE_PATH)

thread_pool.o: $(SRC)thread_pool.cpp
	$(CXX) -c $(SRC)thread_pool.cpp

clean: AdDetector.exe main.o model.o advertisement_detector.o transformer.o video_captor.o image_process.o thread_pool.o detector_gui.o 
	del AdDetector.exe main.o model.o advertisement_detector.o transformer.o video_captor.o image_process.o thread_pool.o detector_gui.o


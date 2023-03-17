PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

BUILD_MODE = run

OBJS = Nictophobia.o \
	miocpp/iopath.o \
	miocpp/IODevice.o \
	miocpp/DirDevice.o \
	miocpp/FileReader.o \
	miocpp/PhysicalFileReader.o\
	\
	necore/Window.o \
	necore/Texture.o \
	necore/Shader.o \
	necore/Mesh.o \
	necore/Batch2D.o \
	necore/Camera.o \
	necore/input/InputProcessor.o \
	necore/input/InputBinding.o \
	necore/gl/GLWindow.o \
	necore/gl/GLTexture.o \
	necore/gl/GLShader.o \
	necore/gl/GLMesh.o

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
	EXTRA_CLEAN += Nictophobia.gcda Nictophobia.gcno $(PROJECT_ROOT)gmon.out
	EXTRA_CMDS = rm -rf Nictophobia.gcda
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

CFLAGS += -std=c++17

LDLIBS = -lGL -lglfw -lGLEW

all:	Nictophobia

Nictophobia:	$(OBJS) $(LDLIBS)
	$(CXX) $(LDFLAGS) -o $@ $^
	$(EXTRA_CMDS)

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

	
necore/gl/%.o:	$(PROJECT_ROOT)necore/gl/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<
necore/input/%.o:	$(PROJECT_ROOT)necore/input/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

necore/%.o:	$(PROJECT_ROOT)necore/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<
	
miocpp/%.o:	$(PROJECT_ROOT)miocpp/%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<


%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr Nictophobia $(OBJS) $(EXTRA_CLEAN)

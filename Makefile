CCPP=g++
CPPFLAGS=-W -Wall -fPIC -O3 -std=c++14
LDFLAGS=
DYLIB = libnumericalmethods.so
DIR_SRC = src
DIR_BUILD = build
DIR_LIB = lib
EXEC=test
SRC = $(wildcard $(DIR_SRC)/*.cpp)
OBJ = $(patsubst $(DIR_SRC)%.cpp, $(DIR_BUILD)%.o, $(SRC))

all: $(DIR_BUILD)/$(EXEC) $(DIR_LIB)/$(DYLIB)
	@mkdir -p python-package/libcpp
	cp $(DIR_LIB)/$(DYLIB) python-package/libcpp

$(DIR_BUILD)/$(EXEC): $(OBJ)
	@mkdir -p $(@D)
	$(CCPP) -o $@ $^ $(LDFLAGS)

$(DIR_LIB)/$(DYLIB): $(OBJ)
	@mkdir -p $(@D)
	$(CCPP) $(CPPFLAGS) -shared -o $@ $^ $(LDFLAGS)

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CCPP) -o $@ -c $< $(CPPFLAGS)

.PHONY: clean

clean:
	rm -rf $(DIR_BUILD)
	rm -rf $(DIR_LIB)

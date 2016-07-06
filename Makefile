#################################################################################################
# CONFIG
#################################################################################################

# likely to change
MODE:=debug#						# release, debug
CXXFLAGS:=-Wall -Wextra -Wpedantic -m32 -std=c++14
LDLIBS:=

# less likely to change
SHELL:=/bin/bash#					# bash needed for clean:read... command
HEADER_DIR:=include#				        # directory containing header files
SOURCE_DIR:=src#					# directory containing source files
BUILD_DIR:=build#					# directory containing object files
BIN_DIR:=bin#						# output


# change dirs for mode, add optimization or debugging
BIN_DIR_R:=$(BIN_DIR)/release
BIN_DIR_D:=$(BIN_DIR)/debug
BUILD_DIR_R:=$(BUILD_DIR)/release
BUILD_DIR_D:=$(BUILD_DIR)/debug

ifeq ($(MODE),release)
  BIN_DIR:=$(BIN_DIR_R)
  BUILD_DIR:=$(BUILD_DIR_R)
  CXXFLAGS:=$(CXXFLAGS) -O3
else
  ifeq ($(MODE),debug)
    BIN_DIR:=$(BIN_DIR_D)
    BUILD_DIR:=$(BUILD_DIR_D)
    CXXFLAGS:=$(CXXFLAGS) -ggdb
  else
    $(error invalid mode '$(MODE)')
  endif
endif

# revise some vars
CXXFLAGS:=$(CXXFLAGS) -I$(HEADER_DIR)

# several .o files and resources are deleted as "secondary files" unless marked precious
.PRECIOUS: $(OBJECT_DIR)/%.o
.PHONY: all clean

#################################################################################################
# TARGETS
#################################################################################################

all: test
	
test: $(BUILD_DIR)/Test.o $(BUILD_DIR)/FFGL.o $(BUILD_DIR)/Info.o $(BUILD_DIR)/Parameters.o $(BUILD_DIR)/ParameterTemplate.o $(BUILD_DIR)/PluginCore.o $(BUILD_DIR)/PluginManagerCore.o $(BUILD_DIR)/Plugin.o $(BUILD_DIR)/PluginManager.o
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/Test.o $(BUILD_DIR)/FFGL.o $(BUILD_DIR)/Info.o $(BUILD_DIR)/Parameters.o $(BUILD_DIR)/ParameterTemplate.o \
		$(BUILD_DIR)/PluginCore.o $(BUILD_DIR)/PluginManagerCore.o $(BUILD_DIR)/Plugin.o $(BUILD_DIR)/PluginManager.o -o $(BIN_DIR)/test
	
# make .o files
$(BUILD_DIR)/FFGL.o: $(SOURCE_DIR)/FFGL.cpp $(HEADER_DIR)/FFGL.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Info.o: $(SOURCE_DIR)/Info.cpp $(HEADER_DIR)/Info.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Parameters.o: $(SOURCE_DIR)/Parameters.cpp $(HEADER_DIR)/Parameters.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/ParameterTemplate.o: $(SOURCE_DIR)/ParameterTemplate.cpp $(HEADER_DIR)/ParameterTemplate.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/PluginCore.o: $(SOURCE_DIR)/PluginCore.cpp $(HEADER_DIR)/PluginCore.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/PluginManagerCore.o: $(SOURCE_DIR)/PluginManagerCore.cpp $(HEADER_DIR)/PluginManagerCore.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Plugin.o: $(SOURCE_DIR)/Plugin.cpp $(HEADER_DIR)/Plugin.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/PluginManager.o: $(SOURCE_DIR)/PluginManager.cpp $(HEADER_DIR)/PluginManager.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Test.o: $(SOURCE_DIR)/Test.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

#remove all files in binary and object directories
clean:
	@if [ $$(find bin -type f | wc -l) -gt 0 ]; \
	then { \
		echo "The following will be deleted:"; \
		echo "------------------------------"; \
		find $(BIN_DIR_R) $(BIN_DIR_D) $(BUILD_DIR_R) $(BUILD_DIR_D) -type f; \
		echo "------------------------------"; \
		read -p "Continue (y/n)? " -n 1 -r CONTINUE; \
		echo; \
	}; \
	else echo "No files to delete."; \
	fi; \
	\
	if [[ $$CONTINUE =~ ^[Yy]$$ ]]; \
	then find $(BIN_DIR_R) $(BIN_DIR_D) $(BUILD_DIR_R) $(BUILD_DIR_D) -type f -delete; \
	else echo "Aborted"; \
	fi;

#initialize folder structure
init:
	@mkdir -p $(BIN_DIR_R) $(BIN_DIR_D) $(HEADER_DIR) \
		$(SOURCE_DIR) $(BUILD_DIR_R) $(BUILD_DIR_D)


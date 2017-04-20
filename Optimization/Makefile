# This should point to place where you unpacked or cloned Ceres.
INCLUDES := -I/usr/local/include

CERES_LIBRARY := -lceres
CERES_LIBRARY_PATH := -L$/usr/local/lib
CERES_LIBRARY_DEPENDENCIES = -lgflags -lglog

# If Ceres was built with Suitesparse:
CERES_LIBRARY_DEPENDENCIES += -lblas -lcamd -lamd -lccolamd -lcolamd -lcholmod
# If Ceres was built with CXSparse:
CERES_LIBRARY_DEPENDENCIES += -lcxsparse
# If Ceres was built with OpenMP:
CERES_LIBRARY_DEPENDENCIES += -fopenmp -lpthread -lgomp -lm

# The set of object files for your application.
APPLICATION_OBJS := ceres_solver_tutorial.o

all: ceres_solver_tutorial

ceres_solver_tutorial: $(APPLICATION_OBJS)
	g++ $(APPLICATION_OBJS) \
	$(CERES_LIBRARY_PATH) \
	$(CERES_LIBRARY) \
	$(CERES_LIBRARY_DEPENDENCIES) \
	-o ceres_solver_tutorial

# Disabling debug asserts via -DNDEBUG helps make Eigen faster, at the cost of
# not getting handy assert failures when there are issues in your code.
CFLAGS := -O2 -DNDEBUG

# If you have files ending in .cpp instead of .cc, fix the next line
# appropriately.
%.o: %.cxx $(DEPS)
	g++ -c -o $@ $< $(CFLAGS) $(INCLUDES)

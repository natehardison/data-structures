#
# A simple makefile for managing build of project composed of C source files.
#
# Nate Hardison, pulled from:
# Julie Zelenski, for CS107, Sept 2009
#

# Use clang instead of gcc
CC = clang

# The CFLAGS variable sets compile flags for gcc:
#  -g          compile with debug information
#  -Wall       give all diagnostic warnings
#  -pedantic   require compliance with ANSI standard
#  -O0         do not optimize generated code
#  -std=gnu99  use the Gnu C99 standard language definition
CFLAGS = -g -Wall -pedantic -O0 -std=gnu99

# The LDFLAGS variable sets flags for linker
# Currently we don't need to link with anything
LDFLAGS = 

# In this section, you list the files that are part of the project.
# If you add/change names of header/source files, here is where you
# edit the Makefile.
HEADERS = node.h sll.h
SOURCES = node.c sll.c sll-test.c
LIBRARIES = -L. -lsll -lnode
TARGETS =  sll-test
LIB_TARGETS = 

# The first target defined in the makefile is the one
# used when make is invoked with no argument. The default
# target makes all test programs
default: $(TARGETS)

# $@ is a substitution for the name of the target (sll-test)
# $^ is a substitution for all of the dependencies (sll.o and sll-test.o)
sll-test : node.o sll.o sll-test.o
	$(CC) $(CFLAGS) -o $@  $^ $(LDFLAGS)

# In make's default rules, a .o automatically depends on its .c file
# (so editing the .c will cause recompilation into its .o file).
# The line below creates additional dependencies, most notably that it
# will cause the .c to reocmpiled if any included .h file changes.
Makefile.dependencies:: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -MM $(SOURCES) > Makefile.dependencies

-include Makefile.dependencies

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" that is used to remove all compiled object files.
.PHONY: clean

clean:
	@rm -f $(TARGETS) $(LIB_TARGETS) *.o core Makefile.dependencies


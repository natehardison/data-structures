#
# A simple makefile for managing build of project composed of C source files.
#
# Nate Hardison, pulled from:
# Julie Zelenski, for CS107, Sept 2009
#

# It is likely that default C compiler is already gcc, but explicitly
# set, just to be sure
CC = gcc

# The CFLAGS variable sets compile flags for gcc:
#  -g          compile with debug information
#  -Wall       give all diagnostic warnings
#  -Werror     turn warnings into build errors
#  -pedantic   require compliance with ANSI standard
#  -O0         do not optimize generated code
#  -std=gnu99  use the Gnu C99 standard language definition
#  -m32        emit code for IA32 architecture
CFLAGS = -g -Wall -Werror -pedantic -O0 -std=gnu99

# The LDFLAGS variable sets flags for linker
LDFLAGS = 

# In this section, you list the files that are part of the project.
# If you add/change names of header/source files, here is where you
# edit the Makefile.
HEADERS = stack.h
SOURCES = stack-array.c stack-list.c stack-test.c
LIBRARIES = -L. -lstack
TARGETS =  stack-array-test stack-list-test
LIB_TARGETS = 

# The first target defined in the makefile is the one
# used when make is invoked with no argument. The default
# target makes all test programs
default: $(TARGETS)

stack-array-test : stack-array.o stack-test.o
	$(CC) $(CFLAGS) -o $@  $^ $(LDFLAGS)

stack-list-test : stack-list.o stack-test.o
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

# Include *.dSYM for Mac OSX
clean:
	@rm -rf $(TARGETS) $(LIB_TARGETS) *.o core Makefile.dependencies *.vgcore *.dSYM


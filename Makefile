#
# CS 3377.502
# Jia Hsing
# Jwh150030
#

CXX = g++
CXXFLAGS = -Wall -g -Wno-write-strings 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = cdkexample

OBJS = cdkexample.o

PROJECTNAME = CS3377.502.Program6

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:
	@make clean
	@mkdir -p ~\backups; chmod 700 ~\backups
	@$(eval CURDIRNAME := $(shell basename 'pwd'))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME) -$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

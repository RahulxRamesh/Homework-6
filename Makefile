#Rahul Ramesh rxr162130@utdallas.edu 3377.002
CXX = g++
CXXFLAGS = -Wall -g
CPPFLAGS = -I /scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -lcdk -lcurses
PROJECTNAME = CS3377.HW6
EXECFILE = hw6
OBJS = cdk.o

insta: clean all

all: $(EXECFILE)

clean:
	@rm -f $(OBJS) $(EXECFILE) *.o *~ \#*
	@echo Clean successful!

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
	@echo Compiled sucessfully!

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date+'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup File to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CUDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

TARGET		= list_sample
SRCS		= list_sample.c

#---------------------------------------------------------------------
# Source liraries
DIR_LIB         = ./

# --------------------------------------------------------------------
# Directory included
OBJS		= $(SRCS:.c=.o)

CFLAGS		= $(INCLUDEDIRS) -o -W -Wall -O2
LDFLAGS		= $(LIVDIRS)
LIBS		= -lm    

#---------------------------------------------------------------------
#
CC		= gcc
CP		= cp
MV		= mv

#--------------------------------------------------------------------
#
all : $(TARGET)
	rm -f $(OBJS)

$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LIBS) 

%.o:%.c $(CONFIG_FILE)
	@echo "Compiling $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o
	rm -f $(OBJS)
	rm -f $(TARGET)

distclean: clean
	rm -rf .depend	

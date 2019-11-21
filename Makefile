###########################################
# Simple Makefile sms_service
###########################################

all: sms_service

OUT      ?= sms_service
CC       ?= gcc
CFLAGS   ?= 

CXX      ?= g++
CXXFLAGS ?= -Wall 

COBJS     = 
CPPOBJS   = main.o send_msg.o  send_to.o read_config.o recent_file.o database.o
OBJS      = $(COBJS) $(CPPOBJS)
LIBS      = -lpthread -l sqlite3
INCLUDES ?= -g -I. -Iplog 

sms_service: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $(OUT)
	
$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp ./include/header.h  ./include/declaration.h ./include/global.h
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJS) $(OUT)

.PHONY: clean
   

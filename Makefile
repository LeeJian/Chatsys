#
# Makefile for ALL Workspace
#
include ./make.h

SERVER_TARGET = server
CLIENT_TARGET = client

TARGETS	 =  $(SERVER_TARGET) $(CLIENT_TARGET)

COMMON_OBJS = 
SERVER_OBJS = server.o $(COMMON_OBJS)
CLIENT_OBJS = client.o $(COMMON_OBJS)

OBJS     =  $(COMMON_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS) 

all: $(LIBS) $(TARGETS)

$(SERVER_TARGET):$(SERVER_OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(SERVER_TARGET) $(SERVER_OBJS) $(LIBS) $(CC_PTHREAD_FLAGS)

$(CLIENT_TARGET):$(CLIENT_OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(CLIENT_TARGET) $(CLIENT_OBJS) $(LIBS) $(CC_PTHREAD_FLAGS)
	
.c.o:
	$(CC) $(CC_FLAGS)  $(COMMON_INCLUDE_DIRS)  $<

clean:
	make -w -C $(CHATSYS_PROTOCOL_CHATSYS_DIR) -f Makefile clean
	make -w -C $(CHATSYS_PROTOCOL_OS_WRAPER_DIR) -f Makefile clean
	make -w -C $(CHATSYS_PROTOCOL_TOOL_DIR) -f Makefile clean
	make -w -C $(CHATSYS_PROTOCOL_CLIENTM_DIR) -f Makefile clean
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGETS)
	$(RM) $(RM_FLAGS) *.lib *.bak

# Make for ChatSys Protocol Module
# Output CHATSYS_LIB - chatsys.lib
$(CHATSYS_LIB):
    #  Make for OS wrapper Module
	make -w -C $(CHATSYS_PROTOCOL_OS_WRAPER_DIR) -f Makefile	all	
    #  Make for tools Module
	make -w -C $(CHATSYS_PROTOCOL_TOOL_DIR) -f Makefile	all
    #  Make for clientm Module
	make -w -C $(CHATSYS_PROTOCOL_CLIENTM_DIR) -f Makefile	all
    # Make for ChatSys Protocol Module
	make -w -C $(CHATSYS_PROTOCOL_CHATSYS_DIR) -f Makefile	all
	$(CP) $(CHATSYS_PROTOCOL_CHATSYS_DIR)/$(CHATSYS_LIB) ./


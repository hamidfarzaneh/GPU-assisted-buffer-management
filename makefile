CC  =   gcc
CFLAGS  =   -Wall
OBJFILES    =   Main.o cache_manager.o  binary_tree.o   LRU.o   page_id_node.o  
TARGET  =  gram 
all:    $(TARGET)
$(TARGET):  $(OBJFILES)
	$(CC)	$(CFLAGS)	-o	$(TARGET)	$(OBJFILES)
clean:
	rm  -f  $(OBJFILES) $(TARGET)  

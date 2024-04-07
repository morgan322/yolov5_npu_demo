TARGET := demo
APPROOT ?= ./un_exist_path
TOOLPATH ?= ./un_exist_path

all:clean
	$(CROSS)g++ $(wildcard *.cpp) $(CFLAGS) -o $(TARGET) 

	@cp $(TARGET) 	$(APPROOT)
	@cp ./*.lic 	$(APPROOT)
	@cp ./frpc.ini   $(APPROOT)
	@cp ./frpc   $(APPROOT)
	@cp ./start.sh  $(APPROOT)
	@cp ./install.sh  $(APPROOT)
	
	@cp ./json/$(plat)/sample.json $(TOOLPATH)
	@cd $(TOOLPATH)/; ./ezyBuilder build sample.json
clean:
	@rm -f ./$(TARGET)
	@rm -rf $(APPROOT)/*
	@rm -rf $(TOOLPATH)/*.json	
.PHONY:
	clean

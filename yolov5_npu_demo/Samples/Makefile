plat ?= unknow
app  ?= all
CROSS := unknow
SUBMAKE := unknow
SUBCLEAN := unknow
PWD := $(shell pwd)
TOOLPATH := $(PWD)/../Tools
APPROOT := $(TOOLPATH)/app_root
KEYPATH := $(PWD)/../Keys

ifeq ($(app), all)
SUBMAKE = $(shell find ./ -maxdepth 1 -name 'DhopSmp*' | grep -v '^.$$' | awk -F '/' '{print $$NF}')
else
SUBMAKE = $(app)
endif
DATE = $(shell date +%Y%m%d)
SUBCLEAN = $(addprefix _clean_,$(SUBMAKE) )

ifeq ($(plat),Volt)
CROSS := arm-himix200v002-linux-
else ifeq ($(plat),Nobel)
CROSS := arm-himix200-linux-v2-
else ifeq ($(plat),Fafnir)
CROSS := aarch64-himix100v630r3-linux-
else ifeq ($(plat),Faraday)
CROSS := aarch64-himix210-linux-sd3403v100-v1-
endif

ifeq ($(CROSS), unknow)
help:
endif

CFLAGS := -I$(PWD)/../Include/DhopSdk
#CFLAGS := -I$(PWD)/../Samples/HYAI_HuoYanAIDemo
CFLAGS += -L$(PWD)/../Libs
CFLAGS += -L$(PWD)/../Libs/ThirdParty_Stub

ifeq ($(plat),Faraday)
CFLAGS += -lmau -live -lsecurec -lVoiceEngine -lupvqe -ldnvqe -lascendcl -lge_executor -lgraph -lge_common
CFLAGS += -lruntime -lmmpa -ldrvdevdrv -lslog -ldrv_dfx -lc_sec -laicpu_scheduler -ladump -laicpu_processer -laicpu_prof
CFLAGS += -ldsp -lmsprof -lmsprofiler -lalog -lerror_manager -lregister -lascend_protobuf
CFLAGS += -litop_sdk -lmpi -lrt -lpthread -ldl -lm -lstdc++ -Wl,--gc-sections
else
ifeq ($(app),HYAI_HuoYanFrp)
CFLAGS += -litop_sdk -live -lmpi -lVoiceEngine -lupvqe -lsecurec -ldnvqe  -lrt  -lpthread -ldl  -Wl,--gc-sections
else
CFLAGS += -litop_sdk -live -lmpi -lVoiceEngine -lupvqe -lsecurec -ldnvqe -lcurl -lmp4v2 -lssl -lrabbitmq -lcrypto -lrt  -lpthread -ldl -Wl,--gc-sections
endif
endif

export CROSS
export CFLAGS
export TOOLPATH
export plat
export APPROOT
all: clean pre $(SUBMAKE)	
	@mv $(TOOLPATH)/*.bin ./App/
pre:
	mkdir -p ./App/
	mkdir -p $(APPROOT)
	chmod +x $(TOOLPATH)/ezyBuilder
	cp $(KEYPATH)/private.pem $(TOOLPATH)
ECHO:
	@pwd
	@echo $(SUBMAKE)
	
NONE   := \033[m"
RED    := "\033[0;32;31m
GREEN  := "\033[0;32;32m
BLUE   := "\033[0;32;34m
BROWN  := "\033[0;33m
YELLOW := "\033[1;33m
WHITE  := "\033[1;37m

help:
	@echo "------------------------------------------------------------------------------------------"
	@echo -e $(YELLOW)Format:$(NONE)
	@echo -e $(WHITE)    make [plat=xx] [app=xx]$(NONE)
	@echo -e $(BROWN)plat:$(NONE)
	@echo           "    Volt Nobel Fafnir Faraday"
	@echo -e $(BROWN)app:$(NONE)
	@echo           "    all(default) dirname"
	@echo -e $(GREEN)example:$(NONE)
	@echo           "    make plat=Nobel"
	@echo           "    make plat=Nobel app=all"
	@echo           "    make plat=Nobel app=DhopSmp_alarm"
	@echo "------------------------------------------------------------------------------------------"

$(SUBMAKE): ECHO
	@echo -e "\033[32m==================================[$@]=================================\033[0m"
	@make -C $@


$(SUBCLEAN):
	@make -C $(patsubst _clean_%,%,$@) clean
	
clean:$(SUBCLEAN)	
	@rm -rf ./App/
	@rm -rf $(APPROOT)
	@find $(TOOLPATH)/*  ! \( -name "ezyBuilder" -o -name "README.md" \) | xargs rm -rf 		
		
.PHONY:
	ECHO help clean $(SUBMAKE) $(SUBCLEAN)
	




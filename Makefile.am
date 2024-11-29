bin_PROGRAMS = trig_program
trig_program_SOURCES = main.cpp TrigFunction.cpp TrigFunction.h

SUBDIR = tests

CTRLF_DIR = $(CURDIR)/deb/DEBIAN
CTRLF_NAME = $(CTRLF_DIR)/control

.PHONY: deb debug
deb:
	mkdir -p $(CTRLF_DIR)
	echo Package: "trigprogram" > $(CTRLF_NAME)
	echo Version: $(VERSION) >> $(CTRLF_NAME) 
	echo Architecture: all >> $(CTRLF_NAME)
	echo Maintainer: $(PACKAGE_BUGREPORT) >> $(CTRLF_NAME)
	echo -n "Description:" >> $(CTRLF_NAME)
	cat trig_program.1 >> $(CTRLF_NAME)
	make DESTDIR=$(CURDIR)/deb install


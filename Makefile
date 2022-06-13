all:
	-mkdir build
	cd build && cmake .. && make

build: all
	@echo "Building Done"

run: build
	./build/qgo-clipboard-client

# Only if the DPKG command is supported
DPKG=$(which dpkg)
ifneq (${DPKG},"")
package: build
	cd build && make package

install-deb: package
	sudo dpkg -i ./build/qgo-clipboard-client*.deb
endif

# In vscode internal terminal environment
ifeq ("vscode", "${TERM_PROGRAM}")
edit-config:
	code backend/config.h
endif
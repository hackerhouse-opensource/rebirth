CLANG := $(shell xcrun --sdk iphoneos --find clang)
SYSROOT := $(shell xcrun --sdk iphoneos --show-sdk-path)

all: helloworld 

helloworld: helloworld.c
	$(CLANG) -isysroot $(SYSROOT) -arch arm64 helloworld.c -o helloworld
	./jtool --inplace --sign --ent entitlements.xml helloworld

install:
	cp helloworld ../../binpack/bin

clean:
	rm -rf helloworld

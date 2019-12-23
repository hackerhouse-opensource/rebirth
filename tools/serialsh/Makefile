CLANG := $(shell xcrun --sdk iphoneos --find clang)
SYSROOT := $(shell xcrun --sdk iphoneos --show-sdk-path)

all: serialsh

serialsh: serialsh.c
	$(CLANG) -isysroot $(SYSROOT) -arch arm64 serialsh.c -o serialsh
	./jtool --inplace --sign --ent entitlements.xml serialsh

install:
	cp serialsh ../../binpack/sbin

clean:
	rm -rf serialsh

#!/bin/sh
make clean
make distclean
export CC=`xcrun --sdk iphoneos --find clang`
export CFLAGS="-arch arm64 -miphoneos-version-min=11.0 -isysroot `xcrun --sdk iphoneos --show-sdk-path`"
export LIBS="-arch arm64 -miphoneos-version-min=11.0 -isysroot `xcrun --sdk iphoneos --show-sdk-path`"
export LDFLAGS="-arch arm64 -miphoneos-version-min=11.0 -isysroot `xcrun --sdk iphoneos --show-sdk-path`"
./configure --host=arm-apple-darwin --disable-harden --disable-syslog --disable-lastlog --disable-utmp --disable-utmpx --disable-wtmp --disable-wtmpx --disable-zlib --disable-loginfunc 
make
../jtool/jtool --sign --inplace --ent ../netcat-0.7.1/entitlements.xml dropbear
../jtool/jtool --sign --inplace --ent ../helloworld/entitlements.xml dbclient 
../jtool/jtool --sign --inplace --ent ../helloworld/entitlements.xml dropbearkey 
../jtool/jtool --sign --inplace --ent ../helloworld/entitlements.xml dropbearconvert
cp dropbear ../../binpack/usr/local/bin
cp dbclient ../../binpack/usr/local/bin
cp dropbearkey ../../binpack/usr/local/bin
cp dropbearconvert ../../binpack/usr/local/bin

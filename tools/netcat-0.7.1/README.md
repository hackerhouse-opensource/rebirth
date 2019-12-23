To compile netcat use the following arguements, then make and use jtool to self-sign

CC=`xcrun --sdk iphoneos --find clang` CFLAGS="-arch arm64 -isysroot `xcrun --sdk iphoneos --show-sdk-path`" ./configure --host=arm-apple-darwin

../jtool/jtool --inplace --sign --ent entitlements.xml src/netcat

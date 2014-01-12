rm -rf libraries
mkdir libraries
mkdir libraries/Ucglib
mkdir libraries/Ucglib/examples
mkdir libraries/Ucglib/examples/HelloWorld
mkdir libraries/Ucglib/utility
cp ../../../ChangeLog ./libraries/Ucglib/.
cp ../../../license.txt ./libraries/Ucglib/.
cp INSTALL.TXT ./libraries/Ucglib/.
cp ../../../cppsrc/*.cpp ./libraries/Ucglib/.
cp ../../../cppsrc/*.h ./libraries/Ucglib/.
sed -i 's|ucg.h|utility/ucg.h|g' ./libraries/Ucglib/Ucglib.h
cp ../../../csrc/*.c ./libraries/Ucglib/utility/.
cp ../../../csrc/*.h ./libraries/Ucglib/utility/.
cp ../../../sys/arduino/HelloWorld/*.ino ./libraries/Ucglib/examples/HelloWorld/.


chmod -R og=u libraries
cd libraries 
rm ../u8glib_arduino_`../../print_release.sh`.zip
zip -r ../u8glib_arduino_`../../print_release.sh`.zip *
cd ..


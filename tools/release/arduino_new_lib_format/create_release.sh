mkdir ../../../../Ucglib_Arduino/examples/HelloWorld
mkdir ../../../../Ucglib_Arduino/examples/FPS
mkdir ../../../../Ucglib_Arduino/examples/Box3D
mkdir ../../../../Ucglib_Arduino/examples/UcgLogo
mkdir ../../../../Ucglib_Arduino/examples/Scale
mkdir ../../../../Ucglib_Arduino/examples/GraphicsTest
mkdir ../../../../Ucglib_Arduino/extra
mkdir ../../../../Ucglib_Arduino/src
mkdir ../../../../Ucglib_Arduino/src/clib
cp ../../../ChangeLog ../../../../Ucglib_Arduino/extra/.
# cp ../../../license.txt ../../../../Ucglib_Arduino/extra/.
cp INSTALL.TXT ../../../../Ucglib_Arduino/extra/.
cp library.properties ../../../../Ucglib_Arduino/.
cp ../../../cppsrc/*.cpp ../../../../Ucglib_Arduino/src/.
cp ../../../cppsrc/*.h ../../../../Ucglib_Arduino/src/.
sed -i 's|ucg.h|utility/ucg.h|g' ../../../../Ucglib_Arduino/src/Ucglib.h
cp ../../../csrc/*.c ../../../../Ucglib_Arduino/src/clib/.
cp ../../../csrc/*.h ../../../../Ucglib_Arduino/src/clib/.
cp ../../../sys/arduino/HelloWorld/*.ino ../../../../Ucglib_Arduino/examples/HelloWorld/.
cp ../../../sys/arduino/FPS/*.ino ../../../../Ucglib_Arduino/examples/FPS/.
cp ../../../sys/arduino/Box3D/*.ino ../../../../Ucglib_Arduino/examples/Box3D/.
cp ../../../sys/arduino/UcgLogo/*.ino ../../../../Ucglib_Arduino/examples/UcgLogo/.
cp ../../../sys/arduino/Scale/*.ino ../../../../Ucglib_Arduino/examples/Scale/.
cp ../../../sys/arduino/GraphicsTest/*.ino ../../../../Ucglib_Arduino/examples/GraphicsTest/.



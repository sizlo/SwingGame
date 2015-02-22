SwingGame
=========

A 2D game with grappling hooks made for my third year project.

Follow development progress at http://timbrier.com/blogs/swinggame/


## Building and Running
### Mac
1. Download [SFML 2.2](http://sfml-dev.org/download/sfml/2.2/). Get the clang version for osx.
2. Unpack SFML and run install.sh from the root of the unpacked folder.
3. Open the xcode project (xcode versions other than 5 not checked for support).
4. Hit run.

### Windows
1. Download [SFML 2.2](http://sfml-dev.org/download/sfml/2.2/). Get the Visual C++ 11 (2012) - 64 bits version.
2. Unpack SFML anywhere you like
3. Open the visual studio solution
4. Update the following properties for your location of SFML
	- The path to the SFML headers (<sfml-install-path>/include) in C/C++ » General » Additional Include Directories
	- The path to the SFML libraries (<sfml-install-path>/lib) in Linker » General » Additional Library Directories
5. Make sure the platform configuration is set to x64
6. Hit build

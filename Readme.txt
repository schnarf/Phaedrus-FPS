In addition to the libraries in the lib/ directory, Phaedrus FPS depends on the following other libraries:
	- Boost
	- SDL

On windows, you'll have to add these to your path.

I've chosen to statically link a few libraries, which are in the lib directory. It would be possible to set up the build system to link them dynamically and not distribute them with their source. If anybody out there reads this, I'm open to suggestions, this is just what's been easiest for me to maintain.
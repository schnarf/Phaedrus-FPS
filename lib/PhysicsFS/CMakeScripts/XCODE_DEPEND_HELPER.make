# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to, avoiding a bug in XCode 1.5
all.Debug: \
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/libphysfs.dylib\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/test_physfs\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/wxtest_physfs

all.Release: \
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/libphysfs.dylib\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/test_physfs\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/wxtest_physfs

all.MinSizeRel: \
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/libphysfs.dylib\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/test_physfs\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/wxtest_physfs

all.RelWithDebInfo: \
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/libphysfs.dylib\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/test_physfs\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/wxtest_physfs

# For each target create a dummy rule so the target does not have to exist
/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/libphysfs.dylib:
/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/libphysfs.dylib:
/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/libphysfs.dylib:
/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/libphysfs.dylib:


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/libphysfs.dylib:
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/libphysfs.dylib


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/test_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/test_physfs


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/wxtest_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Debug/wxtest_physfs


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/libphysfs.dylib:
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/libphysfs.dylib


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/test_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/test_physfs


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/wxtest_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/Release/wxtest_physfs


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/libphysfs.dylib:
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/libphysfs.dylib


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/test_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/test_physfs


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/wxtest_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/MinSizeRel/wxtest_physfs


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/libphysfs.dylib:
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/libphysfs.dylib


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/test_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/test_physfs


/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/wxtest_physfs:\
	/Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/libphysfs.dylib
	/bin/rm -f /Users/aaron/Documents/Code/GameEngine/lib/PhysicsFS/RelWithDebInfo/wxtest_physfs



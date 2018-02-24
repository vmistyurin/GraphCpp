wget --quiet $CMAKE_URL
mkdir -p $CMAKE_DIR
tar --strip-components=1 -xzf $CMAKE_TAR -C $CMAKE_DIR

if [ "$TARGET_CPU" != "x86" ]; then
	sudo apt-get -qq update

else
	sudo dpkg --add-architecture i386
	sudo apt-get -qq update

	sudo apt-get install -y g++-multilib
fi

exit 0
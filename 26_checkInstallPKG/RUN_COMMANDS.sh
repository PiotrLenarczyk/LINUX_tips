#!/bin/bash
#https://stackoverflow.com/questions/1298066/check-if-a-package-is-installed-and-then-install-it-if-its-not
CHECK_INSTALL()
{	PKG_NAME=$1; PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $PKG_NAME|grep "install ok installed")
	if [ "" == "$PKG_OK" ]; then
		echo "No [$PKG_NAME]. Setting up [$PKG_NAME]."
		sudo apt-get --force-yes --yes install $PKG_NAME
	else
		echo "[$PKG_NAME] : installed"
	fi
};

CHECK_INSTALL "gcc" 
CHECK_INSTALL "vim" 

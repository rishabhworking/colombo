
Debian
====================
This directory contains files used to package colombod/colombo-qt
for Debian-based Linux systems. If you compile colombod/colombo-qt yourself, there are some useful files here.

## colombo: URI support ##


colombo-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install colombo-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your colombo-qt binary to `/usr/bin`
and the `../../share/pixmaps/colombo128.png` to `/usr/share/pixmaps`

colombo-qt.protocol (KDE)


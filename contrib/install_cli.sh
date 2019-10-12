 #!/usr/bin/env bash

 # Execute this file to install the colombo cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Colombo-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Colombo-Qt.app/Contents/MacOS/colombod /usr/local/bin/colombod
 sudo ln -s ${LOCATION}/Colombo-Qt.app/Contents/MacOS/colombo-cli /usr/local/bin/colombo-cli

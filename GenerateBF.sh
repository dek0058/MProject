function pause(){
   read -p "$*"
}


MProjectBackend="./MProjectBackend/"

if [ -d "$MProjectBackend" ]; then
    pause 'MProjectBackend File already exist. (any key press plz...)'
else
    git clone https://github.com/dek0058/MProjectBackend.git
fi

MProjectFrontend="./MProjectFrontend/"

if [ -d "$MProjectFrontend" ]; then
    pause 'MProjectFrontend File already exist. (any key press plz...)'
else
    git clone https://github.com/dek0058/MProjectFrontend.git
fi

function pause(){
   read -p "$*"
}


MProjectClient="./MProjectClient/"

if [ -d "$MProjectClient" ]; then
    pause 'File already exist. (any key press plz...)'
    exit
else
    git clone https://github.com/dek0058/MProjectClient.git
fi

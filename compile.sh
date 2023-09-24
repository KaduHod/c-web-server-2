#!/bin/bash

DIR=$(pwd)

allCFiles(){
    echo find $DIR -type f \( -name "*.c" -o -name "*.h" \)
}

formatListOfCFiles(){
    echo $(find $DIR -type f \( -name "*.c" -o -name "*.h" \)| xargs echo)
}

formatListOfDirs(){
	echo $(find "$(pwd)" -mindepth 1 -type d \( ! -name ".git" -a ! -name "dist" \) | grep -vE '/\.git$|/\.git/' | xargs -I {} echo "-I{}")
}


log(){
    local msg="$1"
    echo "[$(date -u '+%Y-%m-%d %H:%M:%S')] > $msg"
}

build(){
    files=$(formatListOfCFiles)
    dirs=$(formatListOfDirs)
    comando=$(echo gcc -Werror $files $dirs -o dist/main)
    log "comando de compilação: $comando"
    eval "$comando"
}

inotifywait -m -e create,delete,modify -r --format '%:e %w%f' "$DIR" |
while read -r event file
do
    if [[ "$file" == "$DIR/dist/"* ]]; then
        continue
    fi
    if [[ "$file" == "$DIR/.git/"* ]]; then
        continue
    fi
    if [[ "$file" == "$DIR/compile.sh"*i ]]; then 
	continue
    fi

    log "Evento $event :: Arquivo: $file "
    build
done

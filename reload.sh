#!/bin/bash

DIR=$(pwd)

allCFiles(){
    echo find $DIR -type f \( -name "*.c" -o -name "*.h" \)
}

formatListOfCFiles(){
    echo $(find $DIR -type f \( -name "*.c" -o -name "*.h" \)| xargs echo)
}

build(){
    files=$(formatListOfCFiles)
    #echo gcc -Werror $files -o dist/main
    gcc -Werror $files -o dist/main 
}

log(){
    local msg="$1"
    echo "[$(date -u '+%Y-%m-%d %H:%M:%S')] > $msg"
    echo ""
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
    log "Arquivo: $file"
    log "Evento: $event"
    build
done





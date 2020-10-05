#!/bin/bash

reverse() {
  if ! [ -f $1 ]; then
    error FileNotFoundError "$1."
  elif ! [ -r $1 ]; then
    error PermissionDeniedError "$1."
  elif [[ $2 = '' ]]; then
    error CountOfArgumentsError
  elif ! [[ -f $2 ]] && [[ -d $2 ]]; then
    error DirFoundError
  elif [ -f $2 ] && ! [ -w $2 ]; then
    error PermissionDeniedError "$2."
  elif ! [ -f $2 ] && ! [ -w "$(dirname $2)" ]; then
    error DirPermissionDeniedError
  else
    fileValue=$(tac "$1")
    > $2
    IFS=$'\n'
    for entry in $fileValue; do
      for value in $entry; do
        echo "$value" | awk '{ for (i=NF; i>1; i--) printf("%s ",$i); print $1; }' >> "$2"
      done
    done
  fi
}

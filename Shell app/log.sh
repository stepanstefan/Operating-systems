#!/bin/bash

log() {
  if ! [ -f "$1" ]; then
    error FileNotFoundError $1
  elif ! [ -r "$1" ];then
    error PermissionDeniedError $1
  else
    while IFS= read -r line; do
      if  [[ (("$line" == *"(WW)"*)) && ! (("$line" == *"(WW) warning, (EE) error, (NI) not implemented, (??) unknown"*))  ]]; then
        echo -e "${line//"(WW)"/"\e[33mWarning:\e[0m"}"
      fi
    done < "$1"
    while IFS= read -r line; do
      if  [[ (("$line" == *"(II)"*)) && ! (("$line" == *"(++) from command line, (!!) notice, (II) informational,"*))  ]]; then
        echo -e "${line//"(II)"/"\e[94mInformation:\e[0m"}"
      fi
    done < "$1"
  fi
}

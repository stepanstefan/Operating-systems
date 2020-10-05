#!/bin/bash

isInteractive=false

error() {
  message="${1}Message"
  echo -e "\033[31mError: ${!message} $2\033[0m" >&2
  if ! [[ "$isInteractive" == true ]]; then
    exit ${!1}
  fi
}

includeFile() {
  if ! [[ -r "$1" ]]; then
    error ScriptAvailableError
  else
    . "./$1"
  fi
}

includeFile "constants.sh"

case $1 in
  "calc")
    includeFile "$1.sh"
    if ! [[ "$#" -eq 4 ]]; then
      error CountOfArgumentsError
    fi
    calc "$2" "$3" "$4"
    ;;

  "search")
    includeFile "$1.sh"
    if ! [[ "$#" -eq 3 ]]; then
      error CountOfArgumentsError
    fi
    search "$2" "$3"
    ;;

  "reverse")
    includeFile "$1.sh"
    if ! [[ "$#" -eq 3 ]]; then
      error CountOfArgumentsError
    fi
    reverse "$2" "$3"
    ;;

  "strlen")
    includeFile "$1.sh"
    strlen "$@"
    ;;

  "log")
    includeFile "$1.sh"
    if ! [[ "$#" -eq 1 ]]; then
      error CountOfArgumentsError
    fi
    log "/var/log/anaconda/X.log"
    ;;

  "exit")
    includeFile "$1.sh"
    if ! [[ "$#" -eq 2 ]]; then
      error CountOfArgumentsError
    fi
    exit "$2"
    ;;

  "interactive")
    isInteractive=true
    includeFile "$1.sh"
    interactive
    ;;

  *)
    includeFile "help.sh"
    help
    ;;
esac

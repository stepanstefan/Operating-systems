#!/bin/bash

search() {
  if ! [ -d "$1" ]; then
    error FileNotFoundError
  elif ! [ -r "$1" ]; then
    error PermissionDeniedError "input."
  else
    grep -r -s "$2" "$1"
  fi
}

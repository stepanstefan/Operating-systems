#!/bin/bash

strlen() {
  if [[ $isInteractive == true ]] && [[ "$#" -eq 1 ]]; then
    echo "${#1}"
  elif ! [[ "$#" -eq 2 ]]; then
    error CountOfArgumentsError
  else
    echo "${#2}"
  fi
}

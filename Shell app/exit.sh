#!/bin/bash

exit() {
  re='^-?[0-9]+$'
  if [[ $1 =~ $re ]]; then
    command exit $1
  elif ! [[ $1 ]]; then
    command exit 0
  else
    error TypeOfArgumentsError
  fi
}

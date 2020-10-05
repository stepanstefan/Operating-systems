#!/bin/bash

calc() {
  regexForNumber='^[-+]?[0-9]+$'
  regexForCommands='mul|sum|sub|div'
  regexForZero='^[+-]?0+$'

  if ! [[ $1 =~ $regexForCommands ]]; then
    error ActionError
  elif [[ $1 == "div" && $3 =~ $regexForZero ]]; then
    error DivisionByZeroError
  elif ! [[ $2 =~ $regexForNumber && $3 =~ $regexForNumber ]]; then
    error TypeOfArgumentsError
  else
    echo "Результат:"
    case $1 in
      "sum")
        echo $(($2 + $3))
        ;;
      "sub")
        echo $(($2 - $3))
        ;;
      "mul")
        echo $(($2 * $3))
        ;;
      "div")
        echo "$2 / $3"  | bc -l
        ;;
    esac
  fi
}

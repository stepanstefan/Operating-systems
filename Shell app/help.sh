#!/bin/bash

help(){

  echo "
  Доступные действия:
  calc | sum/div/mul/sub | first number | second number
  search | directory | regular expressions
  reverse | input directory | output directory
  strlen | string
  log - var/log/anaconda/X.log information
  exit | exit code
  help
  interactive

  Значения кодов завершения программы:
   0 - все прошло без проишествий;
  -1 - У вас нет доступа к файлу (PermissionDeniedError)
  -2 - Не найден файл (FileNotFoundError)
  -3 - Неверное количество аргументов (CountOfArgumentsError)
  -4 - Вы выбрали несуществующее действие или не выбрали его вообще (ActionError)
  -5 - Неверный тип аргументов (TypeOfArgumentsError)
  -6 - На 0 делить нельзя (DivisionByZeroError)
  -7 - Часть скрипта отсутствует (ScriptAvailableError)
  -8 - У вас нет доступа к данной директории (DirPermissionDeniedError)
  -9 - Вы ввели директорию, когда ожидался файл. (DirFoundError)
  "
}

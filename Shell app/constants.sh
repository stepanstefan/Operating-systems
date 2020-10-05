#!/bin/bash

PermissionDeniedError=-1
FileNotFoundError=-2
CountOfArgumentsError=-3
ActionError=-4
TypeOfArgumentsError=-5
DivisionByZeroError=-6
ScriptAvailableError=-7
DirPermissionDeniedError=-8
DirFoundError=-9

PermissionDeniedErrorMessage="У вас нет доступа к файлу"
FileNotFoundErrorMessage="Не найден файл"
CountOfArgumentsErrorMessage="Неверное количество аргументов"
ActionErrorMessage="Вы выбрали несуществующее действие или не выбрали его вообще."
TypeOfArgumentsErrorMessage="Неверный тип аргументов."
DivisionByZeroErrorMessage="На 0 делить нельзя."
ScriptAvailableErrorMessage="Действие не выполнимо. Часть скрипта отсутствует."
DirPermissionDeniedErrorMessage="У вас нет доступа к данной директории"
DirFoundErrorMessage="Вы ввели директорию, когда ожидался файл."

#!/bin/bash


interactive()  {
  while true; do
    echo "Введите букву для выбора действия, или его название:

    \"c\" для выбора "calc"
    \"s\" для выбора "search"
    \"r\" для выбора "reverse"
    \"n\" для выбора "strlen"
    \"l\" для выбора "log"
    Для просмотра руководства по использованию введите \"h\" или \"help\"
    Для завершения программы введите \"e\" или \"exit\"
    "
    read action
    case $action in
      c|calc)
        includeFile "calc.sh"
        echo "Введите действие:";
        read action
        echo "Введите первое число:";
        read first
        echo "Введите второе число:";
        read second
        calc "$action" "$first" "$second"
        ;;
      s|search)
        includeFile "search.sh"
        echo "Введите директорию:";
        read directory
        echo "Введите слово или регулярное выражение:";
        read string
        search "$directory" "$string"
        ;;
      r|reverse)
        includeFile "reverse.sh"
        echo "Введите input файл:";
        read input
        echo "Введите output файл:";
        read output
        reverse "$input" "$output"
        ;;
      n|strlen)
        includeFile "strlen.sh"
        echo "Введите строку:";
        read string
        strlen "$string"
        ;;
      l|log)
        includeFile "log.sh"
        log "/var/log/anaconda/X.log"
        ;;
      h|help)
        includeFile "help.sh"
        help
        ;;
      e|exit)
        includeFile "exit.sh"
        echo "Введите код завершения, по умолчанию - 0:";
        read code
        exit "$code"
      esac
      echo " "
  done
}

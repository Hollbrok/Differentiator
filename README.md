# Differentiator
Это 7-й проект в рамках курса __ILAB__. 
- [X] Что реализовано? <details><summary></summary>
    - [X] Реализованно символьное дифференцирование с помощью деревьев:
        - [X] Выражений "школьного" уровня (частные производные __констант__, __переменных__, __сложения__, __вычитания__, __умножения__, __деления__; __степенной функции__, __синуса__, __косинуса__ как сложных функций);
        - [X] некоторых (почти всех) элементарных функций.
        - [X] полной производной (по всем переменных).
    - [X] Дампом в дерево через __graphviz__.
    - [X] Дампом в __TeX__.
    - [X] Генерацией в __TeX__ эпической псевдонаучной статьи о взятии полной производной во имя неразделенной любви к лабам по общефизу или матанализу.
    - [X] Добавлено 3 уровня оптимизации: обычных выражение ( 1+2^(3*5) ), затем выражений типа (0 * x) ==>> 0 и т.п., и последний, это x * 2 + x/1 ==>> x * (2 + 1).
- [X] Как установить и взять производную? <details><summary></summary>
    - [X] Скачать все содержимое следующей [папки](https://github.com/Hollbrok/Differentiator/tree/master/DOWNLOAD%20TO%20USE).
    - [X] После скачивания останется только ввести выражние в __text.txt__, а затем запустить __Differentiator.exe__.
    - [X] После этих действий откроется __затеханная статья с подробный гайдом__ как взять производную от вашего примера.
    - [X] Теперь смело можете удалять __wolframalpha__ из своих закладок, ведь теперь вы сможете взять производную даже в дикой глуши __без интернета__, нужно только ноутбук!
# TODO
- [ ] Самоудаление всех файлов, кроме статьи
- [ ] Еще один уровень оптимизации
- [ ] Добавить в функцию __make_article()__ bool аргумент, чтобы можно было __вкл/выкл__ режим дебага, при котором выводятся дампы всех стадий обработки дерева.
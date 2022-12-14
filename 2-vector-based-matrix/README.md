# Методы программирования 2: Верхнетреугольные матрицы на шаблонах


## Цели и задачи

В рамках лабораторной работы ставится задача создания программных средств, поддерживающих эффективное хранение матриц специального вида (верхнетреугольных) и выполнение основных операций над ними:

- сложение/вычитание;
- копирование;
- сравнение.

В процессе выполнения лабораторной работы требуется использовать систему контроля версий **Git** и фрэймворк для разработки автоматических тестов **Google Test**.

Перед выполнением работы студенты получают данный проект-шаблон, содержащий следующее:

 - Интерфейсы классов *Вектор* и *Матрица* (h-файл)
 - Начальный набор готовых тестов для каждого из указанных классов.
 - Набор заготовок тестов для каждого из указанных классов. 
 - Тестовый пример использования класса *Матрица*

Выполнение работы предполагает решение следующих задач:

  1. Реализация методов шаблонного класса `TVector` согласно заданному интерфейсу.
  1. Реализация методов шаблонного класса `TMatrix` согласно заданному интерфейсу.
  1. Обеспечение работоспособности тестов и примера использования.
  1. Реализация заготовок тестов, покрывающих все методы классов `TVector` и `TMatrix`.
  1. Модификация примера использования в тестовое приложение, позволяющее задавать матрицы и осуществлять основные операции над ними.

## Используемые инструменты

- Система контроля версий [Git][git].
- Фреймворк для написания автоматических тестов [Google Test][gtest]. Не
    требует установки, идет вместе с проектом-шаблоном.
  - Среда разработки Microsoft Visual Studio (2008 или старше).
  - Опционально. Утилита [CMake](http://www.cmake.org) для генерации проектов по сборке исходных кодов. Может быть использована для генерации решения для среды разработки, отличной от Microsoft Visual Studio 2008 или 2010, предоставленных в данном проекте-шаблоне.

## Общая структура проекта

Структура проекта:

  - `include` — директория для размещения заголовочных файлов.
  - `samples` — директория для размещения тестового приложения.
  - `test` — директория с модульными тестами и основным приложением,
  инициализирующим запуск тестов.
  - `work` - рабочий каталог, в котором создаются подкаталоги студентов в соответствии с названием ветки **Git**.
  - `README.md` — информация о проекте, которую вы сейчас читаете.
  - Служебные файлы
    - `.gitignore` — перечень расширений файлов, игнорируемых Git при добавлении
      файлов в репозиторий.
    - `CMakeLists.txt` — корневой файл для сборки проекта с помощью CMake. Может
      быть использован для генерации проекта в среде разработки, отличной от
      Microsoft Visual Studio.

В решении содержатся следующие модули:

  - Модуль `utmatirx`, содержащий реализацию классов Вектор и Матрица (файл
    `./include/utmatrix.h`). Поскольку оба класса шаблонные, реализацию методов необходимо выполнять непосредственно в заголовочном файле. При этом интерфейсы классов должны
    оставаться неизменными.
  - Тесты для классов Вектор и Матрица (файлы `./test/test_tvector.cpp`, `./test/test_tmatrix.cpp`).
  - Пример использования класса Матрица (файл `./samples/sample_matrix.cpp`).


## Порядок выполнения работы

- написать реализацию классов *Вектор* и *Матрица* в заголовочном файле `utmatrix.h`;
- построить тестовое приложение **google test** с данными в работе тестами  и убедиться, что все тесты проходят;
- построить приложение с примером из файла `sample_matrix.cpp` в каталоге `samples`;
- написать не менее 10 своих тестов, разместив их в файле `mytests.cpp` и протестировать свои классы с помощью своих тестов;
- создать ветку в соответствии со списком в каталоге `work`;
- скопировать в каталог `work\имя_ветки` следующие файлы:
   - `utmatrix.h`
   - `sample_matrix.h`
   - `test_tmatrix.cpp`
   - `test_tvector.cpp`
   - `test_main.cpp`
   - `mytests.cpp`
- сделать push-запрос в родительский репозиторий содержимым своей ветки;

# Бинарные файлы
Файлы в компьютере могут храниться в двух вариантах: 
* Текстовые файлы – человеко-читаемые файлы, набор из различны символов.
* Бинарные файлы – файлы, «понятные» компьютеру. Представляющие собой последовательный набор байт. 

**Недостатки бинарных файлов** – для подготовки файла нужны специальные программы. \
**Достоинства бинарных файлов** – прямой доступ к данным, возможность позиционирования на любое место в файле, чтение данных может быть прямым без использования массива, данные хранятся в том же виде, что и в оперативной памяти, не тратится время на преобразование и не тратится лишняя память на хранение текстовой копии, поэтому когда не хватает оперативной памяти, то можно использовать бинарные файлы вместо текстовых, можно одновременно и читать и писать в бинарный файл. 

# Основные функции по работе с бинарными файлами

| Объявление функции       | Пояснение |
| ----------- | ----------- |
| `FILE * fopen(const char * fname, const char * mode);`      | Открытие файла, возвращает указатель на дескриптор файла. Важно какой указан тип открытия (mode). Возвращает null в случае ошибки. |
| `int fclose(FILE *fp);`   | Закрытие файла        |
| `size_t fread(void * ptrvoid, size_t size, size_t count, FILE * filestream);`   | Функция считывает `count` элементов, размера `size` байт, из потока, и сохраняет его в блоке памяти, на который указывает `ptrvoid`. Индикатор положения потока увеличивается на общее число записанных байтов. Возвращаемое значение – общее количество, успешно считанных, элементов. |
| `size_t fwrite(const void * ptrvoid, size_t size, size_t count, FILE * filestream);`   | Функция записывает `count` элементов, размера `size` байт, из блока памяти, на который указывает `ptrvoid`. Индикатор положения потока увеличивается на общее число записанных байтов. Возвращаемое значение - Общее число элементов, которые успешно были записаны.        |
| `int fseek(FILE * filestream, long int offset, int origin);`   | Перемещает указатель позиции в файловом потоке на число байт `offset` относительно `origin` : `SEEK_SET` - Начало файла, `SEEK_CUR` - Текущее положение файла, `SEEK_END` - Конец файла        |
| `long int ftell(FILE * filestream);`   | Возвращает количество байт от начала файла до текущего положения указателя файлового потока `filestream` |
| `void rewind (FILE * filestream);`   | Устанавливает внутренний указатель положения файла в начальное положение (начало файла).        |
| `int fflush(FILE * filestream);`   | Если поток был открыт для записи (или, если он был открыт для обновления и последняя операция ввода/вывода была операцией вывода) любые незаписанные данные в выходном буфере записываются в файл. Если аргумент является нулевым указателем, то открытый файл очищается. Во всех других случаях, поведение зависит от конкретной реализации библиотеки. В некоторых реализациях, очистка потока, открытого для чтения, вызывает очистку его входного буфера (но это не стандартное поведение). Поток остается открытым после вызова функции `fflush.`       |

# lab1

Использование **`perror`** и **`std::cerr`** имеет разные предназначения и случаи применения. Оба инструмента позволяют выводить сообщения об ошибках, но работают по-разному:

### 1. **`perror`**:

-   **Функция**: `void perror(const char *s)`
-   **Назначение**: `perror` выводит сообщение об ошибке, связанное с глобальной переменной **`errno`**, которая хранит код последней системной ошибки.
-   **Вывод**: `perror` выводит строку `s` (если она не равна `NULL`), затем двоеточие и пробел, после чего добавляет строку, соответствующую текущему значению `errno` (например, "No such file or directory" или "Permission denied").
-   **Используется, когда**: Необходим вывод сообщения об ошибке, связанной с системными вызовами, такими как `fork()`, `execvp()`, `open()`, `read()`, и другими функциями, которые могут установить `errno`.

#### Пример использования `perror`:

```cpp
if (fork() == -1) {
    perror("Error creating the process");
    exit(1);
}
```

**Вывод** (если произошла ошибка):

```
Error creating the process: Resource temporarily unavailable
```

### 2. **`std::cerr`**:

-   **Тип**: Поток ошибок в C++ (объект типа `std::ostream`).
-   **Назначение**: `std::cerr` используется для вывода сообщений об ошибках в стандартный поток ошибок (`stderr`). Он не привязан к `errno` и может выводить любые произвольные сообщения, как и `std::cout`, но в поток ошибок.
-   **Вывод**: Можно вывести любое сообщение, например, дополнительную информацию об ошибке, отладочные сообщения или результаты анализа.
-   **Используется, когда**: Нужно вывести произвольные сообщения об ошибках, которые не связаны напрямую с системными вызовами или когда требуется более детализированный или форматированный вывод.

#### Пример использования `std::cerr`:

```cpp
if (someConditionFailed) {
    std::cerr << "Custom error: failed to do something, error code: " << errorCode << std::endl;
}
```

**Вывод**:

```
Custom error: failed to do something, error code: 42
```

### Когда использовать что:

1. **Используйте `perror`**:

    - Когда ошибка вызвана системным вызовом, и вам нужно вывести сообщение, соответствующее значению переменной `errno`.
    - Это удобно для системных ошибок, таких как ошибки при работе с файлами, создании процессов, взаимодействии с памятью и т.п.

    #### Пример:

    ```cpp
    if (execvp(args[0], args) == -1) {
        perror("Error when starting a child program");
        exit(1);
    }
    ```

2. **Используйте `std::cerr`**:

    - Когда нужно выводить **произвольные сообщения**, которые могут включать пользовательские ошибки, форматированные строки, отладочную информацию или дополнительную информацию об ошибках.
    - В тех случаях, когда `errno` не играет роли, или когда вы хотите сами контролировать формат вывода.

    #### Пример:

    ```cpp
    if (customFunctionFailed) {
        std::cerr << "An error occurred in custom function, error code: " << customErrorCode << std::endl;
    }
    ```

### Сравнение:

| **Особенность**      | **`perror`**                                       | **`std::cerr`**                                   |
| -------------------- | -------------------------------------------------- | ------------------------------------------------- |
| **Назначение**       | Вывод сообщения об ошибке, связанной с `errno`     | Произвольный вывод ошибок и сообщений             |
| **Используется для** | Системные вызовы и ошибки, возвращающие `errno`    | Любые пользовательские или произвольные ошибки    |
| **Выводит**          | Сообщение + описание ошибки, основанное на `errno` | Произвольное сообщение, управляемое пользователем |
| **Пример вывода**    | `Error: No such file or directory`                 | `Custom error: failed to open file`               |

### Заключение:

-   **`perror`** отлично подходит для вывода стандартных системных ошибок, так как автоматически отображает описание ошибок, связанных с переменной `errno`.
-   **`std::cerr`** более универсален и может использоваться для вывода любых сообщений, которые не связаны с системными ошибками или когда нужно вывести более детализированные или форматированные сообщения.

В большинстве системных программ вы можете использовать **`perror`** для отображения ошибок, связанных с вызовами операционной системы, а **`std::cerr`** для сообщений, которые не связаны с системными вызовами.
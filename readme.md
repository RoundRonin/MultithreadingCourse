# Steps

## 1. Run omp 

```cpp
#include <stdio.h>

int main(void) {
#pragma omp parallel
    {
        printf("Hello\n");
    }
    
    return 0; 
}
```

По-умолчанию OMP создает столько потоков, сколько ядер в системе.

## 2. Check threads

Задача -- каждый процесс обрабатывает свою часть массива (нужно знать, сколько тредов и номер треда).

```cpp
#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        int n = omp_get_num_threads();
        int m = omp_get_thread_num();
        printf("Hello %i/%i\n", m, n);
    }
    
    return 0; 
}
```

Менеджмент тредов происходит на уровне ОС. Часть потоков может ожидать момента отправки на исполнение, поэтому нельзя ожидать, что треды стартанут одновременно

Поэтому для минимизации рандома при измерении времени надо убить весь шум. Плюс есть вопрос частоты процессора (особенно у моббильных процов), нужно втыкаться в зарядку против троттлинга.

## 3. Loops

```cpp
for (uint i = a; i < b; i++) {
    f(i); 
}
```

Мы хотим разбить этот цикл равномерно между n тредами и чтобы каждая итерация цикла обязательно в единственном экземпляре досталась какому-то треду

Положим, m = 4, b = 12 -- тогда каждому треду должна достаться обработка ровно 3 любых индексов i

Если b = 11, то три треда делают 3 итерации, один -- 1 итерация. То есть количество итераций отличаться должно не более чем на 1. 

Option 1
```cpp
#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        int n = omp_get_num_threads();
        int m = omp_get_thread_num();

        int a = 0;
        int b = 100;

        for (int i = m; i < b; i+=n) {
            printf("Hello %d (current thread -- %d)\n", i, m);
        }
    }
    
    return 0; 
}
```

Second options (doesn't work yet):
$$S=a+(b-a)*m/n$$
$$S=a+(b-a)*(m+1)/n$$

```cpp
#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        int n = omp_get_num_threads();
        int m = omp_get_thread_num();

        int a = 0;
        int b = 102;

        int width = b / n;
        int addition = b / n;

        //
        if (addition < 0) {
            int left = a + m * width + 1;
            int right = a + (m + 1) * width + 1;
        } else {
            int left = a + m * width;
            int right = a + (m + 1) * width;
        }


        for (int i = left; i < right; i+=1) {
            printf("Hello %d (current thread -- %d)\n", i, m);
        }
    }
    
    return 0; 
}
```

Выбирать один или другой вариант надо на основе решаемой задачи.

У каждого ядра свой кэш, как правило.
Кэширование происходит блоками по 64 байта (например) и тогда разбиение через i+=x приведет к тому, что мы убьем кэширование. Поэтому выгодно разбиение вторым подходом.

Первый вариант выгоден, когда задачи разных размеров (например, внутренний цикл зависит от внешнего линейно).
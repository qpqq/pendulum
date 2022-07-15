# Математический маятник

## Описание 

Моделирование простого интерактивного математического маятника.

## Системные требования

Для отрисовки нужна библиотека `sfml`

```bash
sudo apt install git
sudo apt install gcc
sudo apt install g++
sudo apt install make
sudo apt install cmake
sudo apt install libsfml-dev
```


## Установка

```bash
cd <work_path>
git clone https://github.com/qpqq/pendulum.git
```

## Запуск

Если нет папки `build`, то создаём её

```bash
mkdir build
```

Компилируем и запускаем в папке `build`

```bash
cd build
cmake ..
cmake --build . -j 8
sudo ./pendulum
```

## Использование 

`space` — для остановки маятника 

`лкм` по грузику — для управления положением
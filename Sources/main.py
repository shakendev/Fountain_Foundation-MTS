import configparser     # библиотека для парсинга конфига
import numpy as np  # numpy для математических рассчётов
import wave  # для работы с wav

from score import *     # импортируем партутуру-сущность

"""
Описание работы с программой находится в readme.txt
Модуль main.py отвечает за преобразование музыкального файла, путь к которому указан в settings.conf
Модуль score.py отвечает за партуру-сущности
Итоговая партитура фонтана учитывает громкости и частоты каждого из каналов
"""

#   нормализация каждой амплитуды для дальнейшей работы с ней
def normalize(samples, bits_per):
    return [t / 2 ** bits_per for t in samples]

#   парсинг конфига
conf = configparser.RawConfigParser()
conf.read("settings.conf")

#   выбор разрядности для парсинга аудиофайла в битовый массив
width_to_bits = {1: np.int8, 2: np.int16, 3: np.int16, 4: np.int32}
width_to_bits_ = {1: 8, 2: 16, 3: 16, 4: 32}

RED = 2     # константа прореживания

# открываем wav-файл, используем путь из конфига
wav = wave.open(conf.get("common", "nameTrack"), mode='r')  # открываем wav-файл с режимом на чтение
(nchannels, sampwidth, framerate, nframes, comptype, compname) = wav.getparams()  # читаем параметры нашего wav-файла
"""
nchannels - количество каналов (моно/стерео)
sampwidth - разрядность
framerate - количество фреймов в секунду
nframes - общее число фреймов аудиофайла
comptype - способ компрессии
compname - название компрессии
"""

print('Характеристики аудиофайла:', nchannels, sampwidth, framerate, nframes, comptype, compname)
print('Пожалуйста, подождите. Идёт преобразование. Время ожидания ~ 1-2 минуты')

"""Определяем основные характеристики для дальнейшей работы"""
sample_size = 4 * 1024  # выбираем размер кадра из 4 * 1024 фреймов
duration = nframes / framerate  # длительность потока в секундах
timer = round(sample_size / framerate, 7)  # определяем длительность таймера
part = []  # будущая матрица
"""
Основной цикл, рассматривающий аудиофайл от начала до конца покусочно (!)
ps. рассматриваем пока что только МОНО
"""
end_of_cycle = int(round(duration / timer, 4))   # количество выбираемых для обработки фреймор
previous_percent = 0
for i in range(0, end_of_cycle):
    percent_of_cycle = int(i / end_of_cycle * 100)
    if percent_of_cycle % 10 == 0 and percent_of_cycle > previous_percent:
        print('Прогресс: ' + str(percent_of_cycle) + '%')
    previous_percent = percent_of_cycle
    sample = wav.readframes(sample_size)  # отбираем кусочек аудиодорожки в виде ненормализованного массива амплитуд
    # номрмализация, требуется для преобразования Фурье в спектр
    data = normalize(np.fromstring(sample, width_to_bits[sampwidth]), width_to_bits_[sampwidth])

    # применяем преобразование Фурье
    channel = data[::2]
    furier_left = abs(np.fft.rfftn(channel))  # амплитуды на канале
    """
    Фильтрация каналов
    """
    # отбираем экстремумы для фильтрации
    max = np.mean(sorted(furier_left, reverse=True)[0:25])
    mid = np.mean(sorted(furier_left, reverse=True)[0:50])
    rand = np.random.randint(0, 3)
    if rand < 1:
        furier_left = furier_left * np.hamming(len(furier_left)) * 2
    for j in range(len(furier_left)):
        furier_left[j] = furier_left[j] * 10
        '''Дополнительная фильтрация, для улавливания менее заметных частот, чтобы избежать качетсвенных потерь'''
        if furier_left[j] > max:
            furier_left[j] = furier_left[j] * 0.7
        if j > 0.25 * len(furier_left):
            furier_left[j] = furier_left[j] * 1.4
        if j > 0.50 * len(furier_left):
            furier_left[j] = furier_left[j] * 1.4
        if j < 0.20 * len(furier_left):
            furier_left[j] = furier_left[j] * 0.7
        if j < 0.1 * len(furier_left):
            furier_left[j] = furier_left[j] * 0.8
        if np.mean(furier_left) < 50: furier_left[j] = furier_left[j] * 5
        if furier_left[j] > 100:
            furier_left[j] = 100

    b = []  # искомый массив из 13 значений амплитуд (из спектра) на момент времени t
    # Формируем столбики спектра для радов фонтана
    col = int(len(furier_left) / 13)
    for j in range(0, 13):
        b.append(np.mean(furier_left[j * col:(j + 1) * col]))
    part.append(b)
"""
На выходе получием массив b (размерностью 13), с ним должны будут работать партитуры
"""
print("Преобразование выполнено: 100%")
# проредим массив на констранту RED
timer = timer * RED
part = part[::2]
a = score(part, timer)  # инициализируем объект партитур

print('Количество строк = ', len(part))
print('Время одного такта =', timer)

text = a.create_score()
txt = open('partitura.txt', 'w')
for c in text:
    txt.write(c)
    txt.write('\n')
txt.close()
# if debug == 2:
#     subprocess.check_call(r"fountain.exe")

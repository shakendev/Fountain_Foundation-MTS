import numpy as np

"""Константы для работы фонатана"""
MIN_PUMP_POWER = 0.0  # минимально допустимая величина силы струи
# MAX = 2 # максимально допустимая вели
MIN_TIME_OF_MODE = 1.5  # минимальное время работы режима
MIN_TIME_OF_COLORMODE = 14  # мин время работы цветового режима


class score:
    current_mode = 0  # текущий режим
    is_mode_changed = False  # флаг, был ли сменён недавно режим
    current_color_mode = 0  # режим цвета
    current_time = 0.00
    last_time_change_mode = - MIN_TIME_OF_MODE  # последний момент смены режим
    last_time_change_colormode = - MIN_TIME_OF_COLORMODE  # последний момент смены режимы цвета

    def __init__(self, matrix_frequency, tact_time):
        self.matrix_frequency = matrix_frequency  # матрица частотного спектра
        self.current_frequency_half = []  # текущий массив частотного спектра
        self.tact_time = tact_time

    def _time_add(self):
        self.current_time = self.current_time + self.tact_time

    def _get_time(self):
        normal_time = str(round(self.current_time, 2))
        separate_index = normal_time.find('.')
        if len(normal_time[separate_index + 1:]) != 2:
            normal_time = normal_time + '0'
        return normal_time

    """Проверка состояния режима фонтана"""

    def _check_change_mode(self):
        if self.current_time - MIN_TIME_OF_MODE > self.last_time_change_mode:
            if np.mean(self.current_frequency_half) == 0:
                self.current_mode = 0
                self.is_mode_changed = True
            if np.mean(self.current_frequency_half) > 0 and self.current_mode != 1:
                self.current_mode = 1
                self.last_time_change_mode = self.current_time
                self.is_mode_changed = True
            if np.mean(self.current_frequency_half) > 15 and self.current_mode != 2:
                self.current_mode = 2
                self.last_time_change_mode = self.current_time
                self.is_mode_changed = True
            if np.mean(self.current_frequency_half) > 35 and self.current_mode != 3:
                self.current_mode = 3
                self.last_time_change_mode = self.current_time
                self.is_mode_changed = True
            if np.mean(self.current_frequency_half) > 52 and self.current_mode != 4:
                self.current_mode = 4
                self.last_time_change_mode = self.current_time
                self.is_mode_changed = True
            if np.mean(self.current_frequency_half) > 55 and self.current_mode != 5:
                self.current_mode = 5
                self.last_time_change_mode = self.current_time
                self.is_mode_changed = True
        # для дебага
        # print('TIME', self.current_time, 'LAST', self.last_time_change_mode, 'MEAN', np.mean(self.half), 'MODE', self.current_mode,
        #       'COLORMODE', self.current_color_mode)

    """Проверка возможности смены цветового режима"""

    def _check_change_colormode(self):
        if self.current_time - MIN_TIME_OF_COLORMODE > self.last_time_change_colormode:
            rand = np.random.randint(1, 5 + 1)
            self.current_color_mode = rand
            self.last_time_change_colormode = self.current_time

    """Важный метод, формирующий команды в строке партитуры"""

    def _create_command(self):
        command = ''
        self._check_change_mode()
        self._check_change_colormode()
        """Режимы насосов"""
        for i in range(0, len(self.current_frequency_half)):
            preset_random = np.random.randint(0, 4)
            if self.current_mode == 0:
                command = ''
            if self.current_mode == 1 and i != 4 and i != 5 and i != 6 and i != 7 and i != 8 and i != 9 and i != 11 and i != 12:
                self.current_frequency_half[10] = self.current_frequency_half[0]
                command = command + 'm' + str(i + 1) + ':sf(' + str(int(self.current_frequency_half[i])) + ')'
                command = command + "|"
                if self.is_mode_changed:
                    command = command + 'm6:off|m7:off|m8:off|m9:off|m10:off|m12:off|m13:off|octagon1:off|octagon2:off|octagon3:off|k7:off|'
                    self.is_mode_changed = False
            if self.current_mode == 2 and i != 4 and i != 0 and i != 3 and i != 7 and i != 9 and i != 10 and i != 12:
                self.current_frequency_half[11] = self.current_frequency_half[0]
                self.current_frequency_half[5] = self.current_frequency_half[1]
                self.current_frequency_half[6] = self.current_frequency_half[2]
                command = command + 'm' + str(i + 1) + ':sf(' + str(int(self.current_frequency_half[i])) + ')'
                command = command + "|"
                if self.is_mode_changed:
                    command = command + 'm1:off|m4:off|m8:off|m10:off|m11:off|m13:off|octagon1h1:cwave(10,4)|octagon1h2:cwave(10,4)|octagon3h1:cwave(10,4)|octagon3h2:cwave(10,4)|'
                    self.is_mode_changed = False
            if self.current_mode == 3 and i != 4 and i != 2 and i != 5 and i != 6 and i != 8 and i != 10 and i != 11:
                if preset_random == 0:
                    self.current_frequency_half[3] = self.current_frequency_half[0]
                else:
                    self.current_frequency_half[9] = self.current_frequency_half[0]
                self.current_frequency_half[12] = self.current_frequency_half[3]
                command = command + 'm' + str(i + 1) + ':sf(' + str(int(self.current_frequency_half[i])) + ')'
                command = command + "|"
                if self.is_mode_changed:
                    command = command + 'm3:off|m6:off|m7:off|m9:off|m11:off|m12:off|octagon1:off|octagon2:off|octagon3:off|k7:off|'
                    self.is_mode_changed = False
            if self.current_mode == 4 and i != 4 and i != 7 and i != 8 and i != 9 and i != 10 and i != 11 and i != 12:
                self.current_frequency_half[1] = self.current_frequency_half[0]
                command = command + 'm' + str(i + 1) + ':sf(' + str(int(self.current_frequency_half[i])) + ')'
                command = command + "|"
                if self.is_mode_changed:
                    command = command + 'm1:off|m8:off|m9:off|m10:off|m11:off|m12:off|m13:off|k6:on|k7:off|'
                    self.is_mode_changed = False
            if self.current_mode == 5 and i != 4 and i != 7 and i != 8 and i != 9 and i != 10 and i != 11 and i != 12:
                self.current_frequency_half[6] = self.current_frequency_half[0]
                if i != 0:
                    command = command + 'm' + str(i + 1) + ':sf(' + str(int(self.current_frequency_half[i])) + ')'
                    command = command + "|"
                if self.is_mode_changed:
                    if (np.random.randint(0, 2) == 1):
                        command = command + 'snake1:cwave(6,6)|snake2:cwave(7,6)|m5:off|m8:off|m9:off|m10:off|m11:off|m12:off|m13:off|k6:off|'
                    else:
                        command = command + 'snake1:on|snake2:on|m5:off|m8:off|m9:off|m10:off|m11:off|m12:off|m13:off|k6:off|'
                    self.is_mode_changed = False

            """Цветовые режимы"""
            # первый цветовой режим
            if self.current_color_mode == 1 and i != 4:
                if self.current_frequency_half[i] <= MIN_PUMP_POWER:
                    command = command + 'l' + str(i + 1) + ':k'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if MIN_PUMP_POWER < self.current_frequency_half[i] < 15:
                    command = command + 'l' + str(i + 1) + ':b'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if 30 <= self.current_frequency_half[i]:
                    command = command + 'l' + str(i + 1) + ':m'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
            # второй цветовой режим
            if self.current_color_mode == 2 and i != 4:
                if self.current_frequency_half[i] <= MIN_PUMP_POWER:
                    command = command + 'l' + str(i + 1) + ':k'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if MIN_PUMP_POWER < self.current_frequency_half[i] < 15:
                    command = command + 'l' + str(i + 1) + ':b'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if 30 <= self.current_frequency_half[i]:
                    command = command + 'l' + str(i + 1) + ':c'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
            # третий цветовой режим
            if self.current_color_mode == 3 and i != 4:
                if self.current_frequency_half[i] <= MIN_PUMP_POWER:
                    command = command + 'l' + str(i + 1) + ':k'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if MIN_PUMP_POWER < self.current_frequency_half[i] < 15:
                    command = command + 'l' + str(i + 1) + ':r'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if 30 <= self.current_frequency_half[i]:
                    command = command + 'l' + str(i + 1) + ':y'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
            if self.current_color_mode == 4 and i != 4:
                if self.current_frequency_half[i] <= MIN_PUMP_POWER:
                    command = command + 'l' + str(i + 1) + ':k'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if MIN_PUMP_POWER < self.current_frequency_half[i] < 15:
                    command = command + 'l' + str(i + 1) + ':b'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if 30 <= self.current_frequency_half[i]:
                    command = command + 'l' + str(i + 1) + ':y'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
            if self.current_color_mode == 5 and i != 4:
                if self.current_frequency_half[i] <= MIN_PUMP_POWER:
                    command = command + 'l' + str(i + 1) + ':k'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if MIN_PUMP_POWER < self.current_frequency_half[i] < 15:
                    command = command + 'l' + str(i + 1) + ':m'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
                if 30 <= self.current_frequency_half[i]:
                    command = command + 'l' + str(i + 1) + ':w'
                    if i != len(self.current_frequency_half) - 1:
                        command = command + "|"
        return command

    """Главный метод, собирающая многострочный текстовый файл"""

    def create_score(self):
        output_text_file = []  # текст партитуры на выход
        part_of_text_file = ''
        for spectrum in self.matrix_frequency:
            self.current_frequency_half = spectrum
            self._time_add()
            line_of_score = self._create_command()
            if line_of_score != '':
                part_of_text_file = self._get_time() + '\t' + line_of_score
            output_text_file.append(part_of_text_file)

        self._time_add()
        line_of_score = ''
        for j in range(0, len(self.current_frequency_half)):
            line_of_score = line_of_score + 'm' + str(j + 1) + ':off' + '|'
            line_of_score = line_of_score + 'l' + str(j + 1) + ':k'
            if j != len(self.current_frequency_half) - 1:
                line_of_score = line_of_score + "|"
        part_of_text_file = self._get_time() + '\t' + line_of_score
        output_text_file.append(part_of_text_file)
        return output_text_file

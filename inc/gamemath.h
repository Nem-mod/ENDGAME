#pragma once

#include <stdbool.h>
#include <stdlib.h>

int mx_rand(int min, int max);
bool mx_chance(int percent); // Принимает проценты от 0 до 100. Выводит true с заданым шансом
int mx_percent_from_int(int num, int percent);
int mx_int_dispersion(int num, int percent); // Принимает число и процент разброса. Возвращает принятое число с разбросом в данном диапазоне
int mx_get_percent_of_int(int max_num, int num);

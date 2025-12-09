#ifndef ROMAN_H
#define ROMAN_H

/** Переводит арабское число (1–3999) в римскую запись.
 * @param n число от 1 до 3999
 * @return строка с римским числом или NULL если вне диапазона
 */
const char* arabic_to_roman(int n);

/** Переводит римскую запись (строку) к арабскому числу.
 * @param s строка с римской записью в верхнем регистре
 * @return число (1–3999), либо 0 если ошибка */
int roman_to_arabic(const char* s);

#endif

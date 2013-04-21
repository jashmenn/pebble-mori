#include "num2words-en.h"
#include "string.h"
#include "math.h"

static const char* const TENS[] = {
  "",
  "ten",
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety"
};

static const char* const UNITS[] = {
  "",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eightteen",
  "nineteen"
};


size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

// more or less from
// http://stackoverflow.com/questions/2729752/converting-numbers-in-to-words-c-sharp
size_t number_to_words_r(int number, char* words, size_t length) {
  size_t remaining = length;

  if (number == 0)
    remaining -= append_string(words, remaining, "");
  else
    if ((number / 1000000) > 0) {
      remaining = number_to_words_r(number / 1000000, words, remaining);
      remaining -= append_string(words, remaining, " million ");
      number %= 1000000;
    }
    if ((number / 1000) > 0) {
      remaining = number_to_words_r(number / 1000, words, remaining);
      remaining -= append_string(words, remaining, " thousand ");
      number %= 1000;
    }

    if ((number / 100) > 0) {
      remaining = number_to_words_r(number / 100, words, remaining);
      remaining -= append_string(words, remaining, " hundred ");
      number %= 100;
    }

    if (number > 0) {
      // if (words != "")
      //  words += "and ";
   
      if (number < 20)
        remaining -= append_string(words, remaining, UNITS[number]);
      else
        {
          remaining -= append_string(words, remaining, TENS[number / 10]);
          if ((number % 10) > 0)
            remaining -= append_string(words, remaining, "-");
          remaining -= append_string(words, remaining, UNITS[number % 10]);
        }
    }
    return remaining;
}

size_t number_to_words(int number, char* words, size_t length) {
  memset(words, 0, length);
  return number_to_words_r(number, words, length);
}


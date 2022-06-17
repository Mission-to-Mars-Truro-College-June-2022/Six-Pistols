#include <ArduinoUnit.h>

bool isLeapYear(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

test(a_typical_common_year_return_false)
{
  assertFalse(isLeapYear(2001));
}

test(a_typical_leap_year_return_true)
{
  assertTrue(isLeapYear(1996));
}

test(an_atypical_common_year_return_false)
{
  assertFalse(isLeapYear(1900));
}

test(an_atypical_leap_year_return_true)
{
  assertTrue(isLeapYear(2000));
}

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  Test::run();

}

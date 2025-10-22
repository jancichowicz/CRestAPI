#include "../requestParser.h"

void test_requestParser_isParsingWorkingCorrectly(void) {
  const char *requestStr = "GET /forecastwttr?city=Lodz&hour=18 HTTP/1.1\nHost: 31.231.98.102\nAccept: plain/text";
  char *mockRequestString = (char*)malloc(strlen(requestStr)+1);
  strncpy(mockRequestString, requestStr, strlen(requestStr)+1);
  request req = parseRequest(mockRequestString);

  TEST_ASSERT_EQUAL_STRING("/forecastwttr", req.resource);
  TEST_ASSERT_EQUAL_STRING("city=Lodz&hour=18", req.queryParams);

  free(mockRequestString);
}

void test_requestParser_justResourceWithoutQueries(void) {
  const char *requestStr = "GET /forecastwttr HTTP/1.1\nHost: 31.231.98.102\nAccept: plain/text";
  char *mockRequestString = (char*)malloc(strlen(requestStr)+1);
  strncpy(mockRequestString, requestStr, strlen(requestStr)+1);
  request req = parseRequest(mockRequestString);

  TEST_ASSERT_EQUAL_STRING("/forecastwttr", req.resource);
  TEST_ASSERT_EQUAL_STRING(NULL, req.queryParams);

  free(mockRequestString);
}

void test_requestParser_wrongQuery(void) {
  const char *requestStr = "GET &foo? HTTP/1.1\nHost: 31.231.98.102\nAccept: plain/text";
  char *mockRequestString = (char*)malloc(strlen(requestStr)+1);
  strncpy(mockRequestString, requestStr, strlen(requestStr)+1);
  request req = parseRequest(mockRequestString);

  TEST_ASSERT_EQUAL_STRING("WRONG_QUERY", req.resource);
  TEST_ASSERT_EQUAL_STRING("WRONG_QUERY", req.queryParams);

  free(mockRequestString);
}

void test_requestParser_noResourceGiven(void) {
  const char *requestStr = "GET HTTP/1.1\nHost: 31.231.98.102\nAccept: plain/text";
  char *mockRequestString = (char*)malloc(strlen(requestStr)+1);
  strncpy(mockRequestString, requestStr, strlen(requestStr)+1);
  request req = parseRequest(mockRequestString);

  TEST_ASSERT_EQUAL_STRING("WRONG_QUERY", req.resource);
  TEST_ASSERT_EQUAL_STRING("WRONG_QUERY", req.queryParams);

  free(mockRequestString);
}

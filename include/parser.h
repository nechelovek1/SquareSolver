#ifndef PARSER_H
#define PARSER_H

const int MAX_COEFS = 20;

/*

*/
int parseEqation(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt);
int parsePolynom(const char s[], unsigned int len, double coefs[], unsigned int coefsCnt);

#endif
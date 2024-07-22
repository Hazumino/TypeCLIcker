#include "../include/keyboardChange.h"
#include <stdio.h>

char keyboardChange(int type, char c)
{
  switch(type)
  {
    case 1:
      return c;

    case 2:
      return change2dvorak(c);

  }
  return 0;
}

char change2dvorak(char ch) {
    switch (ch) {
        case 'a': return 'a'; case 'A': return 'A';
        case 'b': return 'x'; case 'B': return 'X';
        case 'c': return 'j'; case 'C': return 'J';
        case 'd': return 'e'; case 'D': return 'E';
        case 'e': return '.'; case 'E': return '>';
        case 'f': return 'u'; case 'F': return 'U';
        case 'g': return 'i'; case 'G': return 'I';
        case 'h': return 'd'; case 'H': return 'D';
        case 'i': return 'c'; case 'I': return 'C';
        case 'j': return 'h'; case 'J': return 'H';
        case 'k': return 't'; case 'K': return 'T';
        case 'l': return 'n'; case 'L': return 'N';
        case 'm': return 'm'; case 'M': return 'M';
        case 'n': return 'b'; case 'N': return 'B';
        case 'o': return 'r'; case 'O': return 'R';
        case 'p': return 'l'; case 'P': return 'L';
        case 'q': return '\''; case 'Q': return '\"';
        case 'r': return 'p'; case 'R': return 'P';
        case 's': return 'o'; case 'S': return 'O';
        case 't': return 'y'; case 'T': return 'Y';
        case 'u': return 'g'; case 'U': return 'G';
        case 'v': return 'k'; case 'V': return 'K';
        case 'w': return ','; case 'W': return '<';
        case 'x': return 'q'; case 'X': return 'Q';
        case 'y': return 'f'; case 'Y': return 'F';
        case 'z': return ';'; case 'Z': return ':';
        case ',': return 'w'; case '<': return 'W';
        case '.': return 'v'; case '>': return 'V';
        case '/': return 'z'; case '?': return 'Z';
        case ';': return 's'; case ':': return 'S';
        case '\'': return '-'; case '\"': return '_';
        case '-': return '['; case '_': return '{';
        case '=': return ']'; case '+': return '}';
        case '[': return '='; case '{': return '+';
        case ']': return '\\'; case '}': return '|';
        case '\\': return '/'; case '|': return '?';
        default: return ch;  // return the character itself if no match is found
    }
}

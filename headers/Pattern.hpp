#ifndef PATTERN_H
#define PATTERN_H

/*
 '+' for the plus pattern
 '1' all ones pattern
 '/' Secondry Diagonal ones
 '\' Main Diagonal ones

 default all zeros pattern
*/
class Pattern{
public:
  Pattern(int _size, const int**& _pattern){
    size = _size;
    pattern = new int*[size];
    for(int r = 0 ; r < size ; ++r){
      pattern[r] = new pattern[_size];
      for(int c = 0 ; c < size ; ++c)
        pattern[r][c] = _pattern[r][c];
    }
  }

  Pattern(const int& _size,const unsigned char& pattern, const int& mainV = 1, const int& secV = 0){
    size = _size;
    pattern = new int*[size];
    switch (/* expression */) {
      case /* value */:
    }
  }

  toPlusPattern(const int& mainV = 1, const int& secV = 0);
  toMainDiagonalPattern(const int& mainV = 1, const int& secV = 0);
  toSecDiagonalPattern(const int& mainV = 1, const int& secV = 0);
  toOnesPattern();
  
private:
  int size;
  int** pattern;
};

#endif

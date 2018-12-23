#include "../headers/ImageProcessor.hpp"

Image ImageProcessor :: applyThreshold(Image image, const int& th){
  Image ret = image;
  for(int x = 0 ; x < image.width() ; ++x){
    for(int y = 0 ; y < image.height() ; ++y){
      if(image.get_gray_pixel(x, y) < th)  ret.set_pixel(x, y, 0);
      else ret.set_pixel(x, y, 255);
    }
  }
  return ret;
}

Image ImageProcessor :: applyMedianFilter(Image image){
  int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
  int dy[] = {0, 0, 1, -1, -1, -1, 1, 1};
  Image ret = image;
  vector<int> v;

  for(int x = 0  ; x < image.width() ; ++x){
    for(int y = 0 ; y < image.height() ; ++y){
      v.clear();
      v.push_back(image.get_gray_pixel(x, y));
      for(int k = 0 ; k < 8 ; ++k){
        int nx = x + dx[k], ny = y + dy[k];
        if(nx >= 0 && nx < image.width() && ny >= 0 && ny < image.height())
          v.push_back(image.get_gray_pixel(nx, ny));
      }
      sort(v.begin(), v.end());
      ret.set_pixel(x, y, v[v.size()>>1]);
    }
  }
  return ret;
}

Image ImageProcessor :: applyErosion(Image image){
  Image ret(image.width(), image.height());
  for(int x = 0 ; x < image.width() ; ++x){
    for(int y = 0 ; y < image.height() ; ++y){  //Apply fit
      Pair fit = structuringElement3(image, x, y);
      u_int32 value = ((fit.first == 5) ? image.get_gray_pixel(x, y) : 255);
      ret.set_pixel(x, y, value);
    }
  }
  return ret;
}

Image ImageProcessor :: applyDilation(Image image){
  Image ret(image.width(), image.height());
  for(int x = 0 ; x < image.width() ; ++x){
    for(int y = 0 ; y < image.height() ; ++y){  //Apply hit
      Pair hit = hitter(image, x, y);
      u_int32 value = (hit.first ? 0 : 255);
      ret.set_pixel(x, y, value);
    }
  }
  return ret;
}

ImageProcessor::Pair ImageProcessor :: hitter(const Image& image, u_int32 x, u_int32 y){
  const bool element[][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
  };
  int hits = 0;
  int ins = 0;
  for(u_int32 i = x-1 ; i <= x+1 ; ++i){
    for(u_int32 j = y-1 ; j <= y+1 ; ++j)if(validPoint(image, i, j)){
      ins += element[i-(x-1)][j-(y-1)];
      if(!image.get_gray_pixel(i, j))
        hits += element[i-(x-1)][j-(y-1)];
    }
  }
  return Pair(hits, ins);
}

ImageProcessor::Pair ImageProcessor :: structuringElement3(const Image& image, u_int32 x, u_int32 y){
  const bool element[][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
  };
  int hits = 0;
  int ins = 0;
  for(u_int32 i = x-1 ; i <= x+1 ; ++i){
    for(u_int32 j = y-1 ; j <= y+1 ; ++j)if(validPoint(image, i, j)){
      ins += element[i-(x-1)][j-(y-1)];
      if(image.get_gray_pixel(i, j) == image.get_gray_pixel(x, y))
        hits += element[i-(x-1)][j-(y-1)];
    }
  }
  return Pair(hits, ins);
}

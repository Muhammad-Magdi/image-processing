#include <cstdio>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include "headers/ImageProcessor.hpp"
#include "headers/bitmap_image.hpp"

#define Image bitmap_image
#define RGB rgb_t

using namespace std;
typedef long long ll;
typedef unsigned char pixel;

map<int, RGB> mp;
inline RGB getColor(const int& id){
  if(!mp.count(id)) mp[id] = RGB(rand()%256, rand()%256, rand()%256);
  return mp[id];
}

map<int, int> gray;
inline int getGrayColor(const int& id){
  if(!gray.count(id)) gray[id] = rand()%256;
  return gray[id];
}

void BFS(int srcX, int srcY, bool**& colored, Image& image, const int& color){
  int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
  int dy[] = {0, 0, 1, -1, -1, -1, 1, 1};
  queue<pair<int, int> > q;
  RGB tmpPixel = image.get_pixel(srcX, srcY);

  q.push({srcX, srcY});
  colored[srcX][srcY] = color;
  while(!q.empty()){
    int ux = q.front().first, uy = q.front().second;
    image.set_pixel(ux, uy, getColor(color));
    q.pop();

    for(int k = 0 ; k < 8 ; ++k){
      int vx = ux + dx[k], vy = uy + dy[k];
      if(ImageProcessor::validPoint(image, vx, vy) && !colored[vx][vy] && image.get_pixel(vx, vy) == tmpPixel){
        colored[vx][vy] = true;
        q.push({vx, vy});
      }
    }
  }
  string fileName = "output/filling-00" + to_string(color) + ".bmp";
  image.save_image(fileName);
}


void floodFill(Image& image){
  bool** colored = new bool*[image.width()];
  for(int x = 0 ; x < image.width() ; ++x){
    colored[x] = new bool[image.height()];
    for(int y = 0 ; y < image.height() ; ++y){
      colored[x][y] = 0;
    }
  }

  //FloodFill
  int usedColors = 0;
  for(int y = 0 ; y < image.height() ; ++y){
    for(int x = 0 ; x < image.width() ; ++x){
      if(!colored[x][y]){
        BFS(x, y, colored, image, ++usedColors);
      }
    }
  }
}

int main(int argc, char *argv[]){
  srand(time(0));
  string fileName;
  if(argc > 1)
    fileName = "input/" + string(argv[1]);
  else throw("You Should determine the input image name as an argument");
  Image image(fileName);
  ImageProcessor ip;

  image.convert_to_grayscale();
  image.save_image("output/01gray.bmp");
  image = ip.applyMedianFilter(image);
  image.save_image("output/02median.bmp");
  image = ip.applyThreshold(image, 240);
  image.save_image("output/03threshold.bmp");
  image = ip.applyErosion(image);
  image.save_image("output/04erosion.bmp");
  image = ip.applyDilation(image);
  image.save_image("output/05dilation.bmp");
  floodFill(image);
  return 0;
}

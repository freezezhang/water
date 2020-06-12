#include "buffer.h"
#include <cstdio>

int main() {
  Buffer buffer;
  char str[] = "abcdefjhijklmnopqrstuvwxyz1234567890";
  size_t length = strlen(str);
  buffer.Write(str, length);
  /*
  char buff0[7];
  size_t r0 = buffer.Read(buff0, 6);
  buff0[r0] = 0;

  char buff1[12];
  size_t r1 = buffer.Read(buff1, 11);
  buff1[r1] = 0;

  char buff2[15];
  size_t r2 = buffer.Read(buff2, 14);
  buff2[r2] = 0;

  char buff3[25];
  size_t r3 = buffer.Read(buff3, 24);
  buff3[r3] = 0;
  char buff4[125];
  size_t r4 = buffer.Read(buff4, 124);
  buff4[r4] = 0;

*/
  Buffer buf;
  buf.Write(str, length);
  buffer.Append(buf);

  printf("buffer data count: %d\n", buffer.DataCount());
  printf("buf data count: %d\n", buf.DataCount());

  char buff4[125];
  size_t r4 = buffer.Read(buff4, 124);
  buff4[r4] = 0;

  /*
  printf("%d\n", buffer.ReadMove(12));
  printf("%d\n", buffer.DataCount());
  printf("%d\n", buffer.ReadMove(16));
  printf("%d\n", buffer.DataCount());
  */

/*
  printf("%s\n", buff0);
  printf("%s\n", buff1);
  printf("%s\n", buff2);
  printf("%s\n", buff3);
*/
  printf("%s\n", buff4);
/*
  char xh[256] = "#*******************#";
  buffer.Write(xh, strlen(xh));
  */
/*
  printf("buffer data count:%d\n", buffer.DataCount());
*/
  Buffer b2;
  char xh[256] = "#*******************#";
  b2.Write(xh, strlen(xh));
  printf("b2 data count: %d\n", b2.DataCount());
  buffer.Splice(b2);
  printf("b2 data count: %d\n", b2.DataCount());
  b2.Write(xh, strlen(xh));
  
  printf("buffer data count:%d\n", buffer.DataCount());

  char buff5[125];
  size_t r5 = buffer.Read(buff5, 124);
  buff5[r5] = 0;
  printf("%s\n", buff5);

  r5 = b2.Read(buff5, 124);
  buff5[r5] = 0;
  printf("b2: %s\n", buff5);

  /*
  Buffer::IOVecs iovecs;
  Buffer::IOVecsSizePair p = buffer.DataIOvecs(&iovecs);
  
  for (int i = 0; i < iovecs.size(); ++i) {
    printf("%s\n", p.first[i]);
  }
  */
}
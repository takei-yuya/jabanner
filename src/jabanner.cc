/*
 * Jabanner
 *
 * Copyright (C) 2007- TAKEI Yuya <takei.yuya _at_ gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* プリプロセッサ */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef HAVE_LIBNCURSES
#include <ncurses.h>
#endif

#define PI 3.14159265358
#define TEXT_STRING_BUF (1024*64)

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <termios.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define max2(aa,bb) (((aa)>(bb))?(aa):(bb))
#define min2(aa,bb) (((aa)<(bb))?(aa):(bb))
#define max4(aa,bb,cc,dd) (max2(max2((aa),(bb)),max2((cc),(dd))))
#define min4(aa,bb,cc,dd) (min2(min2((aa),(bb)),min2((cc),(dd))))

#define DEFAULT_USE_ANTIALIAS false
#define DEFAULT_ROTATE 0
#define DEFAULT_CHARS (char *)"#MND80Z7I?+=~:,. "
#define DEFAULT_DELAY 10000
#define DEFAULT_LOOP_COUNT 0
#define DEFAULT_TOP_MARGIN 0
#define DEFAULT_RIGHT_MARGIN 0
#define DEFAULT_BOTTOM_MARGIN 0
#define DEFAULT_LEFT_MARGIN 0
#define DEFAULT_SIZE 8
#define DEFAULT_WIDTH -1
#define DEFAULT_DIRECTION sdNONE;

typedef enum scrollDirection {
  sdNONE,
  sdLEFT,
  sdDOWN,
  sdRIGHT,
  sdUP,
  sdMANUAL
} scrollDirection;

int gdImageGetYvalueFormPixel(gdImagePtr im, int x, int y)
{
  int i = gdImageGetPixel(im, x, y);
  int rr = gdImageRed(im, i);
  int gg = gdImageGreen(im, i);
  int bb = gdImageBlue(im, i);
  return((2 * rr + 4 * gg + 1 * bb) / 7);
}

void version()
{
  printf("%s Ver.%s\n", PACKAGE_NAME, PACKAGE_VERSION);
}

void usage(int argc, char* argv[])
{
  printf("Usage: %s [Options] ... String ...\n", argv[0]);
  printf("\n");
  printf("Print \"banner\" version of string.\n");
  printf("ex) jabanner \"foo bar baz\" ... print \"banner\" in a line.\n");
  printf("ex) jabanner foo bar baz ... print \"banner\" in 3 lines.\n");
  printf("\n");
  printf("Mandatory arguments to long options are mandatory for short options.\n");
  printf("  -a, --antialias            Use antialias.\n");
  printf("  -c, --chars=STRING         Charactors that use with antialias.[\"%s\"]\n", DEFAULT_CHARS);
  printf("  -f, --font=FILE            Font file.[%s]\n", DEFAULT_FONT);
  printf("  -h, --help                 Show this message.\n");
#ifdef HAVE_LIBNCURSES
  printf("  -l, --loop=NUMBER          Scroll banner NUMBER times.(negative value means infinity)[%d]\n", DEFAULT_LOOP_COUNT);
#endif
  printf("  -m, --margin=NUMBERs       Set margin.(top,right,bottom,left)[%1$d,%2$d,%3$d,%4$d]\n", DEFAULT_TOP_MARGIN, DEFAULT_RIGHT_MARGIN, DEFAULT_BOTTOM_MARGIN, DEFAULT_LEFT_MARGIN);
  printf("  -o, --open=FILE            Use FILE as String.\n");
  printf("  -r, --rotate=NUMBER        Rotate \"banner\".(degree)[%d]\n", DEFAULT_ROTATE);
  printf("  -s, --size=NUMBER          Font size(Pt)[%d]\n", DEFAULT_SIZE);
#ifdef HAVE_LIBNCURSES
  printf("  -t, --time=NUMBER          Scroll delay.(micro seconds)[%d]\n", DEFAULT_DELAY);
#endif
  printf("  -v, --version              Show version.\n");
  printf("  -w, --width=NUMBER         Set Width.(<0:use terminal width,0:show all)[%d]\n", DEFAULT_WIDTH);
#ifdef HAVE_LIBNCURSES
  printf("  -x, --x                    Scroll banner from right to left.(use ncurses)\n");
  printf("  -y, --y                    Scroll banner from up to down.(use ncurses)\n");
  printf("  -X, --X                    Scroll banner from left to right.(use ncurses)\n");
  printf("  -Y, --Y                    Scroll banner from down to up(use ncurses)\n");
  printf("  -z, --z                    Scroll banenr with 'h', 'j', 'k', 'l' key.(use ncurses)\n");
#endif
}

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "");

  /* 変数宣言 */
  bool useAntialias = DEFAULT_USE_ANTIALIAS;      // アンチエイリアスを使うか否か
  char* chars = DEFAULT_CHARS;                    // ドットの表示に使うの
#ifdef HAVE_LIBNCURSES
  int delayTime = DEFAULT_DELAY;                  // スクロールディレイ
#endif
  char* filename = NULL;                          // 開くファイルの名前
  char* fontName = DEFAULT_FONT;                  // フォント名
#ifdef HAVE_LIBNCURSES
  int loopCount = DEFAULT_LOOP_COUNT;             // ループ回数
#endif
  int topMargin = DEFAULT_TOP_MARGIN;             // マージン上
  int rightMargin = DEFAULT_RIGHT_MARGIN;         // マージン右
  int bottomMargin = DEFAULT_BOTTOM_MARGIN;       // マージン下
  int leftMargin = DEFAULT_LEFT_MARGIN;           // マージン左
  double rotate = DEFAULT_ROTATE * PI / 180;      // フォントの角度
  double ptSize = DEFAULT_SIZE;                   // ポイントサイズ
  int width = DEFAULT_WIDTH;                      // <0:自動調整, 0:制限なし,n:n文字まで。
#ifdef HAVE_LIBNCURSES
  scrollDirection direction = DEFAULT_DIRECTION;  // スクロール方向
#endif

  std::string text;                               // 表示するテキスト

  /* 引数処理 */
  while(1) {
    static struct option longopts[] = {
      { "antialias", no_argument, NULL, 'a' },
      { "chars", required_argument, NULL, 'c' },
      { "font", required_argument, NULL, 'f' },
      { "help", no_argument, NULL, 'h' },
#ifdef HAVE_LIBNCURSES
      { "loop", required_argument, NULL, 'l' },
#endif
      { "margin", required_argument, NULL, 'm' },
      { "open", required_argument, NULL, 'o' },
      { "rotate", required_argument, NULL, 'r' },
      { "size", required_argument, NULL, 's' },
#ifdef HAVE_LIBNCURSES
      { "time", required_argument, NULL, 't' },
#endif
      { "version", no_argument, NULL, 'v' },
      { "width", required_argument, NULL, 'w' },
#ifdef HAVE_LIBNCURSES
      { "x", no_argument, NULL, 'x' },
      { "y", no_argument, NULL, 'y' },
      { "X", no_argument, NULL, 'X' },
      { "Y", no_argument, NULL, 'Y' },
      { "z", no_argument, NULL, 'z' },
#endif
      { 0, 0, 0, 0 }
    };

#ifdef HAVE_LIBNCURSES
    int c = getopt_long(argc, argv, "c:f:l:m:o:r:s:t:w:adhvxyXYz", longopts, NULL);
#else
    int c = getopt_long(argc, argv, "c:f:m:o:r:s:w:adhv", longopts, NULL);
#endif
    if(c == -1) {
      break;
    }

    switch(c) {
    case 'a':
      useAntialias = true;
      break;
    case 'c':
      useAntialias = true;
      chars = optarg;
      break;
    case 'f':
      fontName = optarg;
      break;
    case 'h':
      usage(argc, argv);
      exit(0);
#ifdef HAVE_LIBNCURSES
    case 'l':
      loopCount = atoi(optarg);
      break;
#endif
    case 'm':
      sscanf(optarg, "%d,%d,%d,%d", &topMargin, &rightMargin, &bottomMargin, &leftMargin);
      break;
    case 'o':
      filename = optarg;
      break;
    case 'r':
      rotate = atof(optarg) * PI / 180;
      break;
    case 's':
      ptSize = atof(optarg);
      break;
#ifdef HAVE_LIBNCURSES
    case 't':
      delayTime = atoi(optarg);
      break;
#endif
    case 'v':
      version();
      exit(0);
    case 'w':
      width = atoi(optarg);
      break;
#ifdef HAVE_LIBNCURSES
    case 'x':
      direction = sdLEFT;
      break;
    case 'y':
      direction = sdDOWN;
      break;
    case 'X':
      direction = sdRIGHT;
      break;
    case 'Y':
      direction = sdUP;
      break;
    case 'z':
      direction = sdMANUAL;
      break;
#endif
    default:
      usage(argc, argv);
      exit(1);
    }
  }

  // オプション以外 : 表示する文字列として利用
  if(filename) {
    std::ifstream ifs(filename);
    if(ifs.fail()) {
      exit(1);
      fprintf(stderr, "Could not open file %s\n", filename);
    }
    while(ifs.good()) {
      char buf[TEXT_STRING_BUF];
      ifs.get(buf, sizeof(buf), '\0');
      text += buf;
    }
    ifs.close();
  } else {
    if(optind < argc) {
      for(int i = optind; i < argc; i++) {
        text += argv[i];
        text += '\n';
      }
    } else {
      while(std::cin.good()) {
        char buf[TEXT_STRING_BUF];
        std::cin.get(buf, sizeof(buf), '\0');
        text += buf;
      }
      int newfd = open("/dev/tty", O_RDONLY);
      if(newfd < 0) {
        perror(NULL);
        exit(1);
      }
      if(dup2(newfd, STDIN_FILENO) < 0) {
        perror(NULL);
        exit(1);
      }
    }
  }
  /* 引数処理終了 */

  /* 範囲計算 */
  int brect[8];
  char* errMessage;
  if(useAntialias) {
    errMessage= gdImageStringTTF(NULL, brect, 0, fontName, ptSize, rotate, 0, 0, (char*)text.c_str());
  } else {
    errMessage= gdImageStringTTF(NULL, brect, -1, fontName, ptSize, rotate, 0, 0, (char*)text.c_str());
  }
  if(errMessage) {
    fprintf(stderr, "%s\n", errMessage);
    exit(1);
  }
  // 範囲
  int minX = min4(brect[0], brect[2], brect[4], brect[6]);
  int minY = min4(brect[1], brect[3], brect[5], brect[7]);
  int maxX = max4(brect[0], brect[2], brect[4], brect[6]);
  int maxY = max4(brect[1], brect[3], brect[5], brect[7]);

  /* イメージ作成 */
  gdImagePtr im = gdImageCreate(maxX - minX + leftMargin + rightMargin, maxY - minY + topMargin + bottomMargin);
  if(!im) {
    exit(1);
  }

  /* 色を確保 */
  gdImageColorAllocate(im, 0xff, 0xff, 0xff);
  int black = gdImageColorAllocate(im, 0x00, 0x00, 0x00);

  /* 文字列描画 */
  if(useAntialias) {
    errMessage = gdImageStringTTF(im, brect, black, fontName, ptSize, rotate, leftMargin - minX, topMargin - minY, (char*)text.c_str());
  } else {
    errMessage = gdImageStringTTF(im, brect, -black, fontName, ptSize, rotate, leftMargin - minX, topMargin - minY, (char*)text.c_str());
  }
  if(errMessage) {
    fprintf(stderr, "%s\n", errMessage);
    // イメージ破棄
    gdImageDestroy(im);
    exit(1);
  }

  /* width / height計算 */
#ifdef HAVE_LIBNCURSES
  if(direction != sdNONE) {
    width = 0;
  }
#endif
  if(width < 0) {
    // ioctlを利用した自動幅調整
    struct winsize ws;
    if(ioctl(1, TIOCGWINSZ, &ws) < 0) {
      width = 0;
    } else {
      width = ws.ws_col;
    }
  }
  if(width == 0) {
    width = maxX - minX + leftMargin + rightMargin;
  }
  int height = maxY - minY + topMargin + bottomMargin;

  /* テキスト化 */
#ifdef HAVE_LIBNCURSES
  if(direction == sdNONE) {
#endif
    /* スクロールしない */
    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        int yy = gdImageGetYvalueFormPixel(im, x, y);
        printf("%c", chars[ (int)((strlen(chars)-1) * yy / 255) ]);
      }
      printf("\n");
    }

#ifdef HAVE_LIBNCURSES
  } else {
    /* スクロールする */
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, false);
    keypad(stdscr, true);
    refresh();

    flushinp();
    WINDOW* pat = newpad(height, width);
    keypad(pat, true);
    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        int yy = gdImageGetYvalueFormPixel(im, x, y);
        mvwprintw(pat, y, x, "%c", chars[ (int)((strlen(chars)-1) * yy / 255) ]);
      }
    }

    int i = 0;
    do {
      switch(direction) {
      case sdNONE:
        break;
      case sdLEFT:
        for(int x = width; x > 0; x--) {
          pnoutrefresh(pat, 0, x, 0, 0, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        for(int x = 0; x < COLS; x++) {
          pnoutrefresh(pat, 0, 0, 0, x, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        break;

      case sdDOWN:
        for(int y = height; y > 0; y--) {
          pnoutrefresh(pat, y, 0, 0, 0, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        for(int y = 0; y < LINES; y++) {
          pnoutrefresh(pat, 0, 0, y, 0, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        break;

      case sdRIGHT:
        for(int x = COLS; x > 0; x--) {
          pnoutrefresh(pat, 0, 0, 0, x, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        for(int x = 0; x < width; x++) {
          pnoutrefresh(pat, 0, x, 0, 0, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        break;

      case sdUP:
        for(int y = LINES; y > 0; y--) {
          pnoutrefresh(pat, 0, 0, y, 0, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        for(int y = 0; y < height; y++) {
          pnoutrefresh(pat, y, 0, 0, 0, LINES - 1, COLS - 1);
          doupdate();
          usleep(delayTime);
        };
        break;

      case sdMANUAL:
        int x = 0;
        int y = 0;
        int key_in;
        bool repeat_flag = true;
        while(repeat_flag) {
          pnoutrefresh(pat, y, x, 0, 0, LINES - 1, COLS - 1);
          doupdate();
          key_in = wgetch(pat);
          switch(key_in) {
            /* move home/end */
          case 'g':
            y = 0;
            break;
          case 'G':
            y = height - LINES;
            break;
          case '^':
          case KEY_HOME:
            x = 0;
            break;
          case '$':
          case KEY_END:
            x = width - COLS;
            break;

            /* page up/down */
          case KEY_NPAGE:
          case ' ':
            y += LINES / 2;
            break;
          case KEY_PPAGE:
            y -= LINES / 2;
            break;

            /* arrow & h j k l */
          case 'h':
          case KEY_LEFT:
            x -= 2;
            break;
          case 'j':
          case KEY_DOWN:
            y += 1;
            break;
          case 'k':
          case KEY_UP:
            y -= 1;
            break;
          case 'l':
          case KEY_RIGHT:
            x += 2;
            break;

            /* H J K L : 1 screen move */
          case 'H':
            x -= COLS;
            break;
          case 'J':
          case KEY_ENTER:
            y += LINES;
            break;
          case 'K':
            y -= LINES;
            break;
          case 'L':
            x += COLS;
            break;

            /* quit */
          case 'q':
            repeat_flag = false;
            break;
          }
          if(x < 0) x = 0;
          if(y < 0) y = 0;
          if(x > width - COLS - 1) x = width - COLS - 1;
          if(y > height - LINES - 1) y = height - LINES - 1;
        }
      }
    } while(direction != sdMANUAL && (loopCount < 0 || i++ < loopCount));
    endwin();
  }
#endif

  // イメージ破棄
  gdImageDestroy(im);
}

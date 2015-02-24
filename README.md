# jabanner

## Waht is Jabanner

```
$ echo jabanner | jabanner
       ##            ##
       ###           ###
       ###           ###
       ###           ###
       ###           ###
       ###   #####   #######      #####   ## ####   ## ####     #####    ## ##
       ###  #######  ########    #######  ########  ########   #######   #####
       ### ###  ###  #### ####  ###  ###  #### ###  #### ###  ###  ###   #####
       ### ###  ###  ###   ###  ###  ###  ###   ##  ###   ##  ###   ###  ###
       ###     ####  ###   ###      ####  ###   ##  ###   ##  #########  ###
       ###  #######  ###   ###   #######  ###   ##  ###   ##  #########  ###
 ###   ### ########  ###   ###  ########  ###   ##  ###   ##  #########  ###
 ###   ##  ###   ##  ###   ###  ###   ##  ###   ##  ###   ##  ###        ###
 ###   ##  ##   ###  ###   ###  ##   ###  ###   ##  ###   ##  ###   ###  ###
 ########  ###  ###  #### ###   ###  ###  ###   ##  ###   ##  #### ###   ###
  #######  ########  ########   ########  ###   ##  ###   ##   #######   ###
   #####    #### ### ## ####     #### ### ##    ##  ##    ##    #####    ##
```

Advanced banner(1). Generate AA (ASCII Art) for given string with font file.
Require: libgd-devel

## Usage

```
$ jabanner --help
Usage: jabanner [Options] ... String ...

Print "banner" version of string.
ex) jabanner "foo bar baz" ... print "banner" in a line.
ex) jabanner foo bar baz ... print "banner" in 3 lines.

Mandatory arguments to long options are mandatory for short options.
  -a, --antialias            Use antialias.
  -c, --chars=STRING         Charactors that use with antialias.["#MND80Z7I?+=~:,. "]
  -f, --font=FILE            Font file.[/Library/Fonts/Hiragino Sans GB W3.otf]
  -h, --help                 Show this message.
  -l, --loop=NUMBER          Scroll banner NUMBER times.(negative value means infinity)[0]
  -m, --margin=NUMBERs       Set margin.(top,right,bottom,left)[0,0,0,0]
  -o, --open=FILE            Use FILE as String.
  -r, --rotate=NUMBER        Rotate "banner".(degree)[0]
  -s, --size=NUMBER          Font size(Pt)[8]
  -t, --time=NUMBER          Scroll delay.(micro seconds)[10000]
  -v, --version              Show version.
  -w, --width=NUMBER         Set Width.(<0:use terminal width,0:show all)[-1]
  -x, --x                    Scroll banner from right to left.(use ncurses)
  -y, --y                    Scroll banner from up to down.(use ncurses)
  -X, --X                    Scroll banner from left to right.(use ncurses)
  -Y, --Y                    Scroll banner from down to up(use ncurses)
  -z, --z                    Scroll banenr with 'h', 'j', 'k', 'l' key.(use ncurses)
```

## How to install

### Use HomeBrew
```console
$ brew tap takei-yuya/jabanner
$ brew install jabanner
```
### Build from source
```console
$ ./autogen.sh
$ ./configure # --enable-font=PATH_TO_YOUR_FAVORIT_FONT
$ make
# make install
```

---

Copyright (c) 2007- TAKEI Yuya <takei.yuya _at_ gmail.com>

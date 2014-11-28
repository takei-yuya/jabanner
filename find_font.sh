#!/usr/bin/env bash

function with_fontconfig()
{
  fc-list -f '%{file}\n' ':lang=ja'
  fc-list -f '%{file}\n'
}

function without_fontconfig()
{
  local IFS=$'\n'
  local -a font_dirs=(
    /Library/Fonts
    /System/Library/Fonts
    /usr/X11R6/lib/X11/fonts/
    /share/fonts
    /usr/share/fonts
    /usr/share/fonts/ja
    /usr/local/share/fonts
  )
  local -a preferred_fonts=(ipa VL- sazanami Hiragino Koz Osaka Ricty)
  local -a fonts=($(
    find "${font_dirs[@]}" \
      \( -iname '*.ttf' \
      -o -iname '*.otf' \
      -o -iname '*.dfont' \
      \)
    )
  )
  for pat in "${preferred_fonts[@]}"; do
    echo "${fonts[*]}" | grep "${pat}"
  done
  echo "${fonts[*]}" | grep '[^ -~]'
  echo "${fonts[*]}"
}

function find_fonts()
{
  with_fontconfig
  without_fontconfig
}

exec 2>/dev/null
find_fonts | head -n1

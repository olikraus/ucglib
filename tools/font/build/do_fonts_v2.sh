#!/bin/bash

# "execute do_combine.sh after executing this script"
# b0:t - transparent, b1:h - common height, b2:m - monospace+common height
# f - full font (32-255), r - reduced char set (32-127),  n - numeric (32, 42-58) 
# 2*128 = 256
# 3*128 = 384
# 4*128 = 512
# 5*128 = 640
# 6*128 = 768
# 7*128 = 896
# 8*128 = 1024
# 67*128 = 8576
# 68*128 = 8704
# 75*128 = 9600
# 76*128 = 9728
# 77*128 = 9856
# 78*128 = 9984
# 79*128 = 10112
# -l 67 -u 75   --> -m '8576-8703>0,9600-9727>128'
# -l 67 -u 75
#  -l 75 -b 32 -e 79 -m '9632-9679>32'
# -l 78 -u 79 -b 0 -e 255 --> -m '9984-10239>0'
#  -m '65-104>65' --> -m '65-104>65'
#  -m '32,42-58>42'

mkdir pixel
mkdir ttf


echo u8glib_4
../bdfconv/bdfconv -b 0 ../bdf/u8glib_4.bdf -n ucg_font_u8glib_4_tf -o ./pixel/ucg_font_u8glib_4_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/u8glib_4.bdf -n ucg_font_u8glib_4_tr -o ./pixel/ucg_font_u8glib_4_tr.c 

echo m2icon
../bdfconv/bdfconv -b 0  -m '65-105>65' ../bdf/m2icon_5.bdf -n ucg_font_m2icon_5 -o ./pixel/ucg_font_m2icon_5.c 
../bdfconv/bdfconv -b 0  -m '65-105>65'  ../bdf/m2icon_7.bdf -n ucg_font_m2icon_7 -o ./pixel/ucg_font_m2icon_7.c 
../bdfconv/bdfconv -b 0  -m '65-105>65'  ../bdf/m2icon_9.bdf -n ucg_font_m2icon_9 -o ./pixel/ucg_font_m2icon_9.c 

echo cursor
../bdfconv/bdfconv -b 0 -m '0-223>32' ../bdf/cursor.bdf -n ucg_font_cursor_tf -o ./pixel/ucg_font_cursor_tf.c 
../bdfconv/bdfconv -b 0 -m '0-80>32' ../bdf/cursorr.bdf -n ucg_font_cursor_tr -o ./pixel/ucg_font_cursor_tr.c 
echo cu12
../bdfconv/bdfconv -b 0 ../bdf/cu12.bdf -n ucg_font_cu12_tf -o ./pixel/ucg_font_cu12_tf.c  
../bdfconv/bdfconv -b 0 -m '8576-8703>0,9600-9727>128' ../bdf/cu12.bdf -n ucg_font_cu12_67_75 -o ./pixel/ucg_font_cu12_67_75.c  
../bdfconv/bdfconv -b 0 -m '9632-9679>32' ../bdf/cu12.bdf -n ucg_font_cu12_75 -o ./pixel/ucg_font_cu12_75.c  
echo micro
../bdfconv/bdfconv -b 0  ../bdf/micro.bdf -n ucg_font_micro_tf -o ./pixel/ucg_font_micro_tf.c  
echo "4x6"
../bdfconv/bdfconv -b 0  ../bdf/4x6.bdf -n ucg_font_4x6_tf -o ./pixel/ucg_font_4x6_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/4x6.bdf -n ucg_font_4x6_tr -o ./pixel/ucg_font_4x6_tr.c  
#../bdfconv/bdfconv -b 0  -m '32,42-58>42' ../bdf/4x6.bdf -n ucg_font_4x6n -o ./pixel/ucg_font_4x6n.c  
echo "5x7"
../bdfconv/bdfconv -b 0  ../bdf/5x7.bdf -n ucg_font_5x7_tf -o ./pixel/ucg_font_5x7_tf.c  
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/5x7.bdf -n ucg_font_5x7_tr -o ./pixel/ucg_font_5x7_tr.c  
echo "5x8"
../bdfconv/bdfconv -b 0  ../bdf/5x8.bdf -n ucg_font_5x8_tf -o ./pixel/ucg_font_5x8_tf.c  
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/5x8.bdf -n ucg_font_5x8_tr -o ./pixel/ucg_font_5x8_tr.c  
echo "6x10"
../bdfconv/bdfconv -b 0  ../bdf/6x10.bdf -n ucg_font_6x10_tf -o ./pixel/ucg_font_6x10_tf.c  
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/6x10.bdf -n ucg_font_6x10_tr -o ./pixel/ucg_font_6x10_tr.c  
echo "6x12"
../bdfconv/bdfconv -b 0  ../bdf/6x12.bdf -n ucg_font_6x12_tf -o ./pixel/ucg_font_6x12_tf.c  
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/6x12.bdf -n ucg_font_6x12_tr -o ./pixel/ucg_font_6x12_tr.c  
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/6x12.bdf -n ucg_font_6x12_67_75 -o ./pixel/ucg_font_6x12_67_75.c  
../bdfconv/bdfconv -b 0  -m '9632-9679>32' ../bdf/6x12.bdf -n ucg_font_6x12_75 -o ./pixel/ucg_font_6x12_75.c  
../bdfconv/bdfconv -b 0  -m '9984-10239>0' ../bdf/6x12.bdf -n ucg_font_6x12_78_79 -o ./pixel/ucg_font_6x12_78_79.c  
echo "6x13"
../bdfconv/bdfconv -b 0  ../bdf/6x13.bdf -n ucg_font_6x13_tf -o ./pixel/ucg_font_6x13_tf.c  
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/6x13.bdf -n ucg_font_6x13_tr -o ./pixel/ucg_font_6x13_tr.c  
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/6x13.bdf -n ucg_font_6x13_67_75 -o ./pixel/ucg_font_6x13_67_75.c  
#../bdfconv/bdfconv -b 0  -l 75 -b 32 -e 79 ../bdf/6x13.bdf -n ucg_font_6x13_75r -o ./pixel/ucg_font_6x13_75r.c  
../bdfconv/bdfconv -b 0  -m '9984-10239>0' ../bdf/6x13.bdf -n ucg_font_6x13_78_79 -o ./pixel/ucg_font_6x13_78_79.c  
../bdfconv/bdfconv -b 0  ../bdf/6x13B.bdf -n ucg_font_6x13B_tf -o ./pixel/ucg_font_6x13B_tf.c  
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/6x13B.bdf -n ucg_font_6x13B_tr -o ./pixel/ucg_font_6x13B_tr.c  
../bdfconv/bdfconv -b 0  ../bdf/6x13O.bdf -n ucg_font_6x13O_tf -o ./pixel/ucg_font_6x13O_tf.c  
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/6x13O.bdf -n ucg_font_6x13O_tr -o ./pixel/ucg_font_6x13O_tr.c  
echo "7x13"
../bdfconv/bdfconv -b 0  ../bdf/7x13.bdf -n ucg_font_7x13_tf -o ./pixel/ucg_font_7x13_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/7x13.bdf -n ucg_font_7x13_tr -o ./pixel/ucg_font_7x13_tr.c 
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/7x13.bdf -n ucg_font_7x13_67_75 -o ./pixel/ucg_font_7x13_67_75.c 
#../bdfconv/bdfconv -b 0  -l 75 -b 32 -e 79 ../bdf/7x13.bdf -n ucg_font_7x13_75r -o ./pixel/ucg_font_7x13_75r.c 
../bdfconv/bdfconv -b 0  -m '9984-10239>0' ../bdf/7x13.bdf -n ucg_font_7x13_78_79 -o ./pixel/ucg_font_7x13_78_79.c
../bdfconv/bdfconv -b 0  ../bdf/7x13B.bdf -n ucg_font_7x13B_tf -o ./pixel/ucg_font_7x13B_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/7x13B.bdf -n ucg_font_7x13B_tr -o ./pixel/ucg_font_7x13B_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/7x13O.bdf -n ucg_font_7x13O_tf -o ./pixel/ucg_font_7x13O_tf.c
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/7x13O.bdf -n ucg_font_7x13O_tr -o ./pixel/ucg_font_7x13O_tr.c 
echo "7x14"
../bdfconv/bdfconv -b 0  ../bdf/7x14.bdf -n ucg_font_7x14_tf -o ./pixel/ucg_font_7x14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/7x14.bdf -n ucg_font_7x14_tr -o ./pixel/ucg_font_7x14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/7x14B.bdf -n ucg_font_7x14B_tf -o ./pixel/ucg_font_7x14B_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/7x14B.bdf -n ucg_font_7x14B_tr -o ./pixel/ucg_font_7x14B_tr.c 
echo "8x13"
../bdfconv/bdfconv -b 0  ../bdf/8x13.bdf -n ucg_font_8x13_tf -o ./pixel/ucg_font_8x13_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/8x13.bdf -n ucg_font_8x13_tr -o ./pixel/ucg_font_8x13_tr.c 
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/8x13.bdf -n ucg_font_8x13_67_75 -o ./pixel/ucg_font_8x13_67_75.c 
#../bdfconv/bdfconv -b 0  -l 75 -b 32 -e 79 ../bdf/8x13.bdf -n ucg_font_8x13_75 -o ./pixel/ucg_font_8x13_75.c 
../bdfconv/bdfconv -b 0  ../bdf/8x13B.bdf -n ucg_font_8x13B_tf -o ./pixel/ucg_font_8x13B_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/8x13B.bdf -n ucg_font_8x13B_tr -o ./pixel/ucg_font_8x13B_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/8x13O.bdf -n ucg_font_8x13O_tf -o ./pixel/ucg_font_8x13O_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/8x13O.bdf -n ucg_font_8x13O_tr -o ./pixel/ucg_font_8x13O_tr.c 
echo "9x15"
../bdfconv/bdfconv -b 0  ../bdf/9x15.bdf -n ucg_font_9x15_tf -o ./pixel/ucg_font_9x15_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/9x15.bdf -n ucg_font_9x15_tr -o ./pixel/ucg_font_9x15_tr.c 
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/9x15.bdf -n ucg_font_9x15_67_75 -o ./pixel/ucg_font_9x15_67_75.c 
#../bdfconv/bdfconv -b 0  -l 75 -b 32 -e 79 ../bdf/9x15.bdf -n ucg_font_9x15_75 -o ./pixel/ucg_font_9x15_75.c 
../bdfconv/bdfconv -b 0  -m '9984-10239>0' ../bdf/9x15.bdf -n ucg_font_9x15_78_79 -o ./pixel/ucg_font_9x15_78_79.c 
../bdfconv/bdfconv -b 0  ../bdf/9x15B.bdf -n ucg_font_9x15B_tf -o ./pixel/ucg_font_9x15B_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/9x15B.bdf -n ucg_font_9x15B_tr -o ./pixel/ucg_font_9x15B_tr.c 
echo "9x18"
../bdfconv/bdfconv -b 0  ../bdf/9x18.bdf -n ucg_font_9x18_tf -o ./pixel/ucg_font_9x18_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/9x18.bdf -n ucg_font_9x18_tr -o ./pixel/ucg_font_9x18_tr.c 
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/9x18.bdf -n ucg_font_9x18_67_75 -o ./pixel/ucg_font_9x18_67_75.c 
#../bdfconv/bdfconv -b 0  -l 75 -b 32 -e 79  ../bdf/9x18.bdf -n ucg_font_9x18_75r -o ./pixel/ucg_font_9x18_75r.c 
../bdfconv/bdfconv -b 0  -m '9984-10239>0' ../bdf/9x18.bdf -n ucg_font_9x18_78_79 -o ./pixel/ucg_font_9x18_78_79.c 
../bdfconv/bdfconv -b 0  ../bdf/9x18B.bdf -n ucg_font_9x18B_tf -o ./pixel/ucg_font_9x18B_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/9x18B.bdf -n ucg_font_9x18B_tr -o ./pixel/ucg_font_9x18B_tr.c 
echo "10x20"
../bdfconv/bdfconv -b 0  ../bdf/10x20.bdf -n ucg_font_10x20_tf -o ./pixel/ucg_font_10x20_tf.c 
../bdfconv/bdfconv -b 0  -m '32-127>32' ../bdf/10x20.bdf -n ucg_font_10x20_tr -o ./pixel/ucg_font_10x20_tr.c 
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/10x20.bdf -n ucg_font_10x20_67_75 -o ./pixel/ucg_font_10x20_67_75.c 
#../bdfconv/bdfconv -b 0  -l 75  -b 32 -e 79 ../bdf/10x20.bdf -n ucg_font_10x20_75r -o ./pixel/ucg_font_10x20_75r.c 
../bdfconv/bdfconv -b 0  -m '9984-10239>0' ../bdf/10x20.bdf -n ucg_font_10x20_78_79 -o ./pixel/ucg_font_10x20_78_79.c 
echo "profont"
../bdfconv/bdfconv -b 2  ../bdf/profont10.bdf -n ucg_font_profont10_mf -o ./pixel/ucg_font_profont10_mf.c 
../bdfconv/bdfconv -b 2  ../bdf/profont11.bdf -n ucg_font_profont11_mf -o ./pixel/ucg_font_profont11_mf.c 
../bdfconv/bdfconv -b 2  ../bdf/profont12.bdf -n ucg_font_profont12_mf -o ./pixel/ucg_font_profont12_mf.c 
../bdfconv/bdfconv -b 2  ../bdf/profont15.bdf -n ucg_font_profont15_mf -o ./pixel/ucg_font_profont15_mf.c 
../bdfconv/bdfconv -b 2  ../bdf/profont17.bdf -n ucg_font_profont17_mf -o ./pixel/ucg_font_profont17_mf.c 
../bdfconv/bdfconv -b 2  ../bdf/profont22.bdf -n ucg_font_profont22_mf -o ./pixel/ucg_font_profont22_mf.c 
../bdfconv/bdfconv -b 2  ../bdf/profont29.bdf -n ucg_font_profont29_mf -o ./pixel/ucg_font_profont29_mf.c 

../bdfconv/bdfconv -b 2  -m '32-127>32' ../bdf/profont10.bdf -n ucg_font_profont10_mr -o ./pixel/ucg_font_profont10_mr.c 
../bdfconv/bdfconv -b 2  -m '32-127>32' ../bdf/profont11.bdf -n ucg_font_profont11_mr -o ./pixel/ucg_font_profont11_mr.c 
../bdfconv/bdfconv -b 2  -m '32-127>32' ../bdf/profont12.bdf -n ucg_font_profont12_mr -o ./pixel/ucg_font_profont12_mr.c 
../bdfconv/bdfconv -b 2  -m '32-127>32' ../bdf/profont15.bdf -n ucg_font_profont15_mr -o ./pixel/ucg_font_profont15_mr.c 
../bdfconv/bdfconv -b 2  -m '32-127>32' ../bdf/profont17.bdf -n ucg_font_profont17_mr -o ./pixel/ucg_font_profont17_mr.c 
../bdfconv/bdfconv -b 2  -m '32-127>32' ../bdf/profont22.bdf -n ucg_font_profont22_mr -o ./pixel/ucg_font_profont22_mr.c 
../bdfconv/bdfconv -b 2  -m '32-127>32' ../bdf/profont29.bdf -n ucg_font_profont29_mr -o ./pixel/ucg_font_profont29_mr.c 

../bdfconv/bdfconv -b 2  -m '32,42-58>42' ../bdf/profont22.bdf -n ucg_font_profont22_mn -o ./pixel/ucg_font_profont22_mn.c 
../bdfconv/bdfconv -b 2  -m '32,42-58>42' ../bdf/profont29.bdf -n ucg_font_profont29_mn -o ./pixel/ucg_font_profont29_mn.c 

echo "unifont"

../bdfconv/bdfconv -b 2  -m '32-255,~127-159'  ../bdf/unifont.bdf -n ucg_font_unifont_mf -o ./pixel/ucg_font_unifont_mf.c 
../bdfconv/bdfconv -b 2  -m '32-126'  ../bdf/unifont.bdf -n ucg_font_unifont_mr -o ./pixel/ucg_font_unifont_mr.c 

../bdfconv/bdfconv -b 0  -m '32-255,~127-159'  ../bdf/unifont.bdf -n ucg_font_unifont_tf -o ./pixel/ucg_font_unifont_tf.c 
../bdfconv/bdfconv -b 0  -m '32-126'  ../bdf/unifont.bdf -n ucg_font_unifont_tr -o ./pixel/ucg_font_unifont_tr.c 

../bdfconv/bdfconv -b 0  -m '256-511>0'  ../bdf/unifont.bdf -n ucg_font_unifont_2_3 -o ./pixel/ucg_font_unifont_2_3.c 
../bdfconv/bdfconv -b 0  -m '512-767>0'  ../bdf/unifont.bdf -n ucg_font_unifont_4_5 -o ./pixel/ucg_font_unifont_4_5.c 
../bdfconv/bdfconv -b 0  -m '2304-2559>0' ../bdf/unifont.bdf -n ucg_font_unifont_18_19 -o ./pixel/ucg_font_unifont_18_19.c 
../bdfconv/bdfconv -b 0  -m '72*128-73*128+127>0'-l 72 -u 73 -b 0 -e 255 ../bdf/unifont.bdf -n ucg_font_unifont_72_73 -o ./pixel/ucg_font_unifont_72_73.c 
../bdfconv/bdfconv -b 0  -m '8576-8703>0,9600-9727>128' ../bdf/unifont.bdf -n ucg_font_unifont_67_75 -o ./pixel/ucg_font_unifont_67_75.c 
#../bdfconv/bdfconv -b 0  -l 75 -b 32 -e 79 ../bdf/unifont.bdf -n ucg_font_unifont_75r -o ./pixel/ucg_font_unifont_75r.c 
../bdfconv/bdfconv -b 0  -m '9984-10239>0' ../bdf/unifont.bdf -n ucg_font_unifont_78_79 -o ./pixel/ucg_font_unifont_78_79.c 
#../bdfconv/bdfconv -b 0  -l 86 -u 87 -s 32 -b 32 -e 116 ../bdf/unifont.bdf -n ucg_font_unifont_86 -o ./pixel/ucg_font_unifont_86.c 
#../bdfconv/bdfconv -b 0  -l 77 -u 87 -s 32 -b 32 -e 99 ../bdf/unifont.bdf -n ucg_font_unifont_77 -o ./pixel/ucg_font_unifont_77.c 
#../bdfconv/bdfconv -b 0  -l 76 -u 87 -s 32 -b 32 -e 159  ../bdf/unifont.bdf -n ucg_font_unifont_76 -o ./pixel/ucg_font_unifont_76.c 
../bdfconv/bdfconv -b 0  -m '1024-1279>0' ../bdf/unifont.bdf -n ucg_font_unifont_8_9 -o ./pixel/ucg_font_unifont_8_9.c 
../bdfconv/bdfconv -b 0  -m '0-127>0,1024-1151>128' ../bdf/unifont.bdf -n ucg_font_unifont_0_8 -o ./pixel/ucg_font_unifont_0_8.c 
../bdfconv/bdfconv -b 0  -m '1536-1791>0' ../bdf/unifont.bdf -n ucg_font_unifont_12_13 -o ./pixel/ucg_font_unifont_12_13.c 

echo "adobe courB 08"
../bdfconv/bdfconv -b 0  ../bdf/courB08.bdf -n ucg_font_courB08_tf -o ./pixel/ucg_font_courb08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courB08.bdf -n ucg_font_courB08_tr -o ./pixel/ucg_font_courb08_tr.c 
echo "adobe courB 10"
../bdfconv/bdfconv -b 0  ../bdf/courB10.bdf -n ucg_font_courB10_tf -o ./pixel/ucg_font_courb10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courB10.bdf -n ucg_font_courB10_tr -o ./pixel/ucg_font_courb10_tr.c 
echo "adobe courB 12"
../bdfconv/bdfconv -b 0  ../bdf/courB12.bdf -n ucg_font_courB12_tf -o ./pixel/ucg_font_courb12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courB12.bdf -n ucg_font_courB12_tr -o ./pixel/ucg_font_courb12_tr.c 
echo "adobe courB 14"
../bdfconv/bdfconv -b 0  ../bdf/courB14.bdf -n ucg_font_courB14_tf -o ./pixel/ucg_font_courb14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courB14.bdf -n ucg_font_courB14_tr -o ./pixel/ucg_font_courb14_tr.c 
echo "adobe courB 18"
../bdfconv/bdfconv -b 0  ../bdf/courB18.bdf -n ucg_font_courB18_tf -o ./pixel/ucg_font_courb18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courB18.bdf -n ucg_font_courB18_tr -o ./pixel/ucg_font_courb18_tr.c 
../bdfconv/bdfconv -b 0   -m '42-58>42,32' ../bdf/courB18.bdf -n ucg_font_courB18_tn -o ./pixel/ucg_font_courb18_tn.c 
echo "adobe courB 24"
../bdfconv/bdfconv -b 0  ../bdf/courB24.bdf -n ucg_font_courB24_tf -o ./pixel/ucg_font_courb24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courB24.bdf -n ucg_font_courB24_tr -o ./pixel/ucg_font_courb24_tr.c 
../bdfconv/bdfconv -b 0   -m '42-58>42,32' ../bdf/courB24.bdf -n ucg_font_courB24_tn -o ./pixel/ucg_font_courb24_tn.c 

echo "adobe courR"
../bdfconv/bdfconv -b 0  ../bdf/courR08.bdf -n ucg_font_courR08_tf -o ./pixel/ucg_font_courr08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courR08.bdf -n ucg_font_courR08_tr -o ./pixel/ucg_font_courr08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/courR10.bdf -n ucg_font_courR10_tf -o ./pixel/ucg_font_courr10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courR10.bdf -n ucg_font_courR10_tr -o ./pixel/ucg_font_courr10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/courR12.bdf -n ucg_font_courR12_tf -o ./pixel/ucg_font_courr12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courR12.bdf -n ucg_font_courR12_tr -o ./pixel/ucg_font_courr12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/courR14.bdf -n ucg_font_courR14_tf -o ./pixel/ucg_font_courr14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courR14.bdf -n ucg_font_courR14_tr -o ./pixel/ucg_font_courr14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/courR18.bdf -n ucg_font_courR18_tf -o ./pixel/ucg_font_courr18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courR18.bdf -n ucg_font_courR18_tr -o ./pixel/ucg_font_courr18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/courR24.bdf -n ucg_font_courR24_tf -o ./pixel/ucg_font_courr24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/courR24.bdf -n ucg_font_courR24_tr -o ./pixel/ucg_font_courr24_tr.c 
../bdfconv/bdfconv -b 0   -m '42-58>42,32' ../bdf/courR24.bdf -n ucg_font_courR24_tn -o ./pixel/ucg_font_courr24_tn.c 

echo "adobe helvB"
../bdfconv/bdfconv -b 0  ../bdf/helvB08.bdf -n ucg_font_helvB08_tf -o ./pixel/ucg_font_helvb08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvB08.bdf -n ucg_font_helvB08_tr -o ./pixel/ucg_font_helvb08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvB10.bdf -n ucg_font_helvB10_tf -o ./pixel/ucg_font_helvb10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvB10.bdf -n ucg_font_helvB10_tr -o ./pixel/ucg_font_helvb10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvB12.bdf -n ucg_font_helvB12_tf -o ./pixel/ucg_font_helvb12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvB12.bdf -n ucg_font_helvB12_tr -o ./pixel/ucg_font_helvb12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvB14.bdf -n ucg_font_helvB14_tf -o ./pixel/ucg_font_helvb14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvB14.bdf -n ucg_font_helvB14_tr -o ./pixel/ucg_font_helvb14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvB18.bdf -n ucg_font_helvB18_tf -o ./pixel/ucg_font_helvb18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvB18.bdf -n ucg_font_helvB18_tr -o ./pixel/ucg_font_helvb18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvB24.bdf -n ucg_font_helvB24_tf -o ./pixel/ucg_font_helvb24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvB24.bdf -n ucg_font_helvB24_tr -o ./pixel/ucg_font_helvb24_tr.c 
../bdfconv/bdfconv -b 0   -b 42 -e 58  ../bdf/helvB24.bdf -n ucg_font_helvB24_tn -o ./pixel/ucg_font_helvb24_tn.c 

echo "adobe helvR"
../bdfconv/bdfconv -b 0  ../bdf/helvR08.bdf -n ucg_font_helvR08_tf -o ./pixel/ucg_font_helvr08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvR08.bdf -n ucg_font_helvR08_tr -o ./pixel/ucg_font_helvr08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvR10.bdf -n ucg_font_helvR10_tf -o ./pixel/ucg_font_helvr10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvR10.bdf -n ucg_font_helvR10_tr -o ./pixel/ucg_font_helvr10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvR12.bdf -n ucg_font_helvR12_tf -o ./pixel/ucg_font_helvr12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvR12.bdf -n ucg_font_helvR12_tr -o ./pixel/ucg_font_helvr12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvR14.bdf -n ucg_font_helvR14_tf -o ./pixel/ucg_font_helvr14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvR14.bdf -n ucg_font_helvR14_tr -o ./pixel/ucg_font_helvr14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvR18.bdf -n ucg_font_helvR18_tf -o ./pixel/ucg_font_helvr18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvR18.bdf -n ucg_font_helvR18_tr -o ./pixel/ucg_font_helvr18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/helvR24.bdf -n ucg_font_helvR24_tf -o ./pixel/ucg_font_helvr24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/helvR24.bdf -n ucg_font_helvR24_tr -o ./pixel/ucg_font_helvr24_tr.c 
../bdfconv/bdfconv -b 0   -b 42 -e 58  ../bdf/helvR24.bdf -n ucg_font_helvR24_tn -o ./pixel/ucg_font_helvr24_tn.c 

echo "adobe ncenB b0"
../bdfconv/bdfconv -b 0  ../bdf/ncenB08.bdf -n ucg_font_ncenB08_tf -o ./pixel/ucg_font_ncenb08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenB08.bdf -n ucg_font_ncenB08_tr -o ./pixel/ucg_font_ncenb08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenB10.bdf -n ucg_font_ncenB10_tf -o ./pixel/ucg_font_ncenb10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenB10.bdf -n ucg_font_ncenB10_tr -o ./pixel/ucg_font_ncenb10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenB12.bdf -n ucg_font_ncenB12_tf -o ./pixel/ucg_font_ncenb12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenB12.bdf -n ucg_font_ncenB12_tr -o ./pixel/ucg_font_ncenb12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenB14.bdf -n ucg_font_ncenB14_tf -o ./pixel/ucg_font_ncenb14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenB14.bdf -n ucg_font_ncenB14_tr -o ./pixel/ucg_font_ncenb14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenB18.bdf -n ucg_font_ncenB18_tf -o ./pixel/ucg_font_ncenb18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenB18.bdf -n ucg_font_ncenB18_tr -o ./pixel/ucg_font_ncenb18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenB24.bdf -n ucg_font_ncenB24_tf -o ./pixel/ucg_font_ncenb24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenB24.bdf -n ucg_font_ncenB24_tr -o ./pixel/ucg_font_ncenb24_tr.c 
../bdfconv/bdfconv -b 0   -b 42 -e 58  ../bdf/ncenB24.bdf -n ucg_font_ncenB24_tn -o ./pixel/ucg_font_ncenb24_tn.c 

echo "adobe ncenB b1"
../bdfconv/bdfconv -b 1  ../bdf/ncenB08.bdf -n ucg_font_ncenB08_hf -o ./pixel/ucg_font_ncenb08_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenB08.bdf -n ucg_font_ncenB08_hr -o ./pixel/ucg_font_ncenb08_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenB10.bdf -n ucg_font_ncenB10_hf -o ./pixel/ucg_font_ncenb10_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenB10.bdf -n ucg_font_ncenB10_hr -o ./pixel/ucg_font_ncenb10_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenB12.bdf -n ucg_font_ncenB12_hf -o ./pixel/ucg_font_ncenb12_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenB12.bdf -n ucg_font_ncenB12_hr -o ./pixel/ucg_font_ncenb12_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenB14.bdf -n ucg_font_ncenB14_hf -o ./pixel/ucg_font_ncenb14_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenB14.bdf -n ucg_font_ncenB14_hr -o ./pixel/ucg_font_ncenb14_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenB18.bdf -n ucg_font_ncenB18_hf -o ./pixel/ucg_font_ncenb18_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenB18.bdf -n ucg_font_ncenB18_hr -o ./pixel/ucg_font_ncenb18_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenB24.bdf -n ucg_font_ncenB24_hf -o ./pixel/ucg_font_ncenb24_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenB24.bdf -n ucg_font_ncenB24_hr -o ./pixel/ucg_font_ncenb24_hr.c 
../bdfconv/bdfconv -b 1   -b 42 -e 58  ../bdf/ncenB24.bdf -n ucg_font_ncenB24_hn -o ./pixel/ucg_font_ncenb24_hn.c 

echo "adobe ncenR b0"
../bdfconv/bdfconv -b 0  ../bdf/ncenR08.bdf -n ucg_font_ncenR08_tf -o ./pixel/ucg_font_ncenr08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenR08.bdf -n ucg_font_ncenR08_tr -o ./pixel/ucg_font_ncenr08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenR10.bdf -n ucg_font_ncenR10_tf -o ./pixel/ucg_font_ncenr10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenR10.bdf -n ucg_font_ncenR10_tr -o ./pixel/ucg_font_ncenr10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenR12.bdf -n ucg_font_ncenR12_tf -o ./pixel/ucg_font_ncenr12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenR12.bdf -n ucg_font_ncenR12_tr -o ./pixel/ucg_font_ncenr12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenR14.bdf -n ucg_font_ncenR14_tf -o ./pixel/ucg_font_ncenr14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenR14.bdf -n ucg_font_ncenR14_tr -o ./pixel/ucg_font_ncenr14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenR18.bdf -n ucg_font_ncenR18_tf -o ./pixel/ucg_font_ncenr18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenR18.bdf -n ucg_font_ncenR18_tr -o ./pixel/ucg_font_ncenr18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/ncenR24.bdf -n ucg_font_ncenR24_tf -o ./pixel/ucg_font_ncenr24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/ncenR24.bdf -n ucg_font_ncenR24_tr -o ./pixel/ucg_font_ncenr24_tr.c 
../bdfconv/bdfconv -b 0   -b 42 -e 58  ../bdf/ncenR24.bdf -n ucg_font_ncenR24_tn -o ./pixel/ucg_font_ncenr24_tn.c 

echo "adobe ncenR b1"
../bdfconv/bdfconv -b 1  ../bdf/ncenR08.bdf -n ucg_font_ncenR08_hf -o ./pixel/ucg_font_ncenr08_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenR08.bdf -n ucg_font_ncenR08_hr -o ./pixel/ucg_font_ncenr08_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenR10.bdf -n ucg_font_ncenR10_hf -o ./pixel/ucg_font_ncenr10_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenR10.bdf -n ucg_font_ncenR10_hr -o ./pixel/ucg_font_ncenr10_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenR12.bdf -n ucg_font_ncenR12_hf -o ./pixel/ucg_font_ncenr12_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenR12.bdf -n ucg_font_ncenR12_hr -o ./pixel/ucg_font_ncenr12_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenR14.bdf -n ucg_font_ncenR14_hf -o ./pixel/ucg_font_ncenr14_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenR14.bdf -n ucg_font_ncenR14_hr -o ./pixel/ucg_font_ncenr14_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenR18.bdf -n ucg_font_ncenR18_hf -o ./pixel/ucg_font_ncenr18_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenR18.bdf -n ucg_font_ncenR18_hr -o ./pixel/ucg_font_ncenr18_hr.c 
../bdfconv/bdfconv -b 1  ../bdf/ncenR24.bdf -n ucg_font_ncenR24_hf -o ./pixel/ucg_font_ncenr24_hf.c 
../bdfconv/bdfconv -b 1   -m '32-127>32' ../bdf/ncenR24.bdf -n ucg_font_ncenR24_hr -o ./pixel/ucg_font_ncenr24_hr.c 
../bdfconv/bdfconv -b 1   -b 42 -e 58  ../bdf/ncenR24.bdf -n ucg_font_ncenR24_hn -o ./pixel/ucg_font_ncenr24_hn.c 


echo "adobe timB"
../bdfconv/bdfconv -b 0  ../bdf/timB08.bdf -n ucg_font_timB08_tf -o ./pixel/ucg_font_timb08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timB08.bdf -n ucg_font_timB08_tr -o ./pixel/ucg_font_timb08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timB10.bdf -n ucg_font_timB10_tf -o ./pixel/ucg_font_timb10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timB10.bdf -n ucg_font_timB10_tr -o ./pixel/ucg_font_timb10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timB12.bdf -n ucg_font_timB12_tf -o ./pixel/ucg_font_timb12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timB12.bdf -n ucg_font_timB12_tr -o ./pixel/ucg_font_timb12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timB14.bdf -n ucg_font_timB14_tf -o ./pixel/ucg_font_timb14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timB14.bdf -n ucg_font_timB14_tr -o ./pixel/ucg_font_timb14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timB18.bdf -n ucg_font_timB18_tf -o ./pixel/ucg_font_timb18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timB18.bdf -n ucg_font_timB18_tr -o ./pixel/ucg_font_timb18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timB24.bdf -n ucg_font_timB24_tf -o ./pixel/ucg_font_timb24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timB24.bdf -n ucg_font_timB24_tr -o ./pixel/ucg_font_timb24_tr.c 
../bdfconv/bdfconv -b 0   -b 42 -e 58  ../bdf/timB24.bdf -n ucg_font_timB24_tn -o ./pixel/ucg_font_timb24_tn.c 

echo "adobe timR"
../bdfconv/bdfconv -b 0  ../bdf/timR08.bdf -n ucg_font_timR08_tf -o ./pixel/ucg_font_timr08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timR08.bdf -n ucg_font_timR08_tr -o ./pixel/ucg_font_timr08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timR10.bdf -n ucg_font_timR10_tf -o ./pixel/ucg_font_timr10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timR10.bdf -n ucg_font_timR10_tr -o ./pixel/ucg_font_timr10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timR12.bdf -n ucg_font_timR12_tf -o ./pixel/ucg_font_timr12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timR12.bdf -n ucg_font_timR12_tr -o ./pixel/ucg_font_timr12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timR14.bdf -n ucg_font_timR14_tf -o ./pixel/ucg_font_timr14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timR14.bdf -n ucg_font_timR14_tr -o ./pixel/ucg_font_timr14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timR18.bdf -n ucg_font_timR18_tf -o ./pixel/ucg_font_timr18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timR18.bdf -n ucg_font_timR18_tr -o ./pixel/ucg_font_timr18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/timR24.bdf -n ucg_font_timR24_tf -o ./pixel/ucg_font_timr24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/timR24.bdf -n ucg_font_timR24_tr -o ./pixel/ucg_font_timr24_tr.c 
../bdfconv/bdfconv -b 0   -b 42 -e 58  ../bdf/timR24.bdf -n ucg_font_timR24_tn -o ./pixel/ucg_font_timr24_tn.c 

echo "adobe symb"
../bdfconv/bdfconv -b 0  ../bdf/symb08.bdf -n ucg_font_symb08_tf -o ./pixel/ucg_font_symb08_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/symb08.bdf -n ucg_font_symb08_tr -o ./pixel/ucg_font_symb08_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/symb10.bdf -n ucg_font_symb10_tf -o ./pixel/ucg_font_symb10_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/symb10.bdf -n ucg_font_symb10_tr -o ./pixel/ucg_font_symb10_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/symb12.bdf -n ucg_font_symb12_tf -o ./pixel/ucg_font_symb12_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/symb12.bdf -n ucg_font_symb12_tr -o ./pixel/ucg_font_symb12_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/symb14.bdf -n ucg_font_symb14_tf -o ./pixel/ucg_font_symb14_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/symb14.bdf -n ucg_font_symb14_tr -o ./pixel/ucg_font_symb14_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/symb18.bdf -n ucg_font_symb18_tf -o ./pixel/ucg_font_symb18_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/symb18.bdf -n ucg_font_symb18_tr -o ./pixel/ucg_font_symb18_tr.c 
../bdfconv/bdfconv -b 0  ../bdf/symb24.bdf -n ucg_font_symb24_tf -o ./pixel/ucg_font_symb24_tf.c 
../bdfconv/bdfconv -b 0   -m '32-127>32' ../bdf/symb24.bdf -n ucg_font_symb24_tr -o ./pixel/ucg_font_symb24_tr.c 


echo "contributed"
../bdfconv/bdfconv -b 0   -m '32-127>32'  ../bdf/freedoomr25n.bdf -n ucg_font_freedoomr25_tn -o ./pixel/ucg_font_freedoomr25_tn.c 
../bdfconv/bdfconv -b 0   -m '32-127>32'  ../bdf/freedoomr10r.bdf -n ucg_font_freedoomr10_tr -o ./pixel/ucg_font_freedoomr10_tr.c 


echo "fontstruct"
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/p01type.ttf p01type
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/lucasfont_alternate.ttf lucasfont_alternate
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/chikita.ttf chikita
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/pixelle_micro.ttf pixelle_micro
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/trixel_square.ttf trixel_square
./do_fontsize_pixel_v2.sh 16 ../ttf/pixel/robot_de_niro.ttf robot_de_niro
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/baby.ttf baby
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/blipfest_07.ttf blipfest_07

echo "04B"
./do_fontsize_pixel_f1_v2.sh 8 ../ttf/pixel/04B_03B_.TTF 04b_03b 
./do_fontsize_pixel_f1_v2.sh 8 ../ttf/pixel/04B_03__.TTF 04b_03 
./do_fontsize_pixel_f1_v2.sh 8 ../ttf/pixel/04B_24__.TTF 04b_24 

echo "orgdot"
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/TEACPSS_.TTF tpss 
./do_fontsize_pixel_v2.sh 8 ../ttf/pixel/TEACPSSB.TTF tpssb 
./do_fontsize_pixel_f1_v2.sh 8 ../ttf/pixel/ORG_V01_.TTF orgv01 
./do_fontsize_pixel_f1_v2.sh 8 ../ttf/pixel/FIXED_V0.TTF fixed_v0 



echo "various ttf"

#./do_fontsize.sh 15 ../ttf/GenBasR.ttf gdr9
#./do_fontsize.sh 17 ../ttf/GenBasR.ttf gdr10
#./do_fontsize.sh 18 ../ttf/GenBasR.ttf gdr11
#./do_fontsize.sh 19 ../ttf/GenBasR.ttf gdr12
#./do_fontsize.sh 23 ../ttf/GenBasR.ttf gdr14
#./do_fontsize.sh 27 ../ttf/GenBasR.ttf gdr17
#./do_fontsize.sh 32 ../ttf/GenBasR.ttf gdr20
#./do_fontsize.sh 40 ../ttf/GenBasR.ttf gdr25
#./do_fontsize.sh 48 ../ttf/GenBasR.ttf gdr30
  
#./do_fontsize.sh 18 ../ttf/GenBasB.ttf gdb11
#./do_fontsize.sh 19 ../ttf/GenBasB.ttf gdb12
#./do_fontsize.sh 23 ../ttf/GenBasB.ttf gdb14
#./do_fontsize.sh 27 ../ttf/GenBasB.ttf gdb17
#./do_fontsize.sh 32 ../ttf/GenBasB.ttf gdb20
#./do_fontsize.sh 40 ../ttf/GenBasB.ttf gdb25
#./do_fontsize.sh 48 ../ttf/GenBasB.ttf gdb30

./do_fontsize_a_v2.sh 16 ../ttf/fu/FreeUniversal-Bold.ttf fub11
./do_fontsize_a_v2.sh 20 ../ttf/fu/FreeUniversal-Bold.ttf fub14
./do_fontsize_a_v2.sh 23 ../ttf/fu/FreeUniversal-Bold.ttf fub17
./do_fontsize_a_v2.sh 27 ../ttf/fu/FreeUniversal-Bold.ttf fub20
./do_fontsize_a_v2.sh 34 ../ttf/fu/FreeUniversal-Bold.ttf fub25
./do_fontsize_a_v2.sh 40 ../ttf/fu/FreeUniversal-Bold.ttf fub30
./do_fontsize_a_n_v2.sh 49 ../ttf/fu/FreeUniversal-Bold.ttf fub35
./do_fontsize_a_n_v2.sh 58 ../ttf/fu/FreeUniversal-Bold.ttf fub42
./do_fontsize_a_n_v2.sh 68 ../ttf/fu/FreeUniversal-Bold.ttf fub49
  
./do_fontsize_a_v2.sh 15 ../ttf/fu/FreeUniversal-Regular.ttf fur11
./do_fontsize_a_v2.sh 19 ../ttf/fu/FreeUniversal-Regular.ttf fur14
./do_fontsize_a_v2.sh 23 ../ttf/fu/FreeUniversal-Regular.ttf fur17
./do_fontsize_a_v2.sh 28 ../ttf/fu/FreeUniversal-Regular.ttf fur20
./do_fontsize_a_v2.sh 34 ../ttf/fu/FreeUniversal-Regular.ttf fur25
./do_fontsize_a_v2.sh 40 ../ttf/fu/FreeUniversal-Regular.ttf fur30
./do_fontsize_a_n_v2.sh 48 ../ttf/fu/FreeUniversal-Regular.ttf fur35
./do_fontsize_a_n_v2.sh 58 ../ttf/fu/FreeUniversal-Regular.ttf fur42
./do_fontsize_a_n_v2.sh 68 ../ttf/fu/FreeUniversal-Regular.ttf fur49

./do_fontsize_a_v2.sh 25 ../ttf/os/OldStandard-Bold.ttf osb18
./do_fontsize_a_v2.sh 28 ../ttf/os/OldStandard-Bold.ttf osb21
./do_fontsize_a_v2.sh 34 ../ttf/os/OldStandard-Bold.ttf osb26
./do_fontsize_a_v2.sh 38 ../ttf/os/OldStandard-Bold.ttf osb29
./do_fontsize_a_v2.sh 48 ../ttf/os/OldStandard-Bold.ttf osb35
#./do_fontsize_a_v2.sh 55 ../ttf/os/OldStandard-Bold.ttf osb41

./do_fontsize_a_v2.sh 26 ../ttf/os/OldStandard-Regular.ttf osr18
./do_fontsize_a_v2.sh 29 ../ttf/os/OldStandard-Regular.ttf osr21
./do_fontsize_a_v2.sh 36 ../ttf/os/OldStandard-Regular.ttf osr26
./do_fontsize_a_v2.sh 41 ../ttf/os/OldStandard-Regular.ttf osr29
./do_fontsize_a_v2.sh 49 ../ttf/os/OldStandard-Regular.ttf osr35
#./do_fontsize_a_v2.sh 57 ../ttf/os/OldStandard-Reglar.ttf osr41

echo "logisoso"

./do_fontsize_a_v2.sh 23 ../ttf/log/Logisoso.ttf logisoso16
./do_fontsize_a_v2.sh 27 ../ttf/log/Logisoso.ttf logisoso18
./do_fontsize_a_v2.sh 30 ../ttf/log/Logisoso.ttf logisoso20
./do_fontsize_a_v2.sh 32 ../ttf/log/Logisoso.ttf logisoso22
./do_fontsize_a_v2.sh 34 ../ttf/log/Logisoso.ttf logisoso24
./do_fontsize_a_v2.sh 38 ../ttf/log/Logisoso.ttf logisoso26
./do_fontsize_a_v2.sh 40 ../ttf/log/Logisoso.ttf logisoso28
./do_fontsize_a_no_64_v2.sh 43 ../ttf/log/Logisoso.ttf logisoso30
./do_fontsize_a_no_64_v2.sh 45 ../ttf/log/Logisoso.ttf logisoso32
./do_fontsize_a_no_64_v2.sh 49 ../ttf/log/Logisoso.ttf logisoso34
./do_fontsize_a_no_64_v2.sh 54 ../ttf/log/Logisoso.ttf logisoso38
./do_fontsize_a_no_64_v2.sh 60 ../ttf/log/Logisoso.ttf logisoso42
./do_fontsize_a_no_64_v2.sh 66 ../ttf/log/Logisoso.ttf logisoso46
./do_fontsize_a_no_64_v2.sh 71 ../ttf/log/Logisoso.ttf logisoso50
./do_fontsize_a_n_v2.sh  77 ../ttf/log/Logisoso.ttf logisoso54
./do_fontsize_a_n_v2.sh  83 ../ttf/log/Logisoso.ttf logisoso58
./do_fontsize_a_n_v2.sh  89 ../ttf/log/Logisoso.ttf logisoso62

echo "execute do_combine.sh after executing this script"

#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/32233456/ucg_bitmap.o \
	${OBJECTDIR}/_ext/32233456/ucg_box.o \
	${OBJECTDIR}/_ext/32233456/ucg_ccs.o \
	${OBJECTDIR}/_ext/32233456/ucg_circle.o \
	${OBJECTDIR}/_ext/32233456/ucg_clip.o \
	${OBJECTDIR}/_ext/32233456/ucg_com_msg_api.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_default_cb.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9163.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9325.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9325_spi.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9341.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ld50t6160.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_pcf8833.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_seps225.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1289.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1331.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1351.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_ic_st7735.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_msg_api.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_ft.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_ilsoft.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_univision.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_oled_160x128_samsung.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_oled_96x64_univision.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_tft_128x128_ili9163.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_tft_128x160_st7735.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_tft_132x132_pcf8833.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ili9325_spi.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ili9341.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_itdb02.o \
	${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ssd1289.o \
	${OBJECTDIR}/_ext/32233456/ucg_font.o \
	${OBJECTDIR}/_ext/32233456/ucg_init.o \
	${OBJECTDIR}/_ext/32233456/ucg_line.o \
	${OBJECTDIR}/_ext/32233456/ucg_pixel.o \
	${OBJECTDIR}/_ext/32233456/ucg_pixel_font_data.o \
	${OBJECTDIR}/_ext/32233456/ucg_polygon.o \
	${OBJECTDIR}/_ext/32233456/ucg_rotate.o \
	${OBJECTDIR}/_ext/32233456/ucg_scale.o \
	${OBJECTDIR}/_ext/32233456/ucg_vector_font_data.o \
	${OBJECTDIR}/_ext/1360921778/ucglib_com_mpsse.o \
	${OBJECTDIR}/draw_tga.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lmpsse

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/show_tga

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/show_tga: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/show_tga ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/32233456/ucg_bitmap.o: ../../../csrc/ucg_bitmap.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_bitmap.o ../../../csrc/ucg_bitmap.c

${OBJECTDIR}/_ext/32233456/ucg_box.o: ../../../csrc/ucg_box.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_box.o ../../../csrc/ucg_box.c

${OBJECTDIR}/_ext/32233456/ucg_ccs.o: ../../../csrc/ucg_ccs.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_ccs.o ../../../csrc/ucg_ccs.c

${OBJECTDIR}/_ext/32233456/ucg_circle.o: ../../../csrc/ucg_circle.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_circle.o ../../../csrc/ucg_circle.c

${OBJECTDIR}/_ext/32233456/ucg_clip.o: ../../../csrc/ucg_clip.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_clip.o ../../../csrc/ucg_clip.c

${OBJECTDIR}/_ext/32233456/ucg_com_msg_api.o: ../../../csrc/ucg_com_msg_api.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_com_msg_api.o ../../../csrc/ucg_com_msg_api.c

${OBJECTDIR}/_ext/32233456/ucg_dev_default_cb.o: ../../../csrc/ucg_dev_default_cb.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_default_cb.o ../../../csrc/ucg_dev_default_cb.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9163.o: ../../../csrc/ucg_dev_ic_ili9163.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9163.o ../../../csrc/ucg_dev_ic_ili9163.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9325.o: ../../../csrc/ucg_dev_ic_ili9325.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9325.o ../../../csrc/ucg_dev_ic_ili9325.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9325_spi.o: ../../../csrc/ucg_dev_ic_ili9325_spi.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9325_spi.o ../../../csrc/ucg_dev_ic_ili9325_spi.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9341.o: ../../../csrc/ucg_dev_ic_ili9341.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ili9341.o ../../../csrc/ucg_dev_ic_ili9341.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ld50t6160.o: ../../../csrc/ucg_dev_ic_ld50t6160.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ld50t6160.o ../../../csrc/ucg_dev_ic_ld50t6160.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_pcf8833.o: ../../../csrc/ucg_dev_ic_pcf8833.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_pcf8833.o ../../../csrc/ucg_dev_ic_pcf8833.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_seps225.o: ../../../csrc/ucg_dev_ic_seps225.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_seps225.o ../../../csrc/ucg_dev_ic_seps225.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1289.o: ../../../csrc/ucg_dev_ic_ssd1289.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1289.o ../../../csrc/ucg_dev_ic_ssd1289.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1331.o: ../../../csrc/ucg_dev_ic_ssd1331.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1331.o ../../../csrc/ucg_dev_ic_ssd1331.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1351.o: ../../../csrc/ucg_dev_ic_ssd1351.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_ssd1351.o ../../../csrc/ucg_dev_ic_ssd1351.c

${OBJECTDIR}/_ext/32233456/ucg_dev_ic_st7735.o: ../../../csrc/ucg_dev_ic_st7735.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_ic_st7735.o ../../../csrc/ucg_dev_ic_st7735.c

${OBJECTDIR}/_ext/32233456/ucg_dev_msg_api.o: ../../../csrc/ucg_dev_msg_api.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_msg_api.o ../../../csrc/ucg_dev_msg_api.c

${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_ft.o: ../../../csrc/ucg_dev_oled_128x128_ft.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_ft.o ../../../csrc/ucg_dev_oled_128x128_ft.c

${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_ilsoft.o: ../../../csrc/ucg_dev_oled_128x128_ilsoft.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_ilsoft.o ../../../csrc/ucg_dev_oled_128x128_ilsoft.c

${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_univision.o: ../../../csrc/ucg_dev_oled_128x128_univision.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_oled_128x128_univision.o ../../../csrc/ucg_dev_oled_128x128_univision.c

${OBJECTDIR}/_ext/32233456/ucg_dev_oled_160x128_samsung.o: ../../../csrc/ucg_dev_oled_160x128_samsung.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_oled_160x128_samsung.o ../../../csrc/ucg_dev_oled_160x128_samsung.c

${OBJECTDIR}/_ext/32233456/ucg_dev_oled_96x64_univision.o: ../../../csrc/ucg_dev_oled_96x64_univision.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_oled_96x64_univision.o ../../../csrc/ucg_dev_oled_96x64_univision.c

${OBJECTDIR}/_ext/32233456/ucg_dev_tft_128x128_ili9163.o: ../../../csrc/ucg_dev_tft_128x128_ili9163.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_tft_128x128_ili9163.o ../../../csrc/ucg_dev_tft_128x128_ili9163.c

${OBJECTDIR}/_ext/32233456/ucg_dev_tft_128x160_st7735.o: ../../../csrc/ucg_dev_tft_128x160_st7735.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_tft_128x160_st7735.o ../../../csrc/ucg_dev_tft_128x160_st7735.c

${OBJECTDIR}/_ext/32233456/ucg_dev_tft_132x132_pcf8833.o: ../../../csrc/ucg_dev_tft_132x132_pcf8833.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_tft_132x132_pcf8833.o ../../../csrc/ucg_dev_tft_132x132_pcf8833.c

${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ili9325_spi.o: ../../../csrc/ucg_dev_tft_240x320_ili9325_spi.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ili9325_spi.o ../../../csrc/ucg_dev_tft_240x320_ili9325_spi.c

${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ili9341.o: ../../../csrc/ucg_dev_tft_240x320_ili9341.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ili9341.o ../../../csrc/ucg_dev_tft_240x320_ili9341.c

${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_itdb02.o: ../../../csrc/ucg_dev_tft_240x320_itdb02.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_itdb02.o ../../../csrc/ucg_dev_tft_240x320_itdb02.c

${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ssd1289.o: ../../../csrc/ucg_dev_tft_240x320_ssd1289.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_dev_tft_240x320_ssd1289.o ../../../csrc/ucg_dev_tft_240x320_ssd1289.c

${OBJECTDIR}/_ext/32233456/ucg_font.o: ../../../csrc/ucg_font.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_font.o ../../../csrc/ucg_font.c

${OBJECTDIR}/_ext/32233456/ucg_init.o: ../../../csrc/ucg_init.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_init.o ../../../csrc/ucg_init.c

${OBJECTDIR}/_ext/32233456/ucg_line.o: ../../../csrc/ucg_line.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_line.o ../../../csrc/ucg_line.c

${OBJECTDIR}/_ext/32233456/ucg_pixel.o: ../../../csrc/ucg_pixel.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_pixel.o ../../../csrc/ucg_pixel.c

${OBJECTDIR}/_ext/32233456/ucg_pixel_font_data.o: ../../../csrc/ucg_pixel_font_data.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_pixel_font_data.o ../../../csrc/ucg_pixel_font_data.c

${OBJECTDIR}/_ext/32233456/ucg_polygon.o: ../../../csrc/ucg_polygon.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_polygon.o ../../../csrc/ucg_polygon.c

${OBJECTDIR}/_ext/32233456/ucg_rotate.o: ../../../csrc/ucg_rotate.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_rotate.o ../../../csrc/ucg_rotate.c

${OBJECTDIR}/_ext/32233456/ucg_scale.o: ../../../csrc/ucg_scale.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_scale.o ../../../csrc/ucg_scale.c

${OBJECTDIR}/_ext/32233456/ucg_vector_font_data.o: ../../../csrc/ucg_vector_font_data.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/32233456
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/32233456/ucg_vector_font_data.o ../../../csrc/ucg_vector_font_data.c

${OBJECTDIR}/_ext/1360921778/ucglib_com_mpsse.o: ../com/ucglib_com_mpsse.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360921778
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360921778/ucglib_com_mpsse.o ../com/ucglib_com_mpsse.c

${OBJECTDIR}/draw_tga.o: draw_tga.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/draw_tga.o draw_tga.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../csrc -I../com -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/show_tga

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

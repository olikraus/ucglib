
#include <string.h>
#include <stdlib.h>
#include "bdf_font.h"

/*================================================*/

int get_str_arg(char ***argv, int c, char **result)
{
  if ( (**argv)[0] == '-' )
  {
    if ( (**argv)[1] == c )
    {
      if ( (**argv)[2] == '\0' )
      {
	(*argv)++;
	*result = **argv;
      }
      else
      {
	*result = (**argv)+2;
      }
      (*argv)++;
      return 1;      
    }
  }
  return 0;
}


int get_num_arg(char ***argv, int c, unsigned long *result)
{
  if ( (**argv)[0] == '-' )
  {
    if ( (**argv)[1] == c )
    {
      if ( (**argv)[2] == '\0' )
      {
	(*argv)++;
	*result = strtoul((**argv), NULL, 10);
      }
      else
      {
	*result = strtoul((**argv)+2, NULL, 10);
      }
      (*argv)++;
      return 1;      
    }
  }
  return 0;
}

int is_arg(char ***argv, int c)
{
  if ( (**argv)[0] == '-' )
  {
    if ( (**argv)[1] == c )
    {
      (*argv)++;
      return 1;      
    }
  }
  return 0;
}

/*================================================*/
void help(void)
{
  printf("bdfconv [options] filename\n");
  printf("-h        Display this help\n");
  printf("-v        Print log messages\n");
  printf("-x        Use max bbx for each selected glyph\n");
  printf("-m <map>  Unicode ASCII mapping\n");
  printf("-d <fontname>  Font for description in TGA file\n");
  printf("\n");

  printf("map := <mapcmd> { \",\" <mapcmd> }\n");
  printf("mapcmd := <default> | <maprange> | <exclude>\n");
  printf("default := \"*\"\n");
  printf("maprange := <range> [  \">\" <num> ]\n");
  printf("exclude := \"~\" <range> \n");
  printf("range := <num> [ \"-\" <num> ]\n");
  printf("num := <hexnum> | <decnum>\n");
  printf("hexnum := \"$\" <hexdigit> { <hexdigit> }\n");
  printf("decnum := <decdigit> { <decdigit> }\n");
  printf("decdigit := \"0\" | \"1\" | \"2\" | \"3\" | \"4\" | \"5\" | \"6\" | \"7\" | \"8\" | \"9\"\n");
  printf("hexdigit := \"a\" | \"b\" | \"c\" | \"d\" | \"e\" | \"f\" | \"A\" | \"B\" | \"C\" | \"D\" | \"E\" | \"F\" | <decdigit>\n");
    
  printf("{ }: zero, one ore more\n");
  printf("[ ]: zero or once\n");
  printf("|: alternative\n");
  
}

/*================================================*/



unsigned tga_draw_font_line(unsigned y, long enc_start, bf_t *bf_desc_font, bf_t *bf)
{
  long i;
  unsigned x;
  int is_empty;
  char pre[32];
  
  is_empty = 1;
  for( i = 0; i< 16 && is_empty != 0; i++ )
  {
    if ( tga_get_glyph_data(i+enc_start) != NULL )
	is_empty = 0;
  }
  
  if ( is_empty != 0 )
    return 0;
  
  sprintf(pre, "%3ld/0x%02lx", enc_start, enc_start);
  
  x = 0;
  if ( bf_desc_font != NULL )
  {
    if ( bf_desc_font->target_data != NULL )
    {
      tga_set_font(bf_desc_font->target_data);
      x += tga_draw_string(x, y, pre, 0, 0);
    }
  }
  x += 4;
  
  tga_set_font(bf->target_data);
  for( i = 0; i< 16; i++ )
  {
    tga_draw_glyph(x + (tga_get_char_width()+2)*i,y,enc_start+i, 1);
  }

  return x + (tga_get_char_width()+2)*16;
}

void tga_draw_font(unsigned y, bf_t *bf_desc_font, bf_t *bf)
{
  long i;
  unsigned x, xmax;
  xmax = 0;
  for( i = 0; i < 256; i+=16 )
  {
    x = tga_draw_font_line(y, i, bf_desc_font, bf);
    if ( x > 0 )
    {
      if ( xmax < x )
	xmax = x;
      y +=  tga_get_char_height()+1;
    }
  }
  
  tga_set_font(bf->target_data);
  
  //tga_draw_string(0, y, "Woven silk pyjamas exchanged for blue quartz", 1, xmax);
  //y += tga_get_char_height()+1;
  tga_draw_string(0, y, "Woven silk pyjamas exchanged for blue quartz", 0, xmax);
}


/*================================================*/
/* main */

int main(int argc, char **argv)
{
  bf_t *bf_desc_font;
  bf_t *bf;
  char *bdf_filename = NULL;
  int is_verbose = 0;
  char *map_str ="*";
  char *desc_font_str = "";
  
  argv++;
  /*
  if ( *argv == NULL )
  {
    help();
    exit(1);
  }
  */
  for(;;)
  {
    if ( *argv == NULL )
      break;
    if ( is_arg(&argv, 'h') != 0 )
    {
      help();
      exit(1);
    }
    else if ( is_arg(&argv, 'v') != 0 )
    {
      is_verbose = 1;
    }
    /*
    else if ( get_num_arg(&argv, 's', &speed) != 0 )
    {
    }
    */
    else if ( get_str_arg(&argv, 'd', &desc_font_str) != 0 )
    {      
    }
    else if ( get_str_arg(&argv, 'm', &map_str) != 0 )
    {      
    }
    else
    {
      bdf_filename = *argv;
      argv++;
    }
  }
  
  if ( bdf_filename  == NULL )
  {
    help();
    exit(1);
  }

  bf_desc_font = NULL;
  if ( desc_font_str[0] != '\0' )
  {
    bf_desc_font = bf_OpenFromFile(desc_font_str, 0, BDF_BBX_MODE_MINIMAL, "*");
    if ( bf_desc_font == NULL )
    {
      exit(1);
    }
  }

  //bf = bf_OpenFromFile(bdf_filename, is_verbose, BDF_BBX_MODE_MINIMAL, map_str);
  bf = bf_OpenFromFile(bdf_filename, is_verbose, BDF_BBX_MODE_MAX, map_str);
  //bf = bf_OpenFromFile(bdf_filename, is_verbose, BDF_BBX_MODE_HEIGHT, map_str);
  
  //bf_ShowAllGlyphs(bf, &(bf->max));

  tga_init(800, 600);
  //tga_set_pixel(1, 1, 255,0,0);

  tga_set_font(bf->target_data);
  //tga_draw_glyph(10, 18, ' ');

  //tga_draw_font_line(50, 64, bf_desc_font, bf);
  tga_draw_font(30, bf_desc_font, bf);
  
  /*
  tga_draw_glyph(40, 18, 'B');

  tga_draw_glyph(10, 50, bf->enc_x);
  tga_draw_glyph(10+30, 50, bf->enc_y);
  tga_draw_glyph(10+30+30, 50, bf->enc_w);
  tga_draw_glyph(10+30+30+30, 50, bf->enc_h);
  tga_draw_glyph(10+30+30+30+30, 50, 'E');
  */
  //tga_draw_string(10,82,"BjAjQ QnBmj");
  
  
  tga_save("bdf.tga");


  
  bf_Close(bf);
  return 0;
}

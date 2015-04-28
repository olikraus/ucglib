
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "bdf_font.h"
#include "fd.h"

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
	if ( *((*argv)+1) != NULL )
	{
	  (*argv)++;
	  *result = strtoul((**argv), NULL, 10);
	}
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
  printf("-b <n>    Font build mode, 0: proportional, 1: common height, 2: monospace, 3: multiple of 8\n");
  printf("-m 'map'  Unicode ASCII mapping\n");
  printf("-o <file>  C output file\n");
  printf("-n <name>  C indentifier (font name)\n");
  printf("-l <margin>   Overview picture: Set left margin\n");
  printf("-d <file>     Overview picture: BDF font for description\n");
  printf("-a            Overview picture: Additional font information (background, orange&blue dot)\n");
  printf("-t            Overview picture: Test string (Woven silk pyjamas exchanged for blue quartz.)\n");
  printf("-r Runtime test\n");
  printf("\n");

  printf("map := <mapcmd> { \",\" <mapcmd> }\n");
  printf("mapcmd := <default> | <maprange> | <exclude>\n");
  printf("default := \"*\"\n");
  printf("maprange := <range> [  \">\" <addexpr> ]        Move specified glyph <range> to target code <num>\n");
  printf("exclude := \"~\" <range> \n");
  printf("range := <addexpr> [ \"-\" <addexpr> ]          Select glyphs within specified range\n");
  printf("addexpr := <mulexpr> [ \"+\" <mulexpr> ]\n");
  printf("mulexpr := <num> [ \"*\" <num> ]\n");
  printf("num := <hexnum> | <decnum>\n");
  printf("hexnum := \"$\" <hexdigit> { <hexdigit> }\n");
  printf("decnum := <decdigit> { <decdigit> }\n");
  printf("decdigit := \"0\" | \"1\" | \"2\" | \"3\" | \"4\" | \"5\" | \"6\" | \"7\" | \"8\" | \"9\"\n");
  printf("hexdigit := \"a\" | \"b\" | \"c\" | \"d\" | \"e\" | \"f\" | \"A\" | \"B\" | \"C\" | \"D\" | \"E\" | \"F\" | <decdigit>\n");
    
  printf("{ }: zero, one ore more\n");
  printf("[ ]: zero or once\n");
  printf("|: alternative\n");

  printf("example:\n");
  printf("  -m '32-255'     select gylphs from encoding 32 to 255\n");
  printf("  -m '32-255,~64' select gylphs from encoding 32 to 255, exclude '@'\n");
  printf("  -m '32,48-57'   select space, '1', '2', ... '9'\n");

}

/*================================================*/

unsigned long left_margin = 1;
unsigned long build_bbx_mode = 0;
int font_picture_extra_info = 0;
int font_picture_test_string = 0;
int runtime_test = 0;
char *c_filename = NULL;
char *target_fontname = "bdf_font";

/*================================================*/

unsigned tga_get_line_height(bf_t *bf_desc_font, bf_t *bf)
{
  unsigned h;
  tga_set_font(bf_desc_font->target_data);
  h = tga_get_char_height();
  tga_set_font(bf->target_data);
  if ( h < tga_get_char_height() )
    return tga_get_char_height();
  return h;
}

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
  
  x = left_margin;
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
    tga_draw_glyph(x + (tga_get_char_width()+2)*i,y,enc_start+i, font_picture_extra_info);
  }

  return left_margin + x + (tga_get_char_width()+2)*16;
}

unsigned tga_draw_font_info(unsigned y, const char *fontname, bf_t *bf_desc_font, bf_t *bf)
{
  unsigned x;
  int cap_a, cap_a_height;
  static char s[256];
  
  cap_a_height = 0;
  cap_a = bf_GetIndexByEncoding(bf, 'A');
  if ( cap_a >= 0 )
  {
    cap_a_height = bf->glyph_list[cap_a]->bbx.h+bf->glyph_list[cap_a]->bbx.y;
  }
  
  if ( bf_desc_font != NULL )
  {
    if ( bf_desc_font->target_data != NULL )
    {
      
      tga_set_font(bf_desc_font->target_data);
      
      y +=  tga_get_char_height()+1;
      x = left_margin;
      x += tga_draw_string(x, y, fontname, 0, 0);

      y +=  tga_get_char_height()+1;      
      sprintf(s, "Max width %u, max height %u", tga_get_char_width(), tga_get_char_height());
      x = left_margin;
      x += tga_draw_string(x, y, s, 0, 0);

      y +=  tga_get_char_height()+1;      
      sprintf(s, "'A' height %d, font size %d ", cap_a_height, bf->target_cnt);
      x = left_margin;
      x += tga_draw_string(x, y, s, 0, 0);
      return (tga_get_char_height()+1)*3;
    }
  }
  return 0;
}


unsigned tga_draw_font(unsigned y, const char *fontname, bf_t *bf_desc_font, bf_t *bf)
{
  long i;
  unsigned x, xmax;
  xmax = 0;
  
  y += tga_draw_font_info( y, fontname, bf_desc_font, bf);
  
  y +=   tga_get_line_height(bf_desc_font, bf)+1;
  
  
  for( i = 0; i < 256; i+=16 )
  {
    x = tga_draw_font_line(y, i, bf_desc_font, bf);
    if ( x > 0 )
    {
      if ( xmax < x )
	xmax = x;
      y +=  tga_get_line_height(bf_desc_font, bf)+1;
    }
  }
  
  tga_set_font(bf->target_data);
  
  //tga_draw_string(0, y, "Woven silk pyjamas exchanged for blue quartz", 1, xmax);
  //y += tga_get_char_height()+1;
  if ( font_picture_test_string != 0 )
  {
    tga_draw_string(left_margin, y, "Woven silk pyjamas exchanged for blue quartz.", 0, xmax);
    y +=  tga_get_line_height(bf_desc_font, bf)+1;
  }
  return y;
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
  unsigned y;
  
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
    else if ( is_arg(&argv, 'a') != 0 )
    {
      font_picture_extra_info = 1;
    }
    else if ( is_arg(&argv, 't') != 0 )
    {
      font_picture_test_string = 1;
    }
    else if ( is_arg(&argv, 'r') != 0 )
    {
      runtime_test = 1;
    }
    else if ( get_num_arg(&argv, 'b', &build_bbx_mode) != 0 )
    {
    }
    else if ( get_num_arg(&argv, 'l', &left_margin) != 0 )
    {
    }
    else if ( get_str_arg(&argv, 'd', &desc_font_str) != 0 )
    {      
    }
    else if ( get_str_arg(&argv, 'o', &c_filename) != 0 )
    {      
    }
    else if ( get_str_arg(&argv, 'n', &target_fontname) != 0 )
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

  
  bf = bf_OpenFromFile(bdf_filename, is_verbose, build_bbx_mode, map_str);
  
  if ( bf == NULL )
  {
    exit(1);
  }

  if ( bf_desc_font != NULL )
  {
    tga_init(1024, 600);
    y = tga_draw_font(0, bdf_filename, bf_desc_font, bf);
    
    if ( runtime_test != 0 )
    {
      long i;
      clock_t c = clock();
      fd_t fd;
      fd_init(&fd);
      fd_set_font(&fd, bf->target_data);
      for( i = 0; i < 10000; i++ )
	fd_draw_string(&fd, left_margin, y, "Woven silk pyjamas exchanged for blue quartz.");
      bf_Log(bf, "Runtime test: %.2lf sec", (double)(clock()-c)/(double)CLOCKS_PER_SEC);
    }
    
    tga_save("bdf.tga");
  }
  if ( c_filename != NULL )
  {
    bf_WriteUCGCByFilename(bf, c_filename, target_fontname, "  ");
  }

  
  bf_Close(bf);
  return 0;
}

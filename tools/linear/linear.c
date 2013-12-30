

/*

  s: start
  e: end
  n: steps
  
  
  f(0) = s
  f(n) = e
  f(x) = m*x + s
  f(n-1) = m*(n-1) + s =!= e
      --> m = (e-s)/n
  f(x) = (e-s)/(n-1) * x + s
  f(0) = s
  f(1) = s + (e-s)/(n-1)
*/

#include <stdint.h>
#include <stdio.h>


typedef int16_t ucg_int_t;

struct _ucg_lin_t
{
  uint8_t start;
  uint8_t current;
  uint8_t num;
  uint8_t quot;
  
  ucg_int_t den;
  ucg_int_t rem;  
  ucg_int_t frac;
};
typedef struct _ucg_lin_t ucg_lin_t;

/*
  
*/
void ucg_lin_init(ucg_lin_t *lin, uint8_t start, uint8_t end, ucg_int_t steps)
{
  lin->start = start;
  lin->num = end-start;
  lin->den = steps-1;
  
  lin->quot = lin->num / lin->den;
  lin->rem = lin->num % lin->den;
  
  lin->frac = lin->den/2;
  lin->current = start;
}

void ucg_lin_step(ucg_lin_t *lin)
{
  
  lin->current += lin->quot;
  lin->frac += lin->rem;
  if ( lin->frac >= lin->den )
  {
    lin->current++;
    lin->frac -= lin->den;
  }
  
}

/*
  f(x) = (e-s)/(n-1) * x + s
  current = (num / den)  * (pos / den)
  
*/
void ucg_lin_seek(ucg_lin_t *lin, ucg_int_t pos)
{
  ucg_int_t p;
  lin->current = lin->quot;
  lin->current *= pos;
  p = lin->rem * pos + lin->den/2;
  lin->current += p / lin->den;
  lin->frac = p % lin->den;
  lin->current += lin->start;
}

int main(void)
{
  ucg_lin_t lin;
  ucg_lin_t lin2;
  ucg_int_t i, n;
  
  n = 10;
  ucg_lin_init(&lin, 5, 70, n);
  ucg_lin_init(&lin2, 5, 70, n);
  for( i = 0; i < n; i++ )
  {
    ucg_lin_seek(&lin2, i);
    printf("%d: current=%d frac=%d (current=%d frac=%d)\n", i, lin.current, lin.frac, lin2.current, lin2.frac);
    ucg_lin_step(&lin);
  }
  
}


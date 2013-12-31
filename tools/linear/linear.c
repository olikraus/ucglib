

/*

  ccs = color component slide

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

struct _ucg_ccs_t
{
  uint8_t current;	/* contains the current color component */
  uint8_t start;
  uint8_t num;
  uint8_t quot;
  
  ucg_int_t den;
  ucg_int_t rem;  
  ucg_int_t frac;
};
typedef struct _ucg_ccs_t ucg_ccs_t;

/*
  
*/
void ucg_ccs_init(ucg_ccs_t *ccs, uint8_t start, uint8_t end, ucg_int_t steps)
{
  ccs->start = start;
  ccs->num = end-start;
  ccs->den = steps-1;
  
  ccs->quot = ccs->num / ccs->den;
  ccs->rem = ccs->num % ccs->den;
  
  ccs->frac = ccs->den/2;
  ccs->current = start;
}

void ucg_ccs_step(ucg_ccs_t *ccs)
{
  
  ccs->current += ccs->quot;
  ccs->frac += ccs->rem;
  if ( ccs->frac >= ccs->den )
  {
    ccs->current++;
    ccs->frac -= ccs->den;
  }
  
}

/*
  f(x) = (e-s)/(n-1) * x + s
  current = (num / den)  * (pos / den)
  
*/
void ucg_ccs_seek(ucg_ccs_t *ccs, ucg_int_t pos)
{
  ucg_int_t p;
  ccs->current = ccs->quot;
  ccs->current *= pos;
  p = ccs->rem * pos + ccs->den/2;
  ccs->current += p / ccs->den;
  ccs->frac = p % ccs->den;
  ccs->current += ccs->start;
}

int main(void)
{
  ucg_ccs_t ccs;
  ucg_ccs_t ccs2;
  ucg_int_t i, n;
  
  n = 10;
  ucg_ccs_init(&ccs, 5, 70, n);
  ucg_ccs_init(&ccs2, 5, 70, n);
  for( i = 0; i < n; i++ )
  {
    ucg_ccs_seek(&ccs2, i);
    printf("%d: current=%d frac=%d (current=%d frac=%d)\n", i, ccs.current, ccs.frac, ccs2.current, ccs2.frac);
    ucg_ccs_step(&ccs);
  }
  
}


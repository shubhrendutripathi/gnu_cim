/* $Id: $ */

/* Copyright (C) 1997 Sverre Hvammen Johansen,
 * Department of Informatics, University of Oslo.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "cim.h"
#include "config.h"

#if STDC_HEADERS || HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#include <stdio.h>

/******************************************************************************
                                 PROCEDURE PUTFIX (text attributt)           */

__txtvp __rtputfix (__txtvp t, double r, long n)
{
  static char cs[__RTPUTTEXTLENGTH + 1],
    fcs[__RTPUTTEXTFORMATLENGTH + 1];
  long i,
    j,
    l;
  char *s;
  if (n < 0)
    __rerror ("Putfix: Second parameter is lesser than zero");
  if (n > __RTPUTMAXN)
    __rerror ("Putfix: Last parameter to big");
  if (t->obj == __NULL)
    __rerror ("Putfix: Notext");
  if (t->obj->h.konstant)
    __rerror ("Putfix: Constant text object");
  s = t->obj->string;
  (void) sprintf (fcs, "%%.%ld%s", n, "lf");
  (void) sprintf (cs, fcs, r);
  if ((cs[0] == 'I') | (cs[1] == 'I'))	/* Test p} om det er lik uendelig */
    __rerror ("Illegal real number");
  if (cs[0] == '-')
    for (i = 1; __TRUE; i++)
      {
	if (cs[i] == '0' || cs[i] == '.')
	  continue;
	if (cs[i] == '\0')
	  {
	    for (i = 0; cs[i]; i++)
	      cs[i] = cs[i + 1];
	    break;
	  }
	break;
      }
  if (__currentdecimalmark != '.')
    {
      for (i = 0; cs[i] != '.'; i++);
      cs[i] = __currentdecimalmark;
    }
  if ((l = strlen (cs)) <= t->length)
    {
      i = t->length - l;
      for (j = 0; j < i; j++)
	s[t->start + j - 1] = ' ';
      for (i = 0; i < l; i++)
	s[t->start + (j++) - 1] = cs[i];
    }
  else
    {
      __rwarning ("Putfix: Text object to short");
      for (j = 0; j < (long) t->length; j++)
	s[t->start + j - 1] = '*';
    }
  t->pos = t->length + 1;
  __rputlen = l;
  return (t);
}

/*
 *  -- High Performance Computing Linpack Benchmark (HPL-GPU)
 *     HPL-GPU - 2.0 - 2015
 *
 *     David Rohr
 *     Matthias Kretz
 *     Matthias Bach
 *     Goethe Universität, Frankfurt am Main
 *     Frankfurt Institute for Advanced Studies
 *     (C) Copyright 2010 All Rights Reserved
 *
 *     Antoine P. Petitet
 *     University of Tennessee, Knoxville
 *     Innovative Computing Laboratory
 *     (C) Copyright 2000-2008 All Rights Reserved
 *
 *  -- Copyright notice and Licensing terms:
 *
 *  Redistribution  and  use in  source and binary forms, with or without
 *  modification, are  permitted provided  that the following  conditions
 *  are met:
 *
 *  1. Redistributions  of  source  code  must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce  the above copyright
 *  notice, this list of conditions,  and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *
 *  3. All  advertising  materials  mentioning  features  or  use of this
 *  software must display the following acknowledgements:
 *  This  product  includes  software  developed  at  the  University  of
 *  Tennessee, Knoxville, Innovative Computing Laboratory.
 *  This product  includes software  developed at the Frankfurt Institute
 *  for Advanced Studies.
 *
 *  4. The name of the  University,  the name of the  Laboratory,  or the
 *  names  of  its  contributors  may  not  be used to endorse or promote
 *  products  derived   from   this  software  without  specific  written
 *  permission.
 *
 *  -- Disclaimer:
 *
 *  THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 *  OR  CONTRIBUTORS  BE  LIABLE FOR ANY  DIRECT,  INDIRECT,  INCIDENTAL,
 *  SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES  (INCLUDING,  BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA OR PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT,  STRICT LIABILITY,  OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ======================================================================
 */

/*
 * Include files
 */
#include "hpl.h"

void HPL_warn
(
   FILE *                           STREAM,
   int                              LINE,
   const char *                     SRNAME,
   const char *                     FORM,
   ...                              
)
{
/* 
 * Purpose
 * =======
 *
 * HPL_warn displays an error message.
 * 
 *
 * Arguments
 * =========
 *
 * STREAM  (local input)                 FILE *
 *         On entry, STREAM specifies the output stream.
 *
 * LINE    (local input)                 int
 *         On entry,  LINE  specifies the line  number in the file where
 *         the  error  has  occured.  When  LINE  is not a positive line
 *         number, it is ignored.
 *
 * SRNAME  (local input)                 const char *
 *         On entry, SRNAME  should  be the name of the routine  calling
 *         this error handler.
 *
 * FORM    (local input)                 const char *
 *         On entry, FORM specifies the format, i.e., how the subsequent
 *         arguments are converted for output.
 *
 *         (local input)                 ...
 *         On entry,  ...  is the list of arguments to be printed within
 *         the format string.
 *
 * ---------------------------------------------------------------------
 */ 
/*
 * .. Local Variables ..
 */
   va_list                    argptr;
   char                       cline[128];
/* ..
 * .. Executable Statements ..
 */
   va_start( argptr, FORM );
   (void) vsprintf( cline, FORM, argptr );
   va_end( argptr ); 
/*
 * Display an error message
 */
   if( LINE <= 0 )
      HPL_fprintf( STREAM, "%s %s:\n>>> %s <<<\n\n", "HPL ERROR in function",
                   SRNAME, cline );
   else
      HPL_fprintf( STREAM, "%s %d %s %s:\n>>> %s <<<\n\n",
                   "HPL ERROR on line", LINE, "of function", SRNAME, cline );
/*
 * End of HPL_warn
 */
} 

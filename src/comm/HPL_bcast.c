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

#include "util_timer.h"
#include "util_trace.h"

int HPL_bcast
(
   HPL_T_panel *                    PANEL
)
{
/* 
 * Purpose
 * =======
 *
 * HPL_bcast broadcasts  the  current  panel.  Successful  completion is
 * indicated by IFLAG set to HPL_SUCCESS on return. IFLAG will be set to
 * HPL_FAILURE on failure and to HPL_KEEP_TESTING when the operation was
 * not completed, in which case this function should be called again.
 *
 * Arguments
 * =========
 *
 * PANEL   (input/output)                HPL_T_panel *
 *         On entry,  PANEL  points to the  current panel data structure
 *         being broadcast.
 *
 * IFLAG   (output)                      int *
 *         On exit,  IFLAG  indicates  whether  or not the broadcast has
 *         occured.
 *
 * ---------------------------------------------------------------------
 */ 
START_TRACE( BCAST )

/*
 * .. Local Variables ..
 */
   int                        ierr;
   HPL_T_TOP                  top;

/* ..
 * .. Executable Statements ..
 */
   if( PANEL == NULL ) return( HPL_SUCCESS );
   if( PANEL->grid->npcol <= 1 ) return( HPL_SUCCESS );
/*
 * Retrieve the selected virtual broadcast topology
 */
   top = PANEL->algo->btopo;

   switch( top )
   {
      case HPL_1RING_M     : ierr = HPL_bcast_1rinM( PANEL ); break;
      case HPL_1RING       : ierr = HPL_bcast_1ring( PANEL ); break;
      case HPL_2RING_M     : ierr = HPL_bcast_2rinM( PANEL ); break;
      case HPL_2RING       : ierr = HPL_bcast_2ring( PANEL ); break;
      case HPL_BLONG_M     : ierr = HPL_bcast_blonM( PANEL ); break;
      case HPL_BLONG       : ierr = HPL_bcast_blong( PANEL ); break;
      case HPL_MPI_BCAST   : ierr = HPL_bcast_mpi  ( PANEL ); break;
      default              : printf( "default" ); ierr = HPL_SUCCESS;
   }

END_TRACE

   return( ierr );
/*
 * End of HPL_bcast
 */
}

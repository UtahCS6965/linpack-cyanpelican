/* 
 * This is a modified version of the High Performance Computing Linpack
 * Benchmark (HPL). All code not contained in the original HPL version
 * 2.0 is property of the Frankfurt Institute for Advanced Studies
 * (FIAS). None of the material may be copied, reproduced, distributed,
 * republished, downloaded, displayed, posted or transmitted in any form
 * or by any means, including, but not limited to, electronic,
 * mechanical, photocopying, recording, or otherwise, without the prior
 * written permission of FIAS. For those parts contained in the
 * unmodified version of the HPL the below copyright notice applies.
 * 
 * Authors:
 * David Rohr (drohr@jwdt.org)
 * Matthias Bach (bach@compeng.uni-frankfurt.de)
 * Matthias Kretz (kretz@compeng.uni-frankfurt.de)
 * 
 * -- High Performance Computing Linpack Benchmark (HPL)                
 *    HPL - 2.0 - September 10, 2008                          
 *    Antoine P. Petitet                                                
 *    University of Tennessee, Knoxville                                
 *    Innovative Computing Laboratory                                 
 *    (C) Copyright 2000-2008 All Rights Reserved                       
 *                                                                      
 * -- Copyright notice and Licensing terms:                             
 *                                                                      
 * Redistribution  and  use in  source and binary forms, with or without
 * modification, are  permitted provided  that the following  conditions
 * are met:                                                             
 *                                                                      
 * 1. Redistributions  of  source  code  must retain the above copyright
 * notice, this list of conditions and the following disclaimer.        
 *                                                                      
 * 2. Redistributions in binary form must reproduce  the above copyright
 * notice, this list of conditions,  and the following disclaimer in the
 * documentation and/or other materials provided with the distribution. 
 *                                                                      
 * 3. All  advertising  materials  mentioning  features  or  use of this
 * software must display the following acknowledgement:                 
 * This  product  includes  software  developed  at  the  University  of
 * Tennessee, Knoxville, Innovative Computing Laboratory.             
 *                                                                      
 * 4. The name of the  University,  the name of the  Laboratory,  or the
 * names  of  its  contributors  may  not  be used to endorse or promote
 * products  derived   from   this  software  without  specific  written
 * permission.                                                          
 *                                                                      
 * -- Disclaimer:                                                       
 *                                                                      
 * THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 * OR  CONTRIBUTORS  BE  LIABLE FOR ANY  DIRECT,  INDIRECT,  INCIDENTAL,
 * SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES  (INCLUDING,  BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA OR PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT,  STRICT LIABILITY,  OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 * ---------------------------------------------------------------------
 */ 
/*
 * Include files
 */
#include "hpl.h"

#include "util_timer.h"
#include "util_trace.h"
/*
 * Do not use  MPI user-defined data types no matter what.  This routine
 * is used for small contiguous messages.
 */
#ifdef HPL_USE_MPI_DATATYPE
#undef HPL_USE_MPI_DATATYPE
#endif

int HPL_recv
(
   double *                         RBUF,
   int                              RCOUNT,
   int                              SRC,
   int                              RTAG,
   MPI_Comm                         COMM
)
{
/* 
 * Purpose
 * =======
 *
 * HPL_recv is a simple wrapper around  MPI_Recv.  Its  main  purpose is
 * to  allow for some  experimentation / tuning  of this simple routine.
 * Successful  completion  is  indicated  by  the  returned  error  code
 * HPL_SUCCESS.  In the case of messages of length less than or equal to
 * zero, this function returns immediately.
 *
 * Arguments
 * =========
 *
 * RBUF    (local output)                double *
 *         On entry, RBUF specifies the starting address of buffer to be
 *         received.
 *
 * RCOUNT  (local input)                 int
 *         On entry,  RCOUNT  specifies  the number  of double precision
 *         entries in RBUF. RCOUNT must be at least zero.
 *
 * SRC     (local input)                 int
 *         On entry, SRC  specifies the rank of the  sending  process in
 *         the communication space defined by COMM.
 *
 * RTAG    (local input)                 int
 *         On entry,  STAG specifies the message tag to be used for this
 *         communication operation.
 *
 * COMM    (local input)                 MPI_Comm
 *         The MPI communicator identifying the communication space.
 *
 * ---------------------------------------------------------------------
 */ 
START_TRACE( RECV )

/*
 * .. Local Variables ..
 */
   MPI_Status                 status;
#ifdef HPL_USE_MPI_DATATYPE
   MPI_Datatype               type;
#endif
   int                        ierr;
/* ..
 * .. Executable Statements ..
 */
   if( RCOUNT <= 0 ) return( HPL_SUCCESS );

#ifdef HPL_USE_MPI_DATATYPE
checkMpiThread    ierr =      MPI_Type_contiguous( RCOUNT, MPI_DOUBLE, &type );
   if( ierr == MPI_SUCCESS ) {
checkMpiThread       ierr =   MPI_Type_commit( &type );
   }
   if( ierr == MPI_SUCCESS ) {
checkMpiThread       ierr =   MPI_Recv( (void *)(RBUF), 1, type, SRC, RTAG, COMM,
                         &status );
   }
   if( ierr == MPI_SUCCESS ) {
checkMpiThread       ierr =   MPI_Type_free( &type );
   }
#else
checkMpiThread    ierr = MPI_Recv( (void *)(RBUF), RCOUNT, MPI_DOUBLE, SRC, RTAG,
                    COMM, &status );
#endif

END_TRACE

   return( ( ierr == MPI_SUCCESS ? HPL_SUCCESS : HPL_FAILURE ) );
/*
 * End of HPL_recv
 */
}

/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtomcrypt.org
 */
#include "tomcrypt.h"

/**
   @file cbc_done.c
   CBC implementation, finish chain, Tom St Denis
*/

#ifdef CBC

/** Terminate the chain
  @param cbc    The CBC chain to terminate
  @return CRYPT_OK on success
*/
int cbc_done(symmetric_CBC *cbc)
{
   int err;
   LTC_ARGCHK(cbc != NULL);

   if ((err = cipher_is_valid(cbc->cipher)) != CRYPT_OK) {
      return err;
   }
   cipher_descriptor[cbc->cipher].done(&cbc->key);
   return CRYPT_OK;
}

   

#endif

/* $Source: /usr/local/dslrepos/uClinux-dist/user/dropbear-0.48.1/libtomcrypt/src/modes/cbc/cbc_done.c,v $ */
/* $Revision: 1.1 $ */
/* $Date: 2006/06/08 13:45:19 $ */

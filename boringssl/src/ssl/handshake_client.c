/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
/* ====================================================================
 * Copyright (c) 1998-2007 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */
/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 *
 * Portions of the attached software ("Contribution") are developed by 
 * SUN MICROSYSTEMS, INC., and are contributed to the OpenSSL project.
 *
 * The Contribution is licensed pursuant to the OpenSSL open source
 * license provided above.
 *
 * ECC cipher suite support in OpenSSL originally written by
 * Vipul Gupta and Sumit Gupta of Sun Microsystems Laboratories.
 *
 */
/* ====================================================================
 * Copyright 2005 Nokia. All rights reserved.
 *
 * The portions of the attached software ("Contribution") is developed by
 * Nokia Corporation and is licensed pursuant to the OpenSSL open source
 * license.
 *
 * The Contribution, originally written by Mika Kousa and Pasi Eronen of
 * Nokia Corporation, consists of the "PSK" (Pre-Shared Key) ciphersuites
 * support (see RFC 4279) to OpenSSL.
 *
 * No patent licenses or other rights except those expressly stated in
 * the OpenSSL open source license shall be deemed granted or received
 * expressly, by implication, estoppel, or otherwise.
 *
 * No assurances are provided by Nokia that the Contribution does not
 * infringe the patent or other intellectual property rights of any third
 * party or that the license provides you with all the necessary rights
 * to make use of the Contribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. IN
 * ADDITION TO THE DISCLAIMERS INCLUDED IN THE LICENSE, NOKIA
 * SPECIFICALLY DISCLAIMS ANY LIABILITY FOR CLAIMS BROUGHT BY YOU OR ANY
 * OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS OR
 * OTHERWISE.
 */

#include <openssl/ssl.h>

#include <assert.h>
#include <string.h>

#include <openssl/bn.h>
#include <openssl/buf.h>
#include <openssl/bytestring.h>
#include <openssl/dh.h>
#include <openssl/ec_key.h>
#include <openssl/ecdsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/mem.h>
#include <openssl/rand.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include "internal.h"
#include "../crypto/dh/internal.h"


static int ssl3_send_client_hello(SSL *ssl);
static int dtls1_get_hello_verify(SSL *ssl);
static int ssl3_get_server_hello(SSL *ssl);
static int ssl3_get_server_certificate(SSL *ssl);
static int ssl3_get_cert_status(SSL *ssl);
static int ssl3_verify_server_cert(SSL *ssl);
static int ssl3_get_server_key_exchange(SSL *ssl);
static int ssl3_get_certificate_request(SSL *ssl);
static int ssl3_get_server_hello_done(SSL *ssl);
static int ssl3_send_client_certificate(SSL *ssl);
static int ssl3_send_client_key_exchange(SSL *ssl);
static int ssl3_send_cert_verify(SSL *ssl);
static int ssl3_send_next_proto(SSL *ssl);
static int ssl3_send_channel_id(SSL *ssl);
static int ssl3_get_new_session_ticket(SSL *ssl);

int ssl3_connect(SSL *ssl) {
  int ret = -1;
  int state, skip = 0;

  assert(ssl->handshake_func == ssl3_connect);
  assert(!ssl->server);

  for (;;) {
    state = ssl->state;

    switch (ssl->state) {
      case SSL_ST_CONNECT:
        ssl_do_info_callback(ssl, SSL_CB_HANDSHAKE_START, 1);

        if (!ssl->method->begin_handshake(ssl)) {
          ret = -1;
          goto end;
        }

        if (!ssl_init_wbio_buffer(ssl)) {
          ret = -1;
          goto end;
        }

        ssl->state = SSL3_ST_CW_CLNT_HELLO_A;
        break;

      case SSL3_ST_CW_CLNT_HELLO_A:
      case SSL3_ST_CW_CLNT_HELLO_B:
        ret = ssl3_send_client_hello(ssl);
        if (ret <= 0) {
          goto end;
        }

        if (!SSL_IS_DTLS(ssl) || ssl->d1->send_cookie) {
          ssl->s3->tmp.next_state = SSL3_ST_CR_SRVR_HELLO_A;
        } else {
          ssl->s3->tmp.next_state = DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A;
        }
        ssl->state = SSL3_ST_CW_FLUSH;
        break;

      case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A:
        assert(SSL_IS_DTLS(ssl));
        ret = dtls1_get_hello_verify(ssl);
        if (ret <= 0) {
          goto end;
        }
        if (ssl->d1->send_cookie) {
          ssl->method->received_flight(ssl);
          ssl->state = SSL3_ST_CW_CLNT_HELLO_A;
        } else {
          ssl->state = SSL3_ST_CR_SRVR_HELLO_A;
        }
        break;

      case SSL3_ST_CR_SRVR_HELLO_A:
        ret = ssl3_get_server_hello(ssl);
        if (ret <= 0) {
          goto end;
        }

        if (ssl->hit) {
          ssl->state = SSL3_ST_CR_SESSION_TICKET_A;
        } else {
          ssl->state = SSL3_ST_CR_CERT_A;
        }
        break;

      case SSL3_ST_CR_CERT_A:
        if (ssl_cipher_uses_certificate_auth(ssl->s3->tmp.new_cipher)) {
          ret = ssl3_get_server_certificate(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CR_CERT_STATUS_A;
        break;

      case SSL3_ST_CR_CERT_STATUS_A:
        if (ssl->s3->tmp.certificate_status_expected) {
          ret = ssl3_get_cert_status(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_VERIFY_SERVER_CERT;
        break;

      case SSL3_ST_VERIFY_SERVER_CERT:
        if (ssl_cipher_uses_certificate_auth(ssl->s3->tmp.new_cipher)) {
          ret = ssl3_verify_server_cert(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CR_KEY_EXCH_A;
        break;

      case SSL3_ST_CR_KEY_EXCH_A:
        ret = ssl3_get_server_key_exchange(ssl);
        if (ret <= 0) {
          goto end;
        }
        ssl->state = SSL3_ST_CR_CERT_REQ_A;
        break;

      case SSL3_ST_CR_CERT_REQ_A:
        if (ssl_cipher_uses_certificate_auth(ssl->s3->tmp.new_cipher)) {
          ret = ssl3_get_certificate_request(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CR_SRVR_DONE_A;
        break;

      case SSL3_ST_CR_SRVR_DONE_A:
        ret = ssl3_get_server_hello_done(ssl);
        if (ret <= 0) {
          goto end;
        }
        ssl->method->received_flight(ssl);
        ssl->state = SSL3_ST_CW_CERT_A;
        break;

      case SSL3_ST_CW_CERT_A:
      case SSL3_ST_CW_CERT_B:
      case SSL3_ST_CW_CERT_C:
      case SSL3_ST_CW_CERT_D:
        if (ssl->s3->tmp.cert_request) {
          ret = ssl3_send_client_certificate(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CW_KEY_EXCH_A;
        break;

      case SSL3_ST_CW_KEY_EXCH_A:
      case SSL3_ST_CW_KEY_EXCH_B:
        ret = ssl3_send_client_key_exchange(ssl);
        if (ret <= 0) {
          goto end;
        }
        ssl->state = SSL3_ST_CW_CERT_VRFY_A;
        break;

      case SSL3_ST_CW_CERT_VRFY_A:
      case SSL3_ST_CW_CERT_VRFY_B:
      case SSL3_ST_CW_CERT_VRFY_C:
        if (ssl->s3->tmp.cert_request) {
          ret = ssl3_send_cert_verify(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CW_CHANGE;
        break;

      case SSL3_ST_CW_CHANGE:
        ret = ssl->method->send_change_cipher_spec(ssl);
        if (ret <= 0) {
          goto end;
        }

        ssl->state = SSL3_ST_CW_NEXT_PROTO_A;

        if (!tls1_change_cipher_state(ssl, SSL3_CHANGE_CIPHER_CLIENT_WRITE)) {
          ret = -1;
          goto end;
        }

        break;

      case SSL3_ST_CW_NEXT_PROTO_A:
      case SSL3_ST_CW_NEXT_PROTO_B:
        if (ssl->s3->next_proto_neg_seen) {
          ret = ssl3_send_next_proto(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CW_CHANNEL_ID_A;
        break;

      case SSL3_ST_CW_CHANNEL_ID_A:
      case SSL3_ST_CW_CHANNEL_ID_B:
        if (ssl->s3->tlsext_channel_id_valid) {
          ret = ssl3_send_channel_id(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CW_FINISHED_A;
        break;

      case SSL3_ST_CW_FINISHED_A:
      case SSL3_ST_CW_FINISHED_B:
        ret = ssl3_send_finished(ssl, SSL3_ST_CW_FINISHED_A,
                                 SSL3_ST_CW_FINISHED_B);
        if (ret <= 0) {
          goto end;
        }
        ssl->state = SSL3_ST_CW_FLUSH;

        if (ssl->hit) {
          ssl->s3->tmp.next_state = SSL_ST_OK;
        } else {
          /* This is a non-resumption handshake. If it involves ChannelID, then
           * record the handshake hashes at this point in the session so that
           * any resumption of this session with ChannelID can sign those
           * hashes. */
          ret = tls1_record_handshake_hashes_for_channel_id(ssl);
          if (ret <= 0) {
            goto end;
          }
          if ((SSL_get_mode(ssl) & SSL_MODE_ENABLE_FALSE_START) &&
              ssl3_can_false_start(ssl) &&
              /* No False Start on renegotiation (would complicate the state
               * machine). */
              !ssl->s3->initial_handshake_complete) {
            ssl->s3->tmp.next_state = SSL3_ST_FALSE_START;
          } else {
            ssl->s3->tmp.next_state = SSL3_ST_CR_SESSION_TICKET_A;
          }
        }
        break;

      case SSL3_ST_FALSE_START:
        ssl->state = SSL3_ST_CR_SESSION_TICKET_A;
        ssl->s3->tmp.in_false_start = 1;

        ssl_free_wbio_buffer(ssl);
        ret = 1;
        goto end;

      case SSL3_ST_CR_SESSION_TICKET_A:
        if (ssl->tlsext_ticket_expected) {
          ret = ssl3_get_new_session_ticket(ssl);
          if (ret <= 0) {
            goto end;
          }
        } else {
          skip = 1;
        }
        ssl->state = SSL3_ST_CR_CHANGE;
        break;

      case SSL3_ST_CR_CHANGE:
        ret = ssl->method->read_change_cipher_spec(ssl);
        if (ret <= 0) {
          goto end;
        }

        if (!tls1_change_cipher_state(ssl, SSL3_CHANGE_CIPHER_CLIENT_READ)) {
          ret = -1;
          goto end;
        }
        ssl->state = SSL3_ST_CR_FINISHED_A;
        break;

      case SSL3_ST_CR_FINISHED_A:
        ret = ssl3_get_finished(ssl);
        if (ret <= 0) {
          goto end;
        }
        ssl->method->received_flight(ssl);

        if (ssl->hit) {
          ssl->state = SSL3_ST_CW_CHANGE;
        } else {
          ssl->state = SSL_ST_OK;
        }
        break;

      case SSL3_ST_CW_FLUSH:
        if (BIO_flush(ssl->wbio) <= 0) {
          ssl->rwstate = SSL_WRITING;
          ret = -1;
          goto end;
        }
        ssl->state = ssl->s3->tmp.next_state;
        if (ssl->state != SSL_ST_OK) {
          ssl->method->expect_flight(ssl);
        }
        break;

      case SSL_ST_OK:
        /* clean a few things up */
        ssl3_cleanup_key_block(ssl);

        ssl->method->finish_handshake(ssl);

        /* Remove write buffering now. */
        ssl_free_wbio_buffer(ssl);

        const int is_initial_handshake = !ssl->s3->initial_handshake_complete;

        ssl->s3->tmp.in_false_start = 0;
        ssl->s3->initial_handshake_complete = 1;

        if (is_initial_handshake) {
          /* Renegotiations do not participate in session resumption. */
          ssl_update_cache(ssl, SSL_SESS_CACHE_CLIENT);
        }

        ret = 1;
        ssl_do_info_callback(ssl, SSL_CB_HANDSHAKE_DONE, 1);
        goto end;

      default:
        OPENSSL_PUT_ERROR(SSL, SSL_R_UNKNOWN_STATE);
        ret = -1;
        goto end;
    }

    if (!ssl->s3->tmp.reuse_message && !skip && ssl->state != state) {
      int new_state = ssl->state;
      ssl->state = state;
      ssl_do_info_callback(ssl, SSL_CB_CONNECT_LOOP, 1);
      ssl->state = new_state;
    }
    skip = 0;
  }

end:
  ssl_do_info_callback(ssl, SSL_CB_CONNECT_EXIT, ret);
  return ret;
}

static int ssl3_write_client_cipher_list(SSL *ssl, CBB *out,
                                         uint16_t min_version,
                                         uint16_t max_version) {
  /* Prepare disabled cipher masks. */
  ssl_set_client_disabled(ssl);

  CBB child;
  if (!CBB_add_u16_length_prefixed(out, &child)) {
    return 0;
  }

  STACK_OF(SSL_CIPHER) *ciphers = SSL_get_ciphers(ssl);

  int any_enabled = 0;
  size_t i;
  for (i = 0; i < sk_SSL_CIPHER_num(ciphers); i++) {
    const SSL_CIPHER *cipher = sk_SSL_CIPHER_value(ciphers, i);
    /* Skip disabled ciphers */
    if ((cipher->algorithm_mkey & ssl->cert->mask_k) ||
        (cipher->algorithm_auth & ssl->cert->mask_a)) {
      continue;
    }
    if (SSL_CIPHER_get_min_version(cipher) > max_version ||
        SSL_CIPHER_get_max_version(cipher) < min_version) {
      continue;
    }
    any_enabled = 1;
    if (!CBB_add_u16(&child, ssl_cipher_get_value(cipher))) {
      return 0;
    }
  }

  /* If all ciphers were disabled, return the error to the caller. */
  if (!any_enabled) {
    OPENSSL_PUT_ERROR(SSL, SSL_R_NO_CIPHERS_AVAILABLE);
    return 0;
  }

  /* For SSLv3, the SCSV is added. Otherwise the renegotiation extension is
   * added. */
  if (ssl->client_version == SSL3_VERSION &&
      !ssl->s3->initial_handshake_complete) {
    if (!CBB_add_u16(&child, SSL3_CK_SCSV & 0xffff)) {
      return 0;
    }
    /* The renegotiation extension is required to be at index zero. */
    ssl->s3->tmp.extensions.sent |= (1u << 0);
  }

  if ((ssl->mode & SSL_MODE_SEND_FALLBACK_SCSV) &&
      !CBB_add_u16(&child, SSL3_CK_FALLBACK_SCSV & 0xffff)) {
    return 0;
  }

  return CBB_flush(out);
}

static int ssl3_send_client_hello(SSL *ssl) {
  if (ssl->state == SSL3_ST_CW_CLNT_HELLO_B) {
    return ssl->method->write_message(ssl);
  }

  /* The handshake buffer is reset on every ClientHello. Notably, in DTLS, we
   * may send multiple ClientHellos if we receive HelloVerifyRequest. */
  if (!ssl3_init_handshake_buffer(ssl)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
    return -1;
  }

  CBB cbb;
  CBB_zero(&cbb);

  uint16_t min_version, max_version;
  if (!ssl_get_version_range(ssl, &min_version, &max_version)) {
    goto err;
  }

  assert(ssl->state == SSL3_ST_CW_CLNT_HELLO_A);
  if (!ssl->s3->have_version) {
    ssl->version = ssl->method->version_to_wire(max_version);
    /* Only set |ssl->client_version| on the initial handshake. Renegotiations,
     * although locked to a version, reuse the value. When using the plain RSA
     * key exchange, the ClientHello version is checked in the premaster secret.
     * Some servers fail when this value changes. */
    ssl->client_version = ssl->version;
  }

  /* If the configured session has expired or was created at a disabled
   * version, drop it. */
  if (ssl->session != NULL) {
    uint16_t session_version =
        ssl->method->version_from_wire(ssl->session->ssl_version);
    if (ssl->session->session_id_length == 0 || ssl->session->not_resumable ||
        ssl->session->timeout < (long)(time(NULL) - ssl->session->time) ||
        session_version < min_version || session_version > max_version) {
      SSL_set_session(ssl, NULL);
    }
  }

  /* If resending the ClientHello in DTLS after a HelloVerifyRequest, don't
   * renegerate the client_random. The random must be reused. */
  if ((!SSL_IS_DTLS(ssl) || !ssl->d1->send_cookie) &&
      !ssl_fill_hello_random(ssl->s3->client_random,
                             sizeof(ssl->s3->client_random), 0 /* client */)) {
    goto err;
  }

  /* Renegotiations do not participate in session resumption. */
  int has_session = ssl->session != NULL &&
                    !ssl->s3->initial_handshake_complete;

  CBB body, child;
  if (!ssl->method->init_message(ssl, &cbb, &body, SSL3_MT_CLIENT_HELLO) ||
      !CBB_add_u16(&body, ssl->client_version) ||
      !CBB_add_bytes(&body, ssl->s3->client_random, SSL3_RANDOM_SIZE) ||
      !CBB_add_u8_length_prefixed(&body, &child) ||
      (has_session &&
       !CBB_add_bytes(&child, ssl->session->session_id,
                      ssl->session->session_id_length))) {
    goto err;
  }

  if (SSL_IS_DTLS(ssl)) {
    if (!CBB_add_u8_length_prefixed(&body, &child) ||
        !CBB_add_bytes(&child, ssl->d1->cookie, ssl->d1->cookie_len)) {
      goto err;
    }
  }

  size_t header_len =
      SSL_IS_DTLS(ssl) ? DTLS1_HM_HEADER_LENGTH : SSL3_HM_HEADER_LENGTH;
  if (!ssl3_write_client_cipher_list(ssl, &body, min_version, max_version) ||
      !CBB_add_u8(&body, 1 /* one compression method */) ||
      !CBB_add_u8(&body, 0 /* null compression */) ||
      !ssl_add_clienthello_tlsext(ssl, &body, header_len + CBB_len(&body)) ||
      !ssl->method->finish_message(ssl, &cbb)) {
    goto err;
  }

  ssl->state = SSL3_ST_CW_CLNT_HELLO_B;
  return ssl->method->write_message(ssl);

err:
  CBB_cleanup(&cbb);
  return -1;
}

static int dtls1_get_hello_verify(SSL *ssl) {
  long n;
  int al, ok = 0;
  CBS hello_verify_request, cookie;
  uint16_t server_version;

  n = ssl->method->ssl_get_message(ssl, -1, ssl_hash_message, &ok);

  if (!ok) {
    return n;
  }

  if (ssl->s3->tmp.message_type != DTLS1_MT_HELLO_VERIFY_REQUEST) {
    ssl->d1->send_cookie = 0;
    ssl->s3->tmp.reuse_message = 1;
    return 1;
  }

  CBS_init(&hello_verify_request, ssl->init_msg, n);

  if (!CBS_get_u16(&hello_verify_request, &server_version) ||
      !CBS_get_u8_length_prefixed(&hello_verify_request, &cookie) ||
      CBS_len(&hello_verify_request) != 0) {
    al = SSL_AD_DECODE_ERROR;
    OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
    goto f_err;
  }

  if (CBS_len(&cookie) > sizeof(ssl->d1->cookie)) {
    al = SSL_AD_ILLEGAL_PARAMETER;
    goto f_err;
  }

  memcpy(ssl->d1->cookie, CBS_data(&cookie), CBS_len(&cookie));
  ssl->d1->cookie_len = CBS_len(&cookie);

  ssl->d1->send_cookie = 1;
  return 1;

f_err:
  ssl3_send_alert(ssl, SSL3_AL_FATAL, al);
  return -1;
}

static int ssl3_get_server_hello(SSL *ssl) {
  STACK_OF(SSL_CIPHER) *sk;
  const SSL_CIPHER *c;
  CERT *ct = ssl->cert;
  int al = SSL_AD_INTERNAL_ERROR, ok;
  long n;
  CBS server_hello, server_random, session_id;
  uint16_t server_wire_version, server_version, cipher_suite;
  uint8_t compression_method;

  n = ssl->method->ssl_get_message(ssl, SSL3_MT_SERVER_HELLO, ssl_hash_message,
                                   &ok);

  if (!ok) {
    uint32_t err = ERR_peek_error();
    if (ERR_GET_LIB(err) == ERR_LIB_SSL &&
        ERR_GET_REASON(err) == SSL_R_SSLV3_ALERT_HANDSHAKE_FAILURE) {
      /* Add a dedicated error code to the queue for a handshake_failure alert
       * in response to ClientHello. This matches NSS's client behavior and
       * gives a better error on a (probable) failure to negotiate initial
       * parameters. Note: this error code comes after the original one.
       *
       * See https://crbug.com/446505. */
      OPENSSL_PUT_ERROR(SSL, SSL_R_HANDSHAKE_FAILURE_ON_CLIENT_HELLO);
    }
    return n;
  }

  CBS_init(&server_hello, ssl->init_msg, n);

  if (!CBS_get_u16(&server_hello, &server_wire_version) ||
      !CBS_get_bytes(&server_hello, &server_random, SSL3_RANDOM_SIZE) ||
      !CBS_get_u8_length_prefixed(&server_hello, &session_id) ||
      CBS_len(&session_id) > SSL3_SESSION_ID_SIZE ||
      !CBS_get_u16(&server_hello, &cipher_suite) ||
      !CBS_get_u8(&server_hello, &compression_method)) {
    al = SSL_AD_DECODE_ERROR;
    OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
    goto f_err;
  }

  server_version = ssl->method->version_from_wire(server_wire_version);

  assert(ssl->s3->have_version == ssl->s3->initial_handshake_complete);
  if (!ssl->s3->have_version) {
    uint16_t min_version, max_version;
    if (!ssl_get_version_range(ssl, &min_version, &max_version) ||
        server_version < min_version || server_version > max_version) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_UNSUPPORTED_PROTOCOL);
      al = SSL_AD_PROTOCOL_VERSION;
      goto f_err;
    }
    ssl->version = server_wire_version;
    ssl->s3->enc_method = ssl3_get_enc_method(server_version);
    assert(ssl->s3->enc_method != NULL);
    /* At this point, the connection's version is known and ssl->version is
     * fixed. Begin enforcing the record-layer version. */
    ssl->s3->have_version = 1;
  } else if (server_wire_version != ssl->version) {
    OPENSSL_PUT_ERROR(SSL, SSL_R_WRONG_SSL_VERSION);
    al = SSL_AD_PROTOCOL_VERSION;
    goto f_err;
  }

  /* Copy over the server random. */
  memcpy(ssl->s3->server_random, CBS_data(&server_random), SSL3_RANDOM_SIZE);

  assert(ssl->session == NULL || ssl->session->session_id_length > 0);
  if (!ssl->s3->initial_handshake_complete && ssl->session != NULL &&
      CBS_mem_equal(&session_id, ssl->session->session_id,
                    ssl->session->session_id_length)) {
    if (ssl->sid_ctx_length != ssl->session->sid_ctx_length ||
        memcmp(ssl->session->sid_ctx, ssl->sid_ctx, ssl->sid_ctx_length)) {
      /* actually a client application bug */
      al = SSL_AD_ILLEGAL_PARAMETER;
      OPENSSL_PUT_ERROR(SSL,
                        SSL_R_ATTEMPT_TO_REUSE_SESSION_IN_DIFFERENT_CONTEXT);
      goto f_err;
    }
    ssl->hit = 1;
  } else {
    /* The session wasn't resumed. Create a fresh SSL_SESSION to
     * fill out. */
    ssl->hit = 0;
    if (!ssl_get_new_session(ssl, 0 /* client */)) {
      goto f_err;
    }
    /* Note: session_id could be empty. */
    ssl->session->session_id_length = CBS_len(&session_id);
    memcpy(ssl->session->session_id, CBS_data(&session_id),
           CBS_len(&session_id));
  }

  c = SSL_get_cipher_by_value(cipher_suite);
  if (c == NULL) {
    /* unknown cipher */
    al = SSL_AD_ILLEGAL_PARAMETER;
    OPENSSL_PUT_ERROR(SSL, SSL_R_UNKNOWN_CIPHER_RETURNED);
    goto f_err;
  }
  /* If the cipher is disabled then we didn't sent it in the ClientHello, so if
   * the server selected it, it's an error. */
  if ((c->algorithm_mkey & ct->mask_k) || (c->algorithm_auth & ct->mask_a) ||
      SSL_CIPHER_get_min_version(c) > ssl3_protocol_version(ssl) ||
      SSL_CIPHER_get_max_version(c) < ssl3_protocol_version(ssl)) {
    al = SSL_AD_ILLEGAL_PARAMETER;
    OPENSSL_PUT_ERROR(SSL, SSL_R_WRONG_CIPHER_RETURNED);
    goto f_err;
  }

  sk = ssl_get_ciphers_by_id(ssl);
  if (!sk_SSL_CIPHER_find(sk, NULL, c)) {
    /* we did not say we would use this cipher */
    al = SSL_AD_ILLEGAL_PARAMETER;
    OPENSSL_PUT_ERROR(SSL, SSL_R_WRONG_CIPHER_RETURNED);
    goto f_err;
  }

  if (ssl->hit) {
    if (ssl->session->cipher != c) {
      al = SSL_AD_ILLEGAL_PARAMETER;
      OPENSSL_PUT_ERROR(SSL, SSL_R_OLD_SESSION_CIPHER_NOT_RETURNED);
      goto f_err;
    }
    if (ssl->session->ssl_version != ssl->version) {
      al = SSL_AD_ILLEGAL_PARAMETER;
      OPENSSL_PUT_ERROR(SSL, SSL_R_OLD_SESSION_VERSION_NOT_RETURNED);
      goto f_err;
    }
  } else {
    ssl->session->cipher = c;
  }
  ssl->s3->tmp.new_cipher = c;

  /* Now that the cipher is known, initialize the handshake hash. */
  if (!ssl3_init_handshake_hash(ssl)) {
    goto f_err;
  }

  /* If doing a full handshake, the server may request a client certificate
   * which requires hashing the handshake transcript. Otherwise, the handshake
   * buffer may be released. */
  if (ssl->hit || !ssl_cipher_uses_certificate_auth(ssl->s3->tmp.new_cipher)) {
    ssl3_free_handshake_buffer(ssl);
  }

  /* Only the NULL compression algorithm is supported. */
  if (compression_method != 0) {
    al = SSL_AD_ILLEGAL_PARAMETER;
    OPENSSL_PUT_ERROR(SSL, SSL_R_UNSUPPORTED_COMPRESSION_ALGORITHM);
    goto f_err;
  }

  /* TLS extensions */
  if (!ssl_parse_serverhello_tlsext(ssl, &server_hello)) {
    OPENSSL_PUT_ERROR(SSL, SSL_R_PARSE_TLSEXT);
    goto err;
  }

  /* There should be nothing left over in the record. */
  if (CBS_len(&server_hello) != 0) {
    /* wrong packet length */
    al = SSL_AD_DECODE_ERROR;
    OPENSSL_PUT_ERROR(SSL, SSL_R_BAD_PACKET_LENGTH);
    goto f_err;
  }

  if (ssl->hit &&
      ssl->s3->tmp.extended_master_secret !=
          ssl->session->extended_master_secret) {
    al = SSL_AD_HANDSHAKE_FAILURE;
    if (ssl->session->extended_master_secret) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_RESUMED_EMS_SESSION_WITHOUT_EMS_EXTENSION);
    } else {
      OPENSSL_PUT_ERROR(SSL, SSL_R_RESUMED_NON_EMS_SESSION_WITH_EMS_EXTENSION);
    }
    goto f_err;
  }

  return 1;

f_err:
  ssl3_send_alert(ssl, SSL3_AL_FATAL, al);
err:
  return -1;
}

/* ssl3_check_leaf_certificate returns one if |leaf| is a suitable leaf server
 * certificate for |ssl|. Otherwise, it returns zero and pushes an error on the
 * error queue. */
static int ssl3_check_leaf_certificate(SSL *ssl, X509 *leaf) {
  int ret = 0;
  EVP_PKEY *pkey = X509_get_pubkey(leaf);
  if (pkey == NULL) {
    goto err;
  }

  /* Check the certificate's type matches the cipher. */
  const SSL_CIPHER *cipher = ssl->s3->tmp.new_cipher;
  int expected_type = ssl_cipher_get_key_type(cipher);
  assert(expected_type != EVP_PKEY_NONE);
  if (pkey->type != expected_type) {
    OPENSSL_PUT_ERROR(SSL, SSL_R_WRONG_CERTIFICATE_TYPE);
    goto err;
  }

  if (cipher->algorithm_auth & SSL_aECDSA) {
    /* TODO(davidben): This behavior is preserved from upstream. Should key
     * usages be checked in other cases as well? */
    /* This call populates the ex_flags field correctly */
    X509_check_purpose(leaf, -1, 0);
    if ((leaf->ex_flags & EXFLAG_KUSAGE) &&
        !(leaf->ex_kusage & X509v3_KU_DIGITAL_SIGNATURE)) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_ECC_CERT_NOT_FOR_SIGNING);
      goto err;
    }

    if (!tls1_check_ec_cert(ssl, leaf)) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_BAD_ECC_CERT);
      goto err;
    }
  }

  ret = 1;

err:
  EVP_PKEY_free(pkey);
  return ret;
}

static int ssl3_get_server_certificate(SSL *ssl) {
  int al, ok, ret = -1;
  unsigned long n;
  X509 *x = NULL;
  STACK_OF(X509) *sk = NULL;
  EVP_PKEY *pkey = NULL;
  CBS cbs, certificate_list;
  const uint8_t *data;

  n = ssl->method->ssl_get_message(ssl, SSL3_MT_CERTIFICATE, ssl_hash_message,
                                   &ok);

  if (!ok) {
    return n;
  }

  CBS_init(&cbs, ssl->init_msg, n);

  sk = sk_X509_new_null();
  if (sk == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
    goto err;
  }

  if (!CBS_get_u24_length_prefixed(&cbs, &certificate_list) ||
      CBS_len(&certificate_list) == 0 ||
      CBS_len(&cbs) != 0) {
    al = SSL_AD_DECODE_ERROR;
    OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
    goto f_err;
  }

  while (CBS_len(&certificate_list) > 0) {
    CBS certificate;
    if (!CBS_get_u24_length_prefixed(&certificate_list, &certificate)) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_CERT_LENGTH_MISMATCH);
      goto f_err;
    }
    /* A u24 length cannot overflow a long. */
    data = CBS_data(&certificate);
    x = d2i_X509(NULL, &data, (long)CBS_len(&certificate));
    if (x == NULL) {
      al = SSL_AD_BAD_CERTIFICATE;
      OPENSSL_PUT_ERROR(SSL, ERR_R_ASN1_LIB);
      goto f_err;
    }
    if (data != CBS_data(&certificate) + CBS_len(&certificate)) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_CERT_LENGTH_MISMATCH);
      goto f_err;
    }
    if (!sk_X509_push(sk, x)) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      goto err;
    }
    x = NULL;
  }

  X509 *leaf = sk_X509_value(sk, 0);
  if (!ssl3_check_leaf_certificate(ssl, leaf)) {
    al = SSL_AD_ILLEGAL_PARAMETER;
    goto f_err;
  }

  /* NOTE: Unlike the server half, the client's copy of |cert_chain| includes
   * the leaf. */
  sk_X509_pop_free(ssl->session->cert_chain, X509_free);
  ssl->session->cert_chain = sk;
  sk = NULL;

  X509_free(ssl->session->peer);
  ssl->session->peer = X509_up_ref(leaf);

  ssl->session->verify_result = ssl->verify_result;

  ret = 1;

  if (0) {
  f_err:
    ssl3_send_alert(ssl, SSL3_AL_FATAL, al);
  }

err:
  EVP_PKEY_free(pkey);
  X509_free(x);
  sk_X509_pop_free(sk, X509_free);
  return ret;
}

static int ssl3_get_cert_status(SSL *ssl) {
  int ok, al;
  long n;
  CBS certificate_status, ocsp_response;
  uint8_t status_type;

  n = ssl->method->ssl_get_message(ssl, -1, ssl_hash_message, &ok);

  if (!ok) {
    return n;
  }

  if (ssl->s3->tmp.message_type != SSL3_MT_CERTIFICATE_STATUS) {
    /* A server may send status_request in ServerHello and then change
     * its mind about sending CertificateStatus. */
    ssl->s3->tmp.reuse_message = 1;
    return 1;
  }

  CBS_init(&certificate_status, ssl->init_msg, n);
  if (!CBS_get_u8(&certificate_status, &status_type) ||
      status_type != TLSEXT_STATUSTYPE_ocsp ||
      !CBS_get_u24_length_prefixed(&certificate_status, &ocsp_response) ||
      CBS_len(&ocsp_response) == 0 ||
      CBS_len(&certificate_status) != 0) {
    al = SSL_AD_DECODE_ERROR;
    OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
    goto f_err;
  }

  if (!CBS_stow(&ocsp_response, &ssl->session->ocsp_response,
                &ssl->session->ocsp_response_length)) {
    al = SSL_AD_INTERNAL_ERROR;
    OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
    goto f_err;
  }
  return 1;

f_err:
  ssl3_send_alert(ssl, SSL3_AL_FATAL, al);
  return -1;
}

static int ssl3_verify_server_cert(SSL *ssl) {
  int ret = ssl_verify_cert_chain(ssl, ssl->session->cert_chain);
  if (ssl->verify_mode != SSL_VERIFY_NONE && ret <= 0) {
    int al = ssl_verify_alarm_type(ssl->verify_result);
    ssl3_send_alert(ssl, SSL3_AL_FATAL, al);
    OPENSSL_PUT_ERROR(SSL, SSL_R_CERTIFICATE_VERIFY_FAILED);
  } else {
    ret = 1;
    ERR_clear_error(); /* but we keep ssl->verify_result */
  }

  return ret;
}

static int ssl3_get_server_key_exchange(SSL *ssl) {
  int al, ok;
  EVP_PKEY *pkey = NULL;
  DH *dh = NULL;
  EC_KEY *ecdh = NULL;
  EC_POINT *srvr_ecpoint = NULL;

  long n = ssl->method->ssl_get_message(ssl, -1, ssl_hash_message, &ok);
  if (!ok) {
    return n;
  }

  if (ssl->s3->tmp.message_type != SSL3_MT_SERVER_KEY_EXCHANGE) {
    if (ssl_cipher_requires_server_key_exchange(ssl->s3->tmp.new_cipher)) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_UNEXPECTED_MESSAGE);
      ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_UNEXPECTED_MESSAGE);
      return -1;
    }

    /* In plain PSK ciphersuite, ServerKeyExchange may be omitted to send no
     * identity hint. */
    if (ssl->s3->tmp.new_cipher->algorithm_auth & SSL_aPSK) {
      /* TODO(davidben): This should be reset in one place with the rest of the
       * handshake state. */
      OPENSSL_free(ssl->s3->tmp.peer_psk_identity_hint);
      ssl->s3->tmp.peer_psk_identity_hint = NULL;
    }
    ssl->s3->tmp.reuse_message = 1;
    return 1;
  }

  /* Retain a copy of the original CBS to compute the signature over. */
  CBS server_key_exchange;
  CBS_init(&server_key_exchange, ssl->init_msg, n);
  CBS server_key_exchange_orig = server_key_exchange;

  uint32_t alg_k = ssl->s3->tmp.new_cipher->algorithm_mkey;
  uint32_t alg_a = ssl->s3->tmp.new_cipher->algorithm_auth;

  if (alg_a & SSL_aPSK) {
    CBS psk_identity_hint;

    /* Each of the PSK key exchanges begins with a psk_identity_hint. */
    if (!CBS_get_u16_length_prefixed(&server_key_exchange,
                                     &psk_identity_hint)) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      goto f_err;
    }

    /* Store PSK identity hint for later use, hint is used in
     * ssl3_send_client_key_exchange.  Assume that the maximum length of a PSK
     * identity hint can be as long as the maximum length of a PSK identity.
     * Also do not allow NULL characters; identities are saved as C strings.
     *
     * TODO(davidben): Should invalid hints be ignored? It's a hint rather than
     * a specific identity. */
    if (CBS_len(&psk_identity_hint) > PSK_MAX_IDENTITY_LEN ||
        CBS_contains_zero_byte(&psk_identity_hint)) {
      al = SSL_AD_HANDSHAKE_FAILURE;
      OPENSSL_PUT_ERROR(SSL, SSL_R_DATA_LENGTH_TOO_LONG);
      goto f_err;
    }

    /* Save the identity hint as a C string. */
    if (!CBS_strdup(&psk_identity_hint, &ssl->s3->tmp.peer_psk_identity_hint)) {
      al = SSL_AD_INTERNAL_ERROR;
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      goto f_err;
    }
  }

  if (alg_k & SSL_kDHE) {
    CBS dh_p, dh_g, dh_Ys;
    if (!CBS_get_u16_length_prefixed(&server_key_exchange, &dh_p) ||
        CBS_len(&dh_p) == 0 ||
        !CBS_get_u16_length_prefixed(&server_key_exchange, &dh_g) ||
        CBS_len(&dh_g) == 0 ||
        !CBS_get_u16_length_prefixed(&server_key_exchange, &dh_Ys) ||
        CBS_len(&dh_Ys) == 0) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      goto f_err;
    }

    dh = DH_new();
    if (dh == NULL) {
      goto err;
    }

    dh->p = BN_bin2bn(CBS_data(&dh_p), CBS_len(&dh_p), NULL);
    dh->g = BN_bin2bn(CBS_data(&dh_g), CBS_len(&dh_g), NULL);
    if (dh->p == NULL || dh->g == NULL) {
      goto err;
    }

    ssl->session->key_exchange_info = DH_num_bits(dh);
    if (ssl->session->key_exchange_info < 1024) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_BAD_DH_P_LENGTH);
      goto err;
    } else if (ssl->session->key_exchange_info > 4096) {
      /* Overly large DHE groups are prohibitively expensive, so enforce a limit
       * to prevent a server from causing us to perform too expensive of a
       * computation. */
      OPENSSL_PUT_ERROR(SSL, SSL_R_DH_P_TOO_LONG);
      goto err;
    }

    SSL_ECDH_CTX_init_for_dhe(&ssl->s3->tmp.ecdh_ctx, dh);
    dh = NULL;

    /* Save the peer public key for later. */
    size_t peer_key_len;
    if (!CBS_stow(&dh_Ys, &ssl->s3->tmp.peer_key, &peer_key_len)) {
      goto err;
    }
    /* |dh_Ys| was initialized with CBS_get_u16_length_prefixed, so peer_key_len
     * fits in a uint16_t. */
    assert(sizeof(ssl->s3->tmp.peer_key_len) == 2 && peer_key_len <= 0xffff);
    ssl->s3->tmp.peer_key_len = (uint16_t)peer_key_len;
  } else if (alg_k & SSL_kECDHE) {
    /* Parse the server parameters. */
    uint8_t group_type;
    uint16_t group_id;
    CBS point;
    if (!CBS_get_u8(&server_key_exchange, &group_type) ||
        group_type != NAMED_CURVE_TYPE ||
        !CBS_get_u16(&server_key_exchange, &group_id) ||
        !CBS_get_u8_length_prefixed(&server_key_exchange, &point)) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      goto f_err;
    }
    ssl->session->key_exchange_info = group_id;

    /* Ensure the group is consistent with preferences. */
    if (!tls1_check_group_id(ssl, group_id)) {
      al = SSL_AD_ILLEGAL_PARAMETER;
      OPENSSL_PUT_ERROR(SSL, SSL_R_WRONG_CURVE);
      goto f_err;
    }

    /* Initialize ECDH and save the peer public key for later. */
    size_t peer_key_len;
    if (!SSL_ECDH_CTX_init(&ssl->s3->tmp.ecdh_ctx, group_id) ||
        !CBS_stow(&point, &ssl->s3->tmp.peer_key, &peer_key_len)) {
      goto err;
    }
    /* |point| was initialized with CBS_get_u8_length_prefixed, so peer_key_len
     * fits in a uint16_t. */
    assert(sizeof(ssl->s3->tmp.peer_key_len) == 2 && peer_key_len <= 0xffff);
    ssl->s3->tmp.peer_key_len = (uint16_t)peer_key_len;
  } else if (alg_k & SSL_kCECPQ1) {
    SSL_ECDH_CTX_init_for_cecpq1(&ssl->s3->tmp.ecdh_ctx);
    CBS key;
    if (!CBS_get_u16_length_prefixed(&server_key_exchange, &key)) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      goto f_err;
    }

    size_t peer_key_len;
    if (!CBS_stow(&key, &ssl->s3->tmp.peer_key, &peer_key_len)) {
      goto err;
    }
    /* |key| was initialized with CBS_get_u16_length_prefixed, so peer_key_len
     * fits in a uint16_t. */
    assert(sizeof(ssl->s3->tmp.peer_key_len) == 2 && peer_key_len <= 0xffff);
    ssl->s3->tmp.peer_key_len = (uint16_t)peer_key_len;
  } else if (!(alg_k & SSL_kPSK)) {
    al = SSL_AD_UNEXPECTED_MESSAGE;
    OPENSSL_PUT_ERROR(SSL, SSL_R_UNEXPECTED_MESSAGE);
    goto f_err;
  }

  /* At this point, |server_key_exchange| contains the signature, if any, while
   * |server_key_exchange_orig| contains the entire message. From that, derive
   * a CBS containing just the parameter. */
  CBS parameter;
  CBS_init(&parameter, CBS_data(&server_key_exchange_orig),
           CBS_len(&server_key_exchange_orig) - CBS_len(&server_key_exchange));

  /* ServerKeyExchange should be signed by the server's public key. */
  if (ssl_cipher_uses_certificate_auth(ssl->s3->tmp.new_cipher)) {
    pkey = X509_get_pubkey(ssl->session->peer);
    if (pkey == NULL) {
      goto err;
    }

    uint16_t signature_algorithm = 0;
    if (ssl3_protocol_version(ssl) >= TLS1_2_VERSION) {
      if (!CBS_get_u16(&server_key_exchange, &signature_algorithm)) {
        al = SSL_AD_DECODE_ERROR;
        OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
        goto f_err;
      }
      if (!tls12_check_peer_sigalg(ssl, &al, signature_algorithm, pkey)) {
        goto f_err;
      }
      ssl->s3->tmp.peer_signature_algorithm = signature_algorithm;
    } else if (pkey->type == EVP_PKEY_RSA) {
      signature_algorithm = SSL_SIGN_RSA_PKCS1_MD5_SHA1;
    } else if (pkey->type == EVP_PKEY_EC) {
      signature_algorithm = SSL_SIGN_ECDSA_SHA1;
    }

    /* The last field in |server_key_exchange| is the signature. */
    CBS signature;
    if (!CBS_get_u16_length_prefixed(&server_key_exchange, &signature) ||
        CBS_len(&server_key_exchange) != 0) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      goto f_err;
    }

    CBB transcript;
    uint8_t *transcript_data;
    size_t transcript_len;
    if (!CBB_init(&transcript, 2*SSL3_RANDOM_SIZE + CBS_len(&parameter)) ||
        !CBB_add_bytes(&transcript, ssl->s3->client_random, SSL3_RANDOM_SIZE) ||
        !CBB_add_bytes(&transcript, ssl->s3->server_random, SSL3_RANDOM_SIZE) ||
        !CBB_add_bytes(&transcript, CBS_data(&parameter), CBS_len(&parameter)) ||
        !CBB_finish(&transcript, &transcript_data, &transcript_len)) {
      CBB_cleanup(&transcript);
      al = SSL_AD_INTERNAL_ERROR;
      OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
      goto f_err;
    }

    int sig_ok = ssl_public_key_verify(
        ssl, CBS_data(&signature), CBS_len(&signature), signature_algorithm,
        pkey, transcript_data, transcript_len);
    OPENSSL_free(transcript_data);

#if defined(BORINGSSL_UNSAFE_FUZZER_MODE)
    sig_ok = 1;
    ERR_clear_error();
#endif
    if (!sig_ok) {
      /* bad signature */
      al = SSL_AD_DECRYPT_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_BAD_SIGNATURE);
      goto f_err;
    }
  } else {
    /* PSK ciphers are the only supported certificate-less ciphers. */
    assert(alg_a == SSL_aPSK);

    if (CBS_len(&server_key_exchange) > 0) {
      al = SSL_AD_DECODE_ERROR;
      OPENSSL_PUT_ERROR(SSL, SSL_R_EXTRA_DATA_IN_MESSAGE);
      goto f_err;
    }
  }
  EVP_PKEY_free(pkey);
  return 1;

f_err:
  ssl3_send_alert(ssl, SSL3_AL_FATAL, al);
err:
  EVP_PKEY_free(pkey);
  DH_free(dh);
  EC_POINT_free(srvr_ecpoint);
  EC_KEY_free(ecdh);
  return -1;
}

static int ca_dn_cmp(const X509_NAME **a, const X509_NAME **b) {
  return X509_NAME_cmp(*a, *b);
}

static int ssl3_get_certificate_request(SSL *ssl) {
  int ok, ret = 0;
  X509_NAME *xn = NULL;
  STACK_OF(X509_NAME) *ca_sk = NULL;

  long n = ssl->method->ssl_get_message(ssl, -1, ssl_hash_message, &ok);

  if (!ok) {
    return n;
  }

  ssl->s3->tmp.cert_request = 0;

  if (ssl->s3->tmp.message_type == SSL3_MT_SERVER_HELLO_DONE) {
    ssl->s3->tmp.reuse_message = 1;
    /* If we get here we don't need the handshake buffer as we won't be doing
     * client auth. */
    ssl3_free_handshake_buffer(ssl);
    return 1;
  }

  if (ssl->s3->tmp.message_type != SSL3_MT_CERTIFICATE_REQUEST) {
    ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_UNEXPECTED_MESSAGE);
    OPENSSL_PUT_ERROR(SSL, SSL_R_UNEXPECTED_MESSAGE);
    goto err;
  }

  CBS cbs;
  CBS_init(&cbs, ssl->init_msg, n);

  ca_sk = sk_X509_NAME_new(ca_dn_cmp);
  if (ca_sk == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
    goto err;
  }

  /* get the certificate types */
  CBS certificate_types;
  if (!CBS_get_u8_length_prefixed(&cbs, &certificate_types)) {
    ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_DECODE_ERROR);
    OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
    goto err;
  }

  if (!CBS_stow(&certificate_types, &ssl->s3->tmp.certificate_types,
                &ssl->s3->tmp.num_certificate_types)) {
    ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_INTERNAL_ERROR);
    goto err;
  }

  if (ssl3_protocol_version(ssl) >= TLS1_2_VERSION) {
    CBS supported_signature_algorithms;
    if (!CBS_get_u16_length_prefixed(&cbs, &supported_signature_algorithms) ||
        !tls1_parse_peer_sigalgs(ssl, &supported_signature_algorithms)) {
      ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_DECODE_ERROR);
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      goto err;
    }
  }

  /* get the CA RDNs */
  CBS certificate_authorities;
  if (!CBS_get_u16_length_prefixed(&cbs, &certificate_authorities)) {
    ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_DECODE_ERROR);
    OPENSSL_PUT_ERROR(SSL, SSL_R_LENGTH_MISMATCH);
    goto err;
  }

  while (CBS_len(&certificate_authorities) > 0) {
    CBS distinguished_name;
    if (!CBS_get_u16_length_prefixed(&certificate_authorities,
                                     &distinguished_name)) {
      ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_DECODE_ERROR);
      OPENSSL_PUT_ERROR(SSL, SSL_R_CA_DN_TOO_LONG);
      goto err;
    }

    const uint8_t *data = CBS_data(&distinguished_name);
    /* A u16 length cannot overflow a long. */
    xn = d2i_X509_NAME(NULL, &data, (long)CBS_len(&distinguished_name));
    if (xn == NULL ||
        data != CBS_data(&distinguished_name) + CBS_len(&distinguished_name)) {
      ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_DECODE_ERROR);
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      goto err;
    }

    if (!sk_X509_NAME_push(ca_sk, xn)) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      goto err;
    }
    xn = NULL;
  }

  /* we should setup a certificate to return.... */
  ssl->s3->tmp.cert_request = 1;
  sk_X509_NAME_pop_free(ssl->s3->tmp.ca_names, X509_NAME_free);
  ssl->s3->tmp.ca_names = ca_sk;
  ca_sk = NULL;

  ret = 1;

err:
  X509_NAME_free(xn);
  sk_X509_NAME_pop_free(ca_sk, X509_NAME_free);
  return ret;
}

static int ssl3_get_server_hello_done(SSL *ssl) {
  int ok;
  long n;

  n = ssl->method->ssl_get_message(ssl, SSL3_MT_SERVER_HELLO_DONE,
                                   ssl_hash_message, &ok);

  if (!ok) {
    return n;
  }

  if (n > 0) {
    /* should contain no data */
    ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_DECODE_ERROR);
    OPENSSL_PUT_ERROR(SSL, SSL_R_LENGTH_MISMATCH);
    return -1;
  }

  return 1;
}

/* ssl3_has_client_certificate returns true if a client certificate is
 * configured. */
static int ssl3_has_client_certificate(SSL *ssl) {
  return ssl->cert && ssl->cert->x509 && ssl_has_private_key(ssl);
}

static int ssl_do_client_cert_cb(SSL *ssl, X509 **out_x509,
                                 EVP_PKEY **out_pkey) {
  if (ssl->ctx->client_cert_cb == NULL) {
    return 0;
  }

  int ret = ssl->ctx->client_cert_cb(ssl, out_x509, out_pkey);
  if (ret <= 0) {
    return ret;
  }

  assert(*out_x509 != NULL);
  assert(*out_pkey != NULL);
  return 1;
}

static int ssl3_send_client_certificate(SSL *ssl) {
  if (ssl->state == SSL3_ST_CW_CERT_A) {
    /* Call cert_cb to update the certificate. */
    if (ssl->cert->cert_cb) {
      int ret = ssl->cert->cert_cb(ssl, ssl->cert->cert_cb_arg);
      if (ret < 0) {
        ssl->rwstate = SSL_X509_LOOKUP;
        return -1;
      }
      if (ret == 0) {
        ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_INTERNAL_ERROR);
        return -1;
      }
    }

    if (ssl3_has_client_certificate(ssl)) {
      ssl->state = SSL3_ST_CW_CERT_C;
    } else {
      ssl->state = SSL3_ST_CW_CERT_B;
    }
  }

  if (ssl->state == SSL3_ST_CW_CERT_B) {
    /* Call client_cert_cb to update the certificate. */
    X509 *x509 = NULL;
    EVP_PKEY *pkey = NULL;
    int ret = ssl_do_client_cert_cb(ssl, &x509, &pkey);
    if (ret < 0) {
      ssl->rwstate = SSL_X509_LOOKUP;
      return -1;
    }

    int setup_error = ret == 1 && (!SSL_use_certificate(ssl, x509) ||
                                   !SSL_use_PrivateKey(ssl, pkey));
    X509_free(x509);
    EVP_PKEY_free(pkey);
    if (setup_error) {
      ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_INTERNAL_ERROR);
      return -1;
    }

    ssl->state = SSL3_ST_CW_CERT_C;
  }

  if (ssl->state == SSL3_ST_CW_CERT_C) {
    if (!ssl3_has_client_certificate(ssl)) {
      ssl->s3->tmp.cert_request = 0;
      /* Without a client certificate, the handshake buffer may be released. */
      ssl3_free_handshake_buffer(ssl);

      if (ssl->version == SSL3_VERSION) {
        /* In SSL 3.0, send no certificate by skipping both messages. */
        ssl3_send_alert(ssl, SSL3_AL_WARNING, SSL_AD_NO_CERTIFICATE);
        return 1;
      }

      CBB cbb, body;
      if (!ssl->method->init_message(ssl, &cbb, &body, SSL3_MT_CERTIFICATE) ||
          !CBB_add_u24(&body, 0 /* no certificates */) ||
          !ssl->method->finish_message(ssl, &cbb)) {
        return -1;
      }
    } else if (!ssl3_output_cert_chain(ssl)) {
      return -1;
    }
    ssl->state = SSL3_ST_CW_CERT_D;
  }

  assert(ssl->state == SSL3_ST_CW_CERT_D);
  return ssl->method->write_message(ssl);
}

OPENSSL_COMPILE_ASSERT(sizeof(size_t) >= sizeof(unsigned),
                       SIZE_T_IS_SMALLER_THAN_UNSIGNED);

static int ssl3_send_client_key_exchange(SSL *ssl) {
  if (ssl->state == SSL3_ST_CW_KEY_EXCH_B) {
    return ssl->method->write_message(ssl);
  }
  assert(ssl->state == SSL3_ST_CW_KEY_EXCH_A);

  uint8_t *pms = NULL;
  size_t pms_len = 0;
  CBB cbb, body;
  if (!ssl->method->init_message(ssl, &cbb, &body,
                                 SSL3_MT_CLIENT_KEY_EXCHANGE)) {
    goto err;
  }

  uint32_t alg_k = ssl->s3->tmp.new_cipher->algorithm_mkey;
  uint32_t alg_a = ssl->s3->tmp.new_cipher->algorithm_auth;

  /* If using a PSK key exchange, prepare the pre-shared key. */
  unsigned psk_len = 0;
  uint8_t psk[PSK_MAX_PSK_LEN];
  if (alg_a & SSL_aPSK) {
    if (ssl->psk_client_callback == NULL) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_PSK_NO_CLIENT_CB);
      goto err;
    }

    char identity[PSK_MAX_IDENTITY_LEN + 1];
    memset(identity, 0, sizeof(identity));
    psk_len = ssl->psk_client_callback(
        ssl, ssl->s3->tmp.peer_psk_identity_hint, identity, sizeof(identity),
        psk, sizeof(psk));
    if (psk_len == 0) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_PSK_IDENTITY_NOT_FOUND);
      ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_HANDSHAKE_FAILURE);
      goto err;
    }
    assert(psk_len <= PSK_MAX_PSK_LEN);

    OPENSSL_free(ssl->session->psk_identity);
    ssl->session->psk_identity = BUF_strdup(identity);
    if (ssl->session->psk_identity == NULL) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      goto err;
    }

    /* Write out psk_identity. */
    CBB child;
    if (!CBB_add_u16_length_prefixed(&body, &child) ||
        !CBB_add_bytes(&child, (const uint8_t *)identity,
                       OPENSSL_strnlen(identity, sizeof(identity))) ||
        !CBB_flush(&body)) {
      goto err;
    }
  }

  /* Depending on the key exchange method, compute |pms| and |pms_len|. */
  if (alg_k & SSL_kRSA) {
    pms_len = SSL_MAX_MASTER_KEY_LENGTH;
    pms = OPENSSL_malloc(pms_len);
    if (pms == NULL) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      goto err;
    }

    EVP_PKEY *pkey = X509_get_pubkey(ssl->session->peer);
    if (pkey == NULL) {
      goto err;
    }

    RSA *rsa = EVP_PKEY_get0_RSA(pkey);
    if (rsa == NULL) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
      EVP_PKEY_free(pkey);
      goto err;
    }

    EVP_PKEY_free(pkey);

    pms[0] = ssl->client_version >> 8;
    pms[1] = ssl->client_version & 0xff;
    if (!RAND_bytes(&pms[2], SSL_MAX_MASTER_KEY_LENGTH - 2)) {
      goto err;
    }

    CBB child, *enc_pms = &body;
    size_t enc_pms_len;
    /* In TLS, there is a length prefix. */
    if (ssl->version > SSL3_VERSION) {
      if (!CBB_add_u16_length_prefixed(&body, &child)) {
        goto err;
      }
      enc_pms = &child;
    }

    uint8_t *ptr;
    if (!CBB_reserve(enc_pms, &ptr, RSA_size(rsa)) ||
        !RSA_encrypt(rsa, &enc_pms_len, ptr, RSA_size(rsa), pms, pms_len,
                     RSA_PKCS1_PADDING) ||
        /* Log the premaster secret, if logging is enabled. */
        !ssl_log_rsa_client_key_exchange(ssl, ptr, enc_pms_len, pms, pms_len) ||
        !CBB_did_write(enc_pms, enc_pms_len) ||
        !CBB_flush(&body)) {
      goto err;
    }
  } else if (alg_k & (SSL_kECDHE|SSL_kDHE|SSL_kCECPQ1)) {
    /* Generate a keypair and serialize the public half. */
    CBB child;
    if (!SSL_ECDH_CTX_add_key(&ssl->s3->tmp.ecdh_ctx, &body, &child)) {
      goto err;
    }

    /* Compute the premaster. */
    uint8_t alert;
    if (!SSL_ECDH_CTX_accept(&ssl->s3->tmp.ecdh_ctx, &child, &pms, &pms_len,
                             &alert, ssl->s3->tmp.peer_key,
                             ssl->s3->tmp.peer_key_len)) {
      ssl3_send_alert(ssl, SSL3_AL_FATAL, alert);
      goto err;
    }
    if (!CBB_flush(&body)) {
      goto err;
    }

    /* The key exchange state may now be discarded. */
    SSL_ECDH_CTX_cleanup(&ssl->s3->tmp.ecdh_ctx);
    OPENSSL_free(ssl->s3->tmp.peer_key);
    ssl->s3->tmp.peer_key = NULL;
  } else if (alg_k & SSL_kPSK) {
    /* For plain PSK, other_secret is a block of 0s with the same length as
     * the pre-shared key. */
    pms_len = psk_len;
    pms = OPENSSL_malloc(pms_len);
    if (pms == NULL) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      goto err;
    }
    memset(pms, 0, pms_len);
  } else {
    ssl3_send_alert(ssl, SSL3_AL_FATAL, SSL_AD_HANDSHAKE_FAILURE);
    OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
    goto err;
  }

  /* For a PSK cipher suite, other_secret is combined with the pre-shared
   * key. */
  if (alg_a & SSL_aPSK) {
    CBB pms_cbb, child;
    uint8_t *new_pms;
    size_t new_pms_len;

    CBB_zero(&pms_cbb);
    if (!CBB_init(&pms_cbb, 2 + psk_len + 2 + pms_len) ||
        !CBB_add_u16_length_prefixed(&pms_cbb, &child) ||
        !CBB_add_bytes(&child, pms, pms_len) ||
        !CBB_add_u16_length_prefixed(&pms_cbb, &child) ||
        !CBB_add_bytes(&child, psk, psk_len) ||
        !CBB_finish(&pms_cbb, &new_pms, &new_pms_len)) {
      CBB_cleanup(&pms_cbb);
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      goto err;
    }
    OPENSSL_cleanse(pms, pms_len);
    OPENSSL_free(pms);
    pms = new_pms;
    pms_len = new_pms_len;
  }

  /* The message must be added to the finished hash before calculating the
   * master secret. */
  if (!ssl->method->finish_message(ssl, &cbb)) {
    goto err;
  }
  ssl->state = SSL3_ST_CW_KEY_EXCH_B;

  ssl->session->master_key_length =
      tls1_generate_master_secret(ssl, ssl->session->master_key, pms, pms_len);
  if (ssl->session->master_key_length == 0) {
    goto err;
  }
  ssl->session->extended_master_secret = ssl->s3->tmp.extended_master_secret;
  OPENSSL_cleanse(pms, pms_len);
  OPENSSL_free(pms);

  return ssl->method->write_message(ssl);

err:
  CBB_cleanup(&cbb);
  if (pms != NULL) {
    OPENSSL_cleanse(pms, pms_len);
    OPENSSL_free(pms);
  }
  return -1;
}

static int ssl3_send_cert_verify(SSL *ssl) {
  if (ssl->state == SSL3_ST_CW_CERT_VRFY_C) {
    return ssl->method->write_message(ssl);
  }

  assert(ssl_has_private_key(ssl));

  CBB cbb, body, child;
  if (!ssl->method->init_message(ssl, &cbb, &body,
                                 SSL3_MT_CERTIFICATE_VERIFY)) {
    goto err;
  }

  uint16_t signature_algorithm = tls1_choose_signature_algorithm(ssl);
  if (ssl3_protocol_version(ssl) >= TLS1_2_VERSION) {
    /* Write out the digest type in TLS 1.2. */
    if (!CBB_add_u16(&body, signature_algorithm)) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
      goto err;
    }
  }

  /* Set aside space for the signature. */
  const size_t max_sig_len = ssl_private_key_max_signature_len(ssl);
  uint8_t *ptr;
  if (!CBB_add_u16_length_prefixed(&body, &child) ||
      !CBB_reserve(&child, &ptr, max_sig_len)) {
    goto err;
  }

  size_t sig_len = max_sig_len;
  enum ssl_private_key_result_t sign_result;
  if (ssl->state == SSL3_ST_CW_CERT_VRFY_A) {
    /* The SSL3 construction for CertificateVerify does not decompose into a
     * single final digest and signature, and must be special-cased. */
    if (ssl3_protocol_version(ssl) == SSL3_VERSION) {
      if (ssl->cert->key_method != NULL) {
        OPENSSL_PUT_ERROR(SSL, SSL_R_UNSUPPORTED_PROTOCOL_FOR_CUSTOM_KEY);
        goto err;
      }

      uint8_t digest[EVP_MAX_MD_SIZE];
      size_t digest_len;
      if (!ssl3_cert_verify_hash(ssl, digest, &digest_len,
                                 signature_algorithm)) {
        goto err;
      }

      sign_result = ssl_private_key_success;

      EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new(ssl->cert->privatekey, NULL);
      if (pctx == NULL ||
          !EVP_PKEY_sign_init(pctx) ||
          !EVP_PKEY_sign(pctx, ptr, &sig_len, digest, digest_len)) {
        EVP_PKEY_CTX_free(pctx);
        sign_result = ssl_private_key_failure;
        goto err;
      }
      EVP_PKEY_CTX_free(pctx);
    } else {
      sign_result = ssl_private_key_sign(
          ssl, ptr, &sig_len, max_sig_len, signature_algorithm,
          (const uint8_t *)ssl->s3->handshake_buffer->data,
          ssl->s3->handshake_buffer->length);
    }

    /* The handshake buffer is no longer necessary. */
    ssl3_free_handshake_buffer(ssl);
  } else {
    assert(ssl->state == SSL3_ST_CW_CERT_VRFY_B);
    sign_result =
        ssl_private_key_sign_complete(ssl, ptr, &sig_len, max_sig_len);
  }

  switch (sign_result) {
    case ssl_private_key_success:
      break;
    case ssl_private_key_failure:
      goto err;
    case ssl_private_key_retry:
      ssl->rwstate = SSL_PRIVATE_KEY_OPERATION;
      ssl->state = SSL3_ST_CW_CERT_VRFY_B;
      goto err;
  }

  if (!CBB_did_write(&child, sig_len) ||
      !ssl->method->finish_message(ssl, &cbb)) {
    goto err;
  }

  ssl->state = SSL3_ST_CW_CERT_VRFY_C;
  return ssl->method->write_message(ssl);

err:
  CBB_cleanup(&cbb);
  return -1;
}

static int ssl3_send_next_proto(SSL *ssl) {
  if (ssl->state == SSL3_ST_CW_NEXT_PROTO_B) {
    return ssl->method->write_message(ssl);
  }

  assert(ssl->state == SSL3_ST_CW_NEXT_PROTO_A);

  static const uint8_t kZero[32] = {0};
  size_t padding_len = 32 - ((ssl->s3->next_proto_negotiated_len + 2) % 32);

  CBB cbb, body, child;
  if (!ssl->method->init_message(ssl, &cbb, &body, SSL3_MT_NEXT_PROTO) ||
      !CBB_add_u8_length_prefixed(&body, &child) ||
      !CBB_add_bytes(&child, ssl->s3->next_proto_negotiated,
                     ssl->s3->next_proto_negotiated_len) ||
      !CBB_add_u8_length_prefixed(&body, &child) ||
      !CBB_add_bytes(&child, kZero, padding_len) ||
      !ssl->method->finish_message(ssl, &cbb)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
    CBB_cleanup(&cbb);
    return -1;
  }

  ssl->state = SSL3_ST_CW_NEXT_PROTO_B;
  return ssl->method->write_message(ssl);
}

static int ssl3_send_channel_id(SSL *ssl) {
  if (ssl->state == SSL3_ST_CW_CHANNEL_ID_B) {
    return ssl->method->write_message(ssl);
  }

  assert(ssl->state == SSL3_ST_CW_CHANNEL_ID_A);

  if (ssl->tlsext_channel_id_private == NULL &&
      ssl->ctx->channel_id_cb != NULL) {
    EVP_PKEY *key = NULL;
    ssl->ctx->channel_id_cb(ssl, &key);
    if (key != NULL &&
        !SSL_set1_tls_channel_id(ssl, key)) {
      EVP_PKEY_free(key);
      return -1;
    }
    EVP_PKEY_free(key);
  }

  if (ssl->tlsext_channel_id_private == NULL) {
    ssl->rwstate = SSL_CHANNEL_ID_LOOKUP;
    return -1;
  }

  EC_KEY *ec_key = EVP_PKEY_get0_EC_KEY(ssl->tlsext_channel_id_private);
  if (ec_key == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
    return -1;
  }

  int ret = -1;
  BIGNUM *x = BN_new();
  BIGNUM *y = BN_new();
  ECDSA_SIG *sig = NULL;
  if (x == NULL || y == NULL ||
      !EC_POINT_get_affine_coordinates_GFp(EC_KEY_get0_group(ec_key),
                                           EC_KEY_get0_public_key(ec_key),
                                           x, y, NULL)) {
    goto err;
  }

  uint8_t digest[EVP_MAX_MD_SIZE];
  size_t digest_len;
  if (!tls1_channel_id_hash(ssl, digest, &digest_len)) {
    goto err;
  }

  sig = ECDSA_do_sign(digest, digest_len, ec_key);
  if (sig == NULL) {
    goto err;
  }

  CBB cbb, body, child;
  if (!ssl->method->init_message(ssl, &cbb, &body, SSL3_MT_CHANNEL_ID) ||
      !CBB_add_u16(&body, TLSEXT_TYPE_channel_id) ||
      !CBB_add_u16_length_prefixed(&body, &child) ||
      !BN_bn2cbb_padded(&child, 32, x) || !BN_bn2cbb_padded(&child, 32, y) ||
      !BN_bn2cbb_padded(&child, 32, sig->r) ||
      !BN_bn2cbb_padded(&child, 32, sig->s) ||
      !ssl->method->finish_message(ssl, &cbb)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
    CBB_cleanup(&cbb);
    goto err;
  }

  ssl->state = SSL3_ST_CW_CHANNEL_ID_B;
  ret = ssl->method->write_message(ssl);

err:
  BN_free(x);
  BN_free(y);
  ECDSA_SIG_free(sig);
  return ret;
}

static int ssl3_get_new_session_ticket(SSL *ssl) {
  int ok, al;
  long n = ssl->method->ssl_get_message(ssl, SSL3_MT_NEW_SESSION_TICKET,
                                        ssl_hash_message, &ok);

  if (!ok) {
    return n;
  }

  CBS new_session_ticket, ticket;
  uint32_t ticket_lifetime_hint;
  CBS_init(&new_session_ticket, ssl->init_msg, n);
  if (!CBS_get_u32(&new_session_ticket, &ticket_lifetime_hint) ||
      !CBS_get_u16_length_prefixed(&new_session_ticket, &ticket) ||
      CBS_len(&new_session_ticket) != 0) {
    al = SSL_AD_DECODE_ERROR;
    OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
    goto f_err;
  }

  if (CBS_len(&ticket) == 0) {
    /* RFC 5077 allows a server to change its mind and send no ticket after
     * negotiating the extension. The value of |tlsext_ticket_expected| is
     * checked in |ssl_update_cache| so is cleared here to avoid an unnecessary
     * update. */
    ssl->tlsext_ticket_expected = 0;
    return 1;
  }

  if (ssl->hit) {
    /* The server is sending a new ticket for an existing session. Sessions are
     * immutable once established, so duplicate all but the ticket of the
     * existing session. */
    uint8_t *bytes;
    size_t bytes_len;
    if (!SSL_SESSION_to_bytes_for_ticket(ssl->session, &bytes, &bytes_len)) {
      goto err;
    }
    SSL_SESSION *new_session = SSL_SESSION_from_bytes(bytes, bytes_len);
    OPENSSL_free(bytes);
    if (new_session == NULL) {
      /* This should never happen. */
      OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
      goto err;
    }

    SSL_SESSION_free(ssl->session);
    ssl->session = new_session;
  }

  if (!CBS_stow(&ticket, &ssl->session->tlsext_tick,
                &ssl->session->tlsext_ticklen)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
    goto err;
  }
  ssl->session->tlsext_tick_lifetime_hint = ticket_lifetime_hint;

  /* Generate a session ID for this session based on the session ticket. We use
   * the session ID mechanism for detecting ticket resumption. This also fits in
   * with assumptions elsewhere in OpenSSL.*/
  if (!EVP_Digest(CBS_data(&ticket), CBS_len(&ticket), ssl->session->session_id,
                  &ssl->session->session_id_length, EVP_sha256(), NULL)) {
    goto err;
  }

  return 1;

f_err:
  ssl3_send_alert(ssl, SSL3_AL_FATAL, al);
err:
  return -1;
}

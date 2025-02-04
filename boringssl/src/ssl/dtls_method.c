/*
 * DTLS implementation written by Nagendra Modadugu
 * (nagendra@cs.stanford.edu) for the OpenSSL project 2005. 
 */
/* ====================================================================
 * Copyright (c) 1999-2005 The OpenSSL Project.  All rights reserved.
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
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
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
 * Hudson (tjh@cryptsoft.com). */

#include <openssl/ssl.h>

#include <assert.h>

#include <openssl/buf.h>

#include "internal.h"


static uint16_t dtls1_version_from_wire(uint16_t wire_version) {
  uint16_t tls_version = ~wire_version;
  uint16_t version = tls_version + 0x0201;
  /* If either component overflowed, clamp it so comparisons still work. */
  if ((version >> 8) < (tls_version >> 8)) {
    version = 0xff00 | (version & 0xff);
  }
  if ((version & 0xff) < (tls_version & 0xff)) {
    version = (version & 0xff00) | 0xff;
  }
  /* DTLS 1.0 maps to TLS 1.1, not TLS 1.0. */
  if (version == TLS1_VERSION) {
    version = TLS1_1_VERSION;
  }
  return version;
}

static uint16_t dtls1_version_to_wire(uint16_t version) {
  assert(version >= TLS1_1_VERSION);

  /* DTLS 1.0 maps to TLS 1.1, not TLS 1.0. */
  if (version == TLS1_1_VERSION) {
    return DTLS1_VERSION;
  }
  return ~(version - 0x0201);
}

static int dtls1_begin_handshake(SSL *ssl) {
  if (ssl->init_buf != NULL) {
    return 1;
  }

  BUF_MEM *buf = BUF_MEM_new();
  if (buf == NULL || !BUF_MEM_reserve(buf, SSL3_RT_MAX_PLAIN_LENGTH)) {
    BUF_MEM_free(buf);
    return 0;
  }

  ssl->init_buf = buf;
  ssl->init_num = 0;
  return 1;
}

static void dtls1_finish_handshake(SSL *ssl) {
  BUF_MEM_free(ssl->init_buf);
  ssl->init_buf = NULL;
  ssl->init_num = 0;

  ssl->d1->handshake_read_seq = 0;
  ssl->d1->handshake_write_seq = 0;
  dtls_clear_incoming_messages(ssl);
}

static const SSL_PROTOCOL_METHOD kDTLSProtocolMethod = {
    1 /* is_dtls */,
    TLS1_1_VERSION,
    TLS1_2_VERSION,
    dtls1_version_from_wire,
    dtls1_version_to_wire,
    dtls1_new,
    dtls1_free,
    dtls1_begin_handshake,
    dtls1_finish_handshake,
    dtls1_get_message,
    dtls1_read_app_data,
    dtls1_read_change_cipher_spec,
    dtls1_read_close_notify,
    dtls1_write_app_data,
    dtls1_dispatch_alert,
    dtls1_supports_cipher,
    dtls1_init_message,
    dtls1_finish_message,
    dtls1_write_message,
    dtls1_send_change_cipher_spec,
    dtls1_expect_flight,
    dtls1_received_flight,
};

const SSL_METHOD *DTLS_method(void) {
  static const SSL_METHOD kMethod = {
      0,
      &kDTLSProtocolMethod,
  };
  return &kMethod;
}

/* Legacy version-locked methods. */

const SSL_METHOD *DTLSv1_2_method(void) {
  static const SSL_METHOD kMethod = {
      DTLS1_2_VERSION,
      &kDTLSProtocolMethod,
  };
  return &kMethod;
}

const SSL_METHOD *DTLSv1_method(void) {
  static const SSL_METHOD kMethod = {
      DTLS1_VERSION,
      &kDTLSProtocolMethod,
  };
  return &kMethod;
}

/* Legacy side-specific methods. */

const SSL_METHOD *DTLSv1_2_server_method(void) {
  return DTLSv1_2_method();
}

const SSL_METHOD *DTLSv1_server_method(void) {
  return DTLSv1_method();
}

const SSL_METHOD *DTLSv1_2_client_method(void) {
  return DTLSv1_2_method();
}

const SSL_METHOD *DTLSv1_client_method(void) {
  return DTLSv1_method();
}

const SSL_METHOD *DTLS_server_method(void) {
  return DTLS_method();
}

const SSL_METHOD *DTLS_client_method(void) {
  return DTLS_method();
}

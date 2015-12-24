/********************************************************************************
 *                               Dionaea
 *                           - catches bugs -
 *
 *
 *
 * Copyright (C) 2009  Paul Baecher & Markus Koetter
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
 * 
 *             contact nepenthesdev@gmail.com  
 *
 *******************************************************************************/

#ifndef HAVE_PROTOCOL_H
#define HAVE_PROTOCOL_H

#include <stdbool.h>

struct connection;


/* protocol error codes */

enum connection_error
{
	ECONDNSTIMEOUT     = 0,
	ECONUNREACH        = 1,
	ECONNOSUCHDOMAIN   = 2,
	ECONMANY		   = 4,
	ECONMAX            = 5
};

typedef void (*protocol_handler_established)(struct connection *con);
typedef bool (*protocol_handler_error)(struct connection *con, enum connection_error error);
typedef void (*protocol_handler_origin)(struct connection *con, struct connection *origin);
typedef unsigned int (*protocol_handler_io_in)(struct connection *con, void *context, unsigned char *data, uint32_t size);
typedef void (*protocol_handler_io_out)(struct connection *con, void *context);

typedef bool (*protocol_handler_disconnect)(struct connection *con, void *context);
typedef bool (*protocol_handler_timeout)(struct connection *con, void *context);
typedef void *(*protocol_handler_ctx_new)(struct connection *con);
typedef void (*protocol_handler_ctx_free)(void *data);
typedef void (*protocol_handler_name)(void *ctx);

struct protocol
{
	char *name;
	protocol_handler_ctx_new  ctx_new;
	protocol_handler_ctx_free ctx_free;
	protocol_handler_origin origin;
	protocol_handler_established established;
	protocol_handler_error error;
	protocol_handler_timeout sustain_timeout;
	protocol_handler_timeout idle_timeout;
	/**
	 * Callback for timeouts when waiting to accept a connection
	 */
	protocol_handler_timeout listen_timeout;
	protocol_handler_disconnect disconnect;
	protocol_handler_io_in io_in;
	protocol_handler_io_out io_out;
	void *ctx;
};

#endif

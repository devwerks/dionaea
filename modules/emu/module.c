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


#include <glib.h>
#include <stdio.h>

#include <lcfg/lcfg.h>
#include <lcfgx/lcfgx_tree.h>


#include "modules.h"
#include "connection.h"
#include "dionaea.h"

#include "module.h"
#include "log.h"
#include "processor.h"

#define D_LOG_DOMAIN "emu"


static struct 
{
	struct lcfgx_tree_node *config;
} emu_runtime;

static bool emu_config(struct lcfgx_tree_node *node)
{
	g_debug("%s", __PRETTY_FUNCTION__);
	emu_runtime.config = node;
	return true;
}

static bool emu_new(struct dionaea *d)
{
	g_debug("%s", __PRETTY_FUNCTION__);
	g_hash_table_insert(g_dionaea->processors->names, (void *)proc_emu.name, &proc_emu);
	return true;
}

static bool emu_free(void)
{
	g_debug("%s", __PRETTY_FUNCTION__);
	return true;
}

static bool emu_hup(struct lcfgx_tree_node *node)
{
	g_debug("%s", __PRETTY_FUNCTION__);
	return true;
}



struct module_api *module_init(struct dionaea *d)
{
    g_debug("%s:%i %s dionaea %p",__FILE__, __LINE__, __PRETTY_FUNCTION__, d);
	static struct module_api emu_api =
	{
		.config = &emu_config,
		.start = NULL,
		.new = &emu_new,
		.free = &emu_free,
		.hup = &emu_hup
	};

    return &emu_api;
}


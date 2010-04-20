/*
 * Copyright (C) 2010, Intel Corporation.
 *
 * Author: Raymond Liu <raymond.liu@intel.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef _DUI_IM_PROXY_H
#define _DUI_IM_PROXY_H

#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib.h>

G_BEGIN_DECLS

typedef struct _DuiIMProxy DuiIMProxy;
typedef struct _DuiIMProxyClass DuiIMProxyClass;

#define DUI_TYPE_IM_PROXY		(dui_im_proxy_get_type())
#define DUI_IM_PROXY(obj)		(G_TYPE_CHECK_INSTANCE_CAST((obj), DUI_TYPE_IM_PROXY, DuiIMProxy))
#define DUI_IM_PROXY_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST((klass), DUI_TYPE_IM_PROXY, DuiIMProxyClass))
#define DUI_IS_IM_PROXY(obj)		(G_TYPE_CHECK_INSTANCE_TYPE((obj), DUI_TYPE_IM_PROXY))
#define DUI_IS_IM_PROXY_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), DUI_TYPE_IM_PROXY))
#define DUI_IM_PROXY_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), DUI_TYPE_IM_PROXY, DuiIMProxyClass))


struct _DuiIMProxy {
	GObject parent;

	DBusGProxy *dbusproxy;
};

struct _DuiIMProxyClass {
	GObjectClass parent;
};

GType dui_im_proxy_get_type (void);

DuiIMProxy *dui_im_proxy_get_singleton (void);

gboolean dui_im_proxy_activate_context (DuiIMProxy *proxy);
gboolean dui_im_proxy_app_orientation_changed (DuiIMProxy *proxy, const gint angle);
gboolean dui_im_proxy_hide_input_method (DuiIMProxy *proxy);
#if 0
// Not yet really implemented
gboolean dui_im_proxy_mouse_clicked_on_preedit (DuiIMProxy *proxy, const GValueArray* pos,
					const GValueArray* preedit_rect);
gboolean dui_im_proxy_update_widget_info (DuiIMProxy *proxy, const GHashTable *state_information);
#endif

gboolean dui_im_proxy_process_key_event (DuiIMProxy *proxy, const gint type, const gint code,
					const gint modifiers, const char * text,
					const gboolean auto_repeat, const gint count,
					const gint native_scan_code);

gboolean dui_im_proxy_reset (DuiIMProxy *proxy);
gboolean dui_im_proxy_set_context_object (DuiIMProxy *proxy, const char *object_name);
gboolean dui_im_proxy_set_copy_paste_state (DuiIMProxy *proxy, const gboolean copy_available,
					const gboolean paste_available);
gboolean dui_im_proxy_set_preedit (DuiIMProxy *proxy, const char *text);
gboolean dui_im_proxy_show_input_method (DuiIMProxy *proxy);

G_END_DECLS

#endif //_DUI_IM_PROXY_H
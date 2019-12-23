/*
 * Copyright (C) 2008-2010 Ole André Vadla Ravnås <ole.andre.ravnas@tillitech.com>
 *
 * Licence: wxWindows Library Licence, Version 3.1
 */

#ifndef __GUM_INVOCATION_CONTEXT_H__
#define __GUM_INVOCATION_CONTEXT_H__

#include "gumprocess.h"

#include <glib-object.h>
#include <gum/gumdefs.h>

#define GUM_LINCTX_GET_THREAD_DATA(context, data_type) \
    ((data_type *) gum_invocation_context_get_listener_thread_data (context, \
        sizeof (data_type)))
#define GUM_LINCTX_GET_FUNC_DATA(context, data_type) \
    ((data_type) gum_invocation_context_get_listener_function_data (context))
#define GUM_LINCTX_GET_FUNC_INVDATA(context, data_type) \
    ((data_type *) \
        gum_invocation_context_get_listener_function_invocation_data (context,\
            sizeof (data_type)))

#define GUM_RINCTX_GET_FUNC_DATA(ctx, data_type) \
    ((data_type) gum_invocation_context_get_replacement_function_data (ctx))

typedef struct _GumInvocationBackend GumInvocationBackend;
typedef struct _GumInvocationContext GumInvocationContext;
typedef guint GumPointCut;

struct _GumInvocationBackend
{
  GumPointCut (* get_point_cut) (GumInvocationContext * context);

  GumThreadId (* get_thread_id) (GumInvocationContext * context);
  guint (* get_depth) (GumInvocationContext * context);

  gpointer (* get_listener_thread_data) (GumInvocationContext * context,
      gsize required_size);
  gpointer (* get_listener_function_data) (GumInvocationContext * context);
  gpointer (* get_listener_function_invocation_data) (
      GumInvocationContext * context, gsize required_size);

  gpointer (* get_replacement_function_data) (GumInvocationContext * context);

  gpointer state;
  gpointer data;
};

struct _GumInvocationContext
{
  GCallback function;
  GumCpuContext * cpu_context;
  gint system_error;

  /*< private */
  GumInvocationBackend * backend;
};

enum _GumPointCut
{
  GUM_POINT_ENTER,
  GUM_POINT_LEAVE
};

G_BEGIN_DECLS

GUM_API GumPointCut gum_invocation_context_get_point_cut (
    GumInvocationContext * context);

GUM_API gpointer gum_invocation_context_get_nth_argument (
    GumInvocationContext * context, guint n);
GUM_API void gum_invocation_context_replace_nth_argument (
    GumInvocationContext * context, guint n, gpointer value);
GUM_API gpointer gum_invocation_context_get_return_value (
    GumInvocationContext * context);
GUM_API void gum_invocation_context_replace_return_value (
    GumInvocationContext * context, gpointer value);

GUM_API gpointer gum_invocation_context_get_return_address (
    GumInvocationContext * context);

GUM_API guint gum_invocation_context_get_thread_id (
    GumInvocationContext * context);
GUM_API guint gum_invocation_context_get_depth (
    GumInvocationContext * context);

GUM_API gpointer gum_invocation_context_get_listener_thread_data (
    GumInvocationContext * context, gsize required_size);
GUM_API gpointer gum_invocation_context_get_listener_function_data (
    GumInvocationContext * context);
GUM_API gpointer gum_invocation_context_get_listener_function_invocation_data (
    GumInvocationContext * context, gsize required_size);

GUM_API gpointer gum_invocation_context_get_replacement_function_data (
    GumInvocationContext * context);

G_END_DECLS

#endif

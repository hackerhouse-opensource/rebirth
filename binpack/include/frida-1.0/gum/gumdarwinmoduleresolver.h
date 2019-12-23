/*
 * Copyright (C) 2015-2016 Ole André Vadla Ravnås <oleavr@nowsecure.com>
 *
 * Licence: wxWindows Library Licence, Version 3.1
 */

#ifndef __GUM_DARWIN_MODULE_RESOLVER_H__
#define __GUM_DARWIN_MODULE_RESOLVER_H__

#include "gumdarwinmodule.h"
#include "gumdefs.h"

G_BEGIN_DECLS

#define GUM_DARWIN_TYPE_MODULE_RESOLVER (gum_darwin_module_resolver_get_type ())
G_DECLARE_FINAL_TYPE (GumDarwinModuleResolver, gum_darwin_module_resolver,
    GUM_DARWIN, MODULE_RESOLVER, GObject)

struct _GumDarwinModuleResolver
{
  GObject parent;

  mach_port_t task;
  GumCpuType cpu_type;
  guint page_size;
  GHashTable * modules;
  gchar * sysroot;
};

GUM_API GumDarwinModuleResolver * gum_darwin_module_resolver_new (
    mach_port_t task);
GUM_API GumDarwinModule * gum_darwin_module_resolver_find_module (
    GumDarwinModuleResolver * self, const gchar * module_name);
GUM_API gboolean gum_darwin_module_resolver_find_export (
    GumDarwinModuleResolver * self, GumDarwinModule * module,
    const gchar * symbol, GumExportDetails * details);
GUM_API GumAddress gum_darwin_module_resolver_find_export_address (
    GumDarwinModuleResolver * self, GumDarwinModule * module,
    const gchar * symbol);
GUM_API gboolean gum_darwin_module_resolver_find_export_by_mangled_name (
    GumDarwinModuleResolver * self, GumDarwinModule * module,
    const gchar * symbol, GumExportDetails * details);
GUM_API gboolean gum_darwin_module_resolver_resolve_export (
    GumDarwinModuleResolver * self, GumDarwinModule * module,
    const GumDarwinExportDetails * export, GumExportDetails * result);

G_END_DECLS

#endif

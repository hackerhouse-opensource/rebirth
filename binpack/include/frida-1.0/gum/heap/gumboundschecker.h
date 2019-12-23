/*
 * Copyright (C) 2008-2010 Ole André Vadla Ravnås <ole.andre.ravnas@tillitech.com>
 *
 * Licence: wxWindows Library Licence, Version 3.1
 */

#ifndef __GUM_BOUNDS_CHECKER_H__
#define __GUM_BOUNDS_CHECKER_H__

#include "gumheapapi.h"

#include <glib-object.h>
#include <gum/gumbacktracer.h>

#define GUM_TYPE_BOUNDS_CHECKER (gum_bounds_checker_get_type ())
#define GUM_BOUNDS_CHECKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj),\
    GUM_TYPE_BOUNDS_CHECKER, GumBoundsChecker))
#define GUM_BOUNDS_CHECKER_CAST(obj) ((GumBoundsChecker *) (obj))
#define GUM_BOUNDS_CHECKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass),\
    GUM_TYPE_BOUNDS_CHECKER, GumBoundsCheckerClass))
#define GUM_IS_BOUNDS_CHECKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj),\
    GUM_TYPE_BOUNDS_CHECKER))
#define GUM_IS_BOUNDS_CHECKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE (\
    (klass), GUM_TYPE_BOUNDS_CHECKER))
#define GUM_BOUNDS_CHECKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS (\
    (obj), GUM_TYPE_BOUNDS_CHECKER, GumBoundsCheckerClass))

typedef struct _GumBoundsChecker GumBoundsChecker;
typedef struct _GumBoundsCheckerClass GumBoundsCheckerClass;

typedef struct _GumBoundsCheckerPrivate GumBoundsCheckerPrivate;

typedef void (* GumBoundsOutputFunc) (const gchar * text, gpointer user_data);

struct _GumBoundsChecker
{
  GObject parent;

  GumBoundsCheckerPrivate * priv;
};

struct _GumBoundsCheckerClass
{
  GObjectClass parent_class;
};

G_BEGIN_DECLS

GUM_API GType gum_bounds_checker_get_type (void) G_GNUC_CONST;

GUM_API GumBoundsChecker * gum_bounds_checker_new (GumBacktracer * backtracer,
    GumBoundsOutputFunc func, gpointer user_data);

GUM_API guint gum_bounds_checker_get_pool_size (GumBoundsChecker * self);
GUM_API void gum_bounds_checker_set_pool_size (GumBoundsChecker * self,
  guint pool_size);
GUM_API guint gum_bounds_checker_get_front_alignment (GumBoundsChecker * self);
GUM_API void gum_bounds_checker_set_front_alignment (GumBoundsChecker * self,
  guint pool_size);

GUM_API void gum_bounds_checker_attach (GumBoundsChecker * self);
GUM_API void gum_bounds_checker_attach_to_apis (GumBoundsChecker * self,
    const GumHeapApiList * apis);
GUM_API void gum_bounds_checker_detach (GumBoundsChecker * self);

G_END_DECLS

#endif

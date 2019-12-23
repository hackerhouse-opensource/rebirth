#ifndef __FRIDA_CORE_H__
#define __FRIDA_CORE_H__

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <json-glib/json-glib.h>

G_BEGIN_DECLS

typedef struct _FridaDeviceManager FridaDeviceManager;
typedef struct _FridaDeviceList FridaDeviceList;
typedef struct _FridaDevice FridaDevice;
typedef struct _FridaApplicationList FridaApplicationList;
typedef struct _FridaApplication FridaApplication;
typedef struct _FridaProcessList FridaProcessList;
typedef struct _FridaProcess FridaProcess;
typedef struct _FridaSpawnOptions FridaSpawnOptions;
typedef struct _FridaSpawnList FridaSpawnList;
typedef struct _FridaSpawn FridaSpawn;
typedef struct _FridaChildList FridaChildList;
typedef struct _FridaChild FridaChild;
typedef struct _FridaIcon FridaIcon;
typedef struct _FridaSession FridaSession;
typedef struct _FridaScript FridaScript;
typedef struct _FridaInjector FridaInjector;
typedef struct _FridaFileMonitor FridaFileMonitor;

typedef enum {
  FRIDA_DEVICE_TYPE_LOCAL,
  FRIDA_DEVICE_TYPE_REMOTE,
  FRIDA_DEVICE_TYPE_USB
} FridaDeviceType;

typedef enum {
  FRIDA_CHILD_ORIGIN_FORK,
  FRIDA_CHILD_ORIGIN_EXEC,
  FRIDA_CHILD_ORIGIN_SPAWN
} FridaChildOrigin;

typedef enum {
  FRIDA_SESSION_DETACH_REASON_APPLICATION_REQUESTED = 1,
  FRIDA_SESSION_DETACH_REASON_PROCESS_REPLACED,
  FRIDA_SESSION_DETACH_REASON_PROCESS_TERMINATED,
  FRIDA_SESSION_DETACH_REASON_SERVER_TERMINATED,
  FRIDA_SESSION_DETACH_REASON_DEVICE_LOST
} FridaSessionDetachReason;

typedef enum {
  FRIDA_STDIO_INHERIT,
  FRIDA_STDIO_PIPE
} FridaStdio;

typedef enum {
  FRIDA_UNLOAD_POLICY_IMMEDIATE,
  FRIDA_UNLOAD_POLICY_RESIDENT,
  FRIDA_UNLOAD_POLICY_DEFERRED
} FridaUnloadPolicy;

/* Library lifetime */
void frida_init (void);
void frida_shutdown (void);
void frida_deinit (void);
GMainContext * frida_get_main_context (void);

/* Object lifetime */
void frida_unref (gpointer obj);

/* Library versioning */
void frida_version (guint * major, guint * minor, guint * micro, guint * nano);
const gchar * frida_version_string (void);

/* DeviceManager */
typedef gboolean (* FridaDeviceManagerPredicate) (FridaDevice * device, gpointer user_data);

FridaDeviceManager * frida_device_manager_new (void);

void frida_device_manager_close (FridaDeviceManager * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_device_manager_close_finish (FridaDeviceManager * self, GAsyncResult * result);
void frida_device_manager_close_sync (FridaDeviceManager * self);
void frida_device_manager_get_device_by_id (FridaDeviceManager * self, const gchar * id, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaDevice * frida_device_manager_get_device_by_id_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDevice * frida_device_manager_get_device_by_id_sync (FridaDeviceManager * self, const gchar * id, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_manager_get_device_by_type (FridaDeviceManager * self, FridaDeviceType type, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaDevice * frida_device_manager_get_device_by_type_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDevice * frida_device_manager_get_device_by_type_sync (FridaDeviceManager * self, FridaDeviceType type, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_manager_get_device (FridaDeviceManager * self, FridaDeviceManagerPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaDevice * frida_device_manager_get_device_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDevice * frida_device_manager_get_device_sync (FridaDeviceManager * self, FridaDeviceManagerPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_manager_find_device_by_id (FridaDeviceManager * self, const gchar * id, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaDevice * frida_device_manager_find_device_by_id_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDevice * frida_device_manager_find_device_by_id_sync (FridaDeviceManager * self, const gchar * id, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_manager_find_device_by_type (FridaDeviceManager * self, FridaDeviceType type, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaDevice * frida_device_manager_find_device_by_type_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDevice * frida_device_manager_find_device_by_type_sync (FridaDeviceManager * self, FridaDeviceType type, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_manager_find_device (FridaDeviceManager * self, FridaDeviceManagerPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaDevice * frida_device_manager_find_device_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDevice * frida_device_manager_find_device_sync (FridaDeviceManager * self, FridaDeviceManagerPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_manager_enumerate_devices (FridaDeviceManager * self, GAsyncReadyCallback callback, gpointer user_data);
FridaDeviceList * frida_device_manager_enumerate_devices_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDeviceList * frida_device_manager_enumerate_devices_sync (FridaDeviceManager * self, GError ** error);
void frida_device_manager_add_remote_device (FridaDeviceManager * self, const gchar * host, GAsyncReadyCallback callback, gpointer user_data);
FridaDevice * frida_device_manager_add_remote_device_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
FridaDevice * frida_device_manager_add_remote_device_sync (FridaDeviceManager * self, const gchar * host, GError ** error);
void frida_device_manager_remove_remote_device (FridaDeviceManager * self, const gchar * host, GAsyncReadyCallback callback, gpointer user_data);
void frida_device_manager_remove_remote_device_finish (FridaDeviceManager * self, GAsyncResult * result, GError ** error);
void frida_device_manager_remove_remote_device_sync (FridaDeviceManager * self, const gchar * host, GError ** error);

/* DeviceList */
gint frida_device_list_size (FridaDeviceList * self);
FridaDevice * frida_device_list_get (FridaDeviceList * self, gint index);

/* Device */
typedef gboolean (* FridaDeviceProcessPredicate) (FridaProcess * process, gpointer user_data);

const gchar * frida_device_get_id (FridaDevice * self);
const gchar * frida_device_get_name (FridaDevice * self);
FridaIcon * frida_device_get_icon (FridaDevice * self);
FridaDeviceType frida_device_get_dtype (FridaDevice * self);
FridaDeviceManager * frida_device_get_manager (FridaDevice * self);

gboolean frida_device_is_lost (FridaDevice * self);
void frida_device_get_frontmost_application (FridaDevice * self, GAsyncReadyCallback callback, gpointer user_data);
FridaApplication * frida_device_get_frontmost_application_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaApplication * frida_device_get_frontmost_application_sync (FridaDevice * self, GError ** error);
void frida_device_enumerate_applications (FridaDevice * self, GAsyncReadyCallback callback, gpointer user_data);
FridaApplicationList * frida_device_enumerate_applications_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaApplicationList * frida_device_enumerate_applications_sync (FridaDevice * self, GError ** error);
void frida_device_get_process_by_pid (FridaDevice * self, guint pid, GAsyncReadyCallback callback, gpointer user_data);
FridaProcess * frida_device_get_process_by_pid_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaProcess * frida_device_get_process_by_pid_sync (FridaDevice * self, guint pid, GError ** error);
void frida_device_get_process_by_name (FridaDevice * self, const gchar * name, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaProcess * frida_device_get_process_by_name_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaProcess * frida_device_get_process_by_name_sync (FridaDevice * self, const gchar * name, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_get_process (FridaDevice * self, FridaDeviceProcessPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaProcess * frida_device_get_process_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaProcess * frida_device_get_process_sync (FridaDevice * self, FridaDeviceProcessPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_find_process_by_pid (FridaDevice * self, guint pid, GAsyncReadyCallback callback, gpointer user_data);
FridaProcess * frida_device_find_process_by_pid_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaProcess * frida_device_find_process_by_pid_sync (FridaDevice * self, guint pid, GError ** error);
void frida_device_find_process_by_name (FridaDevice * self, const gchar * name, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaProcess * frida_device_find_process_by_name_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaProcess * frida_device_find_process_by_name_sync (FridaDevice * self, const gchar * name, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_find_process (FridaDevice * self, FridaDeviceProcessPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
FridaProcess * frida_device_find_process_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaProcess * frida_device_find_process_sync (FridaDevice * self, FridaDeviceProcessPredicate predicate, gpointer predicate_data, gint timeout, GCancellable * cancellable, GError ** error);
void frida_device_enumerate_processes (FridaDevice * self, GAsyncReadyCallback callback, gpointer user_data);
FridaProcessList * frida_device_enumerate_processes_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaProcessList * frida_device_enumerate_processes_sync (FridaDevice * self, GError ** error);
void frida_device_enable_spawn_gating (FridaDevice * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_device_enable_spawn_gating_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
void frida_device_enable_spawn_gating_sync (FridaDevice * self, GError ** error);
void frida_device_disable_spawn_gating (FridaDevice * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_device_disable_spawn_gating_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
void frida_device_disable_spawn_gating_sync (FridaDevice * self, GError ** error);
void frida_device_enumerate_pending_spawn (FridaDevice * self, GAsyncReadyCallback callback, gpointer user_data);
FridaSpawnList * frida_device_enumerate_pending_spawn_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaSpawnList * frida_device_enumerate_pending_spawn_sync (FridaDevice * self, GError ** error);
void frida_device_enumerate_pending_children (FridaDevice * self, GAsyncReadyCallback callback, gpointer user_data);
FridaChildList * frida_device_enumerate_pending_children_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaChildList * frida_device_enumerate_pending_children_sync (FridaDevice * self, GError ** error);
void frida_device_spawn (FridaDevice * self, const gchar * program, FridaSpawnOptions * options, GAsyncReadyCallback callback, gpointer user_data);
guint frida_device_spawn_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
guint frida_device_spawn_sync (FridaDevice * self, const gchar * program, FridaSpawnOptions * options, GError ** error);
void frida_device_input (FridaDevice * self, guint pid, GBytes * data, GAsyncReadyCallback callback, gpointer user_data);
void frida_device_input_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
void frida_device_input_sync (FridaDevice * self, guint pid, GBytes * data, GError ** error);
void frida_device_resume (FridaDevice * self, guint pid, GAsyncReadyCallback callback, gpointer user_data);
void frida_device_resume_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
void frida_device_resume_sync (FridaDevice * self, guint pid, GError ** error);
void frida_device_kill (FridaDevice * self, guint pid, GAsyncReadyCallback callback, gpointer user_data);
void frida_device_kill_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
void frida_device_kill_sync (FridaDevice * self, guint pid, GError ** error);
void frida_device_attach (FridaDevice * self, guint pid, GAsyncReadyCallback callback, gpointer user_data);
FridaSession * frida_device_attach_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
FridaSession * frida_device_attach_sync (FridaDevice * self, guint pid, GError ** error);
void frida_device_inject_library_file (FridaDevice * self, guint pid, const gchar * path, const gchar * entrypoint, const gchar * data, GAsyncReadyCallback callback, gpointer user_data);
guint frida_device_inject_library_file_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
guint frida_device_inject_library_file_sync (FridaDevice * self, guint pid, const gchar * path, const gchar * entrypoint, const gchar * data, GError ** error);
void frida_device_inject_library_blob (FridaDevice * self, guint pid, GBytes * blob, const gchar * entrypoint, const gchar * data, GAsyncReadyCallback callback, gpointer user_data);
guint frida_device_inject_library_blob_finish (FridaDevice * self, GAsyncResult * result, GError ** error);
guint frida_device_inject_library_blob_sync (FridaDevice * self, guint pid, GBytes * blob, const gchar * entrypoint, const gchar * data, GError ** error);

/* ApplicationList */
gint frida_application_list_size (FridaApplicationList * self);
FridaApplication * frida_application_list_get (FridaApplicationList * self, gint index);

/* Application */
const gchar * frida_application_get_identifier (FridaApplication * self);
const gchar * frida_application_get_name (FridaApplication * self);
guint frida_application_get_pid (FridaApplication * self);
FridaIcon * frida_application_get_small_icon (FridaApplication * self);
FridaIcon * frida_application_get_large_icon (FridaApplication * self);

/* ProcessList */
gint frida_process_list_size (FridaProcessList * self);
FridaProcess * frida_process_list_get (FridaProcessList * self, gint index);

/* Process */
guint frida_process_get_pid (FridaProcess * self);
const gchar * frida_process_get_name (FridaProcess * self);
FridaIcon * frida_process_get_small_icon (FridaProcess * self);
FridaIcon * frida_process_get_large_icon (FridaProcess * self);

/* SpawnOptions */
FridaSpawnOptions * frida_spawn_options_new (void);

gchar ** frida_spawn_options_get_argv (FridaSpawnOptions * self, int * result_length);
gchar ** frida_spawn_options_get_envp (FridaSpawnOptions * self, int * result_length);
gchar ** frida_spawn_options_get_env (FridaSpawnOptions * self, int * result_length);
const gchar * frida_spawn_options_get_cwd (FridaSpawnOptions * self);
FridaStdio frida_spawn_options_get_stdio (FridaSpawnOptions * self);
GVariantDict * frida_spawn_options_get_aux (FridaSpawnOptions * self);

void frida_spawn_options_set_argv (FridaSpawnOptions * self, gchar ** value, int value_length);
void frida_spawn_options_set_envp (FridaSpawnOptions * self, gchar ** value, int value_length);
void frida_spawn_options_set_env (FridaSpawnOptions * self, gchar ** value, int value_length);
void frida_spawn_options_set_cwd (FridaSpawnOptions * self, const gchar * value);
void frida_spawn_options_set_stdio (FridaSpawnOptions * self, FridaStdio value);

/* SpawnList */
gint frida_spawn_list_size (FridaSpawnList * self);
FridaSpawn * frida_spawn_list_get (FridaSpawnList * self, gint index);

/* Spawn */
guint frida_spawn_get_pid (FridaSpawn * self);
const gchar * frida_spawn_get_identifier (FridaSpawn * self);

/* ChildList */
gint frida_child_list_size (FridaChildList * self);
FridaChild * frida_child_list_get (FridaChildList * self, gint index);

/* Child */
guint frida_child_get_pid (FridaChild * self);
guint frida_child_get_parent_pid (FridaChild * self);
FridaChildOrigin frida_child_get_origin (FridaChild * self);
const gchar * frida_child_get_identifier (FridaChild * self);
const gchar * frida_child_get_path (FridaChild * self);
gchar ** frida_child_get_argv (FridaChild * self, int * result_length);
gchar ** frida_child_get_envp (FridaChild * self, int * result_length);

/* Icon */
gint frida_icon_get_width (FridaIcon * self);
gint frida_icon_get_height (FridaIcon * self);
gint frida_icon_get_rowstride (FridaIcon * self);
GBytes * frida_icon_get_pixels (FridaIcon * self);

/* Session */
guint frida_session_get_pid (FridaSession * self);
FridaDevice * frida_session_get_device (FridaSession * self);

gboolean frida_session_is_detached (FridaSession * self);
void frida_session_detach (FridaSession * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_session_detach_finish (FridaSession * self, GAsyncResult * result);
void frida_session_detach_sync (FridaSession * self);
void frida_session_enable_child_gating (FridaSession * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_session_enable_child_gating_finish (FridaSession * self, GAsyncResult * result, GError ** error);
void frida_session_enable_child_gating_sync (FridaSession * self, GError ** error);
void frida_session_disable_child_gating (FridaSession * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_session_disable_child_gating_finish (FridaSession * self, GAsyncResult * result, GError ** error);
void frida_session_disable_child_gating_sync (FridaSession * self, GError ** error);
void frida_session_create_script (FridaSession * self, const gchar * name, const gchar * source, GAsyncReadyCallback callback, gpointer user_data);
FridaScript * frida_session_create_script_finish (FridaSession * self, GAsyncResult * result, GError ** error);
FridaScript * frida_session_create_script_sync (FridaSession * self, const gchar * name, const gchar * source, GError ** error);
void frida_session_create_script_from_bytes (FridaSession * self, GBytes * bytes, GAsyncReadyCallback callback, gpointer user_data);
FridaScript * frida_session_create_script_from_bytes_finish (FridaSession * self, GAsyncResult * result, GError ** error);
FridaScript * frida_session_create_script_from_bytes_sync (FridaSession * self, GBytes * bytes, GError ** error);
void frida_session_compile_script (FridaSession * self, const gchar * name, const gchar * source, GAsyncReadyCallback callback, gpointer user_data);
GBytes * frida_session_compile_script_finish (FridaSession * self, GAsyncResult * result, GError ** error);
GBytes * frida_session_compile_script_sync (FridaSession * self, const gchar * name, const gchar * source, GError ** error);
void frida_session_enable_debugger (FridaSession * self, guint16 port, GAsyncReadyCallback callback, gpointer user_data);
void frida_session_enable_debugger_finish (FridaSession * self, GAsyncResult * result, GError ** error);
void frida_session_enable_debugger_sync (FridaSession * self, guint16 port, GError ** error);
void frida_session_disable_debugger (FridaSession * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_session_disable_debugger_finish (FridaSession * self, GAsyncResult * result, GError ** error);
void frida_session_disable_debugger_sync (FridaSession * self, GError ** error);
void frida_session_enable_jit (FridaSession * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_session_enable_jit_finish (FridaSession * self, GAsyncResult * result, GError ** error);
void frida_session_enable_jit_sync (FridaSession * self, GError ** error);

/* Script */
guint frida_script_get_id (FridaScript * self);

gboolean frida_script_is_destroyed (FridaScript * self);
void frida_script_load (FridaScript * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_script_load_finish (FridaScript * self, GAsyncResult * result, GError ** error);
void frida_script_load_sync (FridaScript * self, GError ** error);
void frida_script_unload (FridaScript * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_script_unload_finish (FridaScript * self, GAsyncResult * result, GError ** error);
void frida_script_unload_sync (FridaScript * self, GError ** error);
void frida_script_post (FridaScript * self, const gchar * message, GBytes * data, GAsyncReadyCallback callback, gpointer user_data);
void frida_script_post_finish (FridaScript * self, GAsyncResult * result, GError ** error);
void frida_script_post_sync (FridaScript * self, const gchar * message, GBytes * data, GError ** error);

/* Injector */
FridaInjector * frida_injector_new (void);

FridaInjector * frida_injector_new_inprocess (void);
void frida_injector_close (FridaInjector * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_injector_close_finish (FridaInjector * self, GAsyncResult * result);
void frida_injector_close_sync (FridaInjector * self);
void frida_injector_inject_library_file (FridaInjector * self, guint pid, const gchar * path, const gchar * entrypoint, const gchar * data, GAsyncReadyCallback callback, gpointer user_data);
guint frida_injector_inject_library_file_finish (FridaInjector * self, GAsyncResult * result, GError ** error);
guint frida_injector_inject_library_file_sync (FridaInjector * self, guint pid, const gchar * path, const gchar * entrypoint, const gchar * data, GError ** error);
void frida_injector_inject_library_blob (FridaInjector * self, guint pid, GBytes * blob, const gchar * entrypoint, const gchar * data, GAsyncReadyCallback callback, gpointer user_data);
guint frida_injector_inject_library_blob_finish (FridaInjector * self, GAsyncResult * result, GError ** error);
guint frida_injector_inject_library_blob_sync (FridaInjector * self, guint pid, GBytes * blob, const gchar * entrypoint, const gchar * data, GError ** error);
void frida_injector_demonitor_and_clone_state (FridaInjector * self, guint id, GAsyncReadyCallback callback, gpointer user_data);
guint frida_injector_demonitor_and_clone_state_finish (FridaInjector * self, GAsyncResult * result, GError ** error);
guint frida_injector_demonitor_and_clone_state_sync (FridaInjector * self, guint id, GError ** error);
void frida_injector_recreate_thread (FridaInjector * self, guint pid, guint id, GAsyncReadyCallback callback, gpointer user_data);
void frida_injector_recreate_thread_finish (FridaInjector * self, GAsyncResult * result, GError ** error);
void frida_injector_recreate_thread_sync (FridaInjector * self, guint pid, guint id, GError ** error);

/* FileMonitor */
FridaFileMonitor * frida_file_monitor_new (const gchar * path);

const gchar * frida_file_monitor_get_path (FridaFileMonitor * self);

void frida_file_monitor_enable (FridaFileMonitor * self, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data);
void frida_file_monitor_enable_finish (FridaFileMonitor * self, GAsyncResult * result, GError ** error);
void frida_file_monitor_enable_sync (FridaFileMonitor * self, GCancellable * cancellable, GError ** error);
void frida_file_monitor_disable (FridaFileMonitor * self, GAsyncReadyCallback callback, gpointer user_data);
void frida_file_monitor_disable_finish (FridaFileMonitor * self, GAsyncResult * result, GError ** error);
void frida_file_monitor_disable_sync (FridaFileMonitor * self, GError ** error);

/* Errors */
GQuark frida_error_quark (void);

typedef enum {
  FRIDA_ERROR_SERVER_NOT_RUNNING,
  FRIDA_ERROR_EXECUTABLE_NOT_FOUND,
  FRIDA_ERROR_EXECUTABLE_NOT_SUPPORTED,
  FRIDA_ERROR_PROCESS_NOT_FOUND,
  FRIDA_ERROR_PROCESS_NOT_RESPONDING,
  FRIDA_ERROR_INVALID_ARGUMENT,
  FRIDA_ERROR_INVALID_OPERATION,
  FRIDA_ERROR_PERMISSION_DENIED,
  FRIDA_ERROR_ADDRESS_IN_USE,
  FRIDA_ERROR_TIMED_OUT,
  FRIDA_ERROR_NOT_SUPPORTED,
  FRIDA_ERROR_PROTOCOL,
  FRIDA_ERROR_TRANSPORT
} FridaError;

/* GTypes */
GType frida_device_type_get_type (void) G_GNUC_CONST;
GType frida_child_origin_get_type (void) G_GNUC_CONST;
GType frida_session_detach_reason_get_type (void) G_GNUC_CONST;
GType frida_stdio_get_type (void) G_GNUC_CONST;
GType frida_unload_policy_get_type (void) G_GNUC_CONST;
GType frida_device_manager_get_type (void) G_GNUC_CONST;
GType frida_device_list_get_type (void) G_GNUC_CONST;
GType frida_device_get_type (void) G_GNUC_CONST;
GType frida_application_list_get_type (void) G_GNUC_CONST;
GType frida_application_get_type (void) G_GNUC_CONST;
GType frida_process_list_get_type (void) G_GNUC_CONST;
GType frida_process_get_type (void) G_GNUC_CONST;
GType frida_spawn_options_get_type (void) G_GNUC_CONST;
GType frida_spawn_list_get_type (void) G_GNUC_CONST;
GType frida_spawn_get_type (void) G_GNUC_CONST;
GType frida_child_list_get_type (void) G_GNUC_CONST;
GType frida_child_get_type (void) G_GNUC_CONST;
GType frida_icon_get_type (void) G_GNUC_CONST;
GType frida_session_get_type (void) G_GNUC_CONST;
GType frida_script_get_type (void) G_GNUC_CONST;
GType frida_injector_get_type (void) G_GNUC_CONST;
GType frida_file_monitor_get_type (void) G_GNUC_CONST;

/* Macros */
#define FRIDA_TYPE_DEVICE_TYPE (frida_device_type_get_type ())

#define FRIDA_TYPE_CHILD_ORIGIN (frida_child_origin_get_type ())

#define FRIDA_TYPE_SESSION_DETACH_REASON (frida_session_detach_reason_get_type ())

#define FRIDA_TYPE_STDIO (frida_stdio_get_type ())

#define FRIDA_TYPE_UNLOAD_POLICY (frida_unload_policy_get_type ())

#define FRIDA_TYPE_DEVICE_MANAGER (frida_device_manager_get_type ())
#define FRIDA_DEVICE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_DEVICE_MANAGER, FridaDeviceManager))
#define FRIDA_IS_DEVICE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_DEVICE_MANAGER))

#define FRIDA_TYPE_DEVICE_LIST (frida_device_list_get_type ())
#define FRIDA_DEVICE_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_DEVICE_LIST, FridaDeviceList))
#define FRIDA_IS_DEVICE_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_DEVICE_LIST))

#define FRIDA_TYPE_DEVICE (frida_device_get_type ())
#define FRIDA_DEVICE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_DEVICE, FridaDevice))
#define FRIDA_IS_DEVICE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_DEVICE))

#define FRIDA_TYPE_APPLICATION_LIST (frida_application_list_get_type ())
#define FRIDA_APPLICATION_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_APPLICATION_LIST, FridaApplicationList))
#define FRIDA_IS_APPLICATION_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_APPLICATION_LIST))

#define FRIDA_TYPE_APPLICATION (frida_application_get_type ())
#define FRIDA_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_APPLICATION, FridaApplication))
#define FRIDA_IS_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_APPLICATION))

#define FRIDA_TYPE_PROCESS_LIST (frida_process_list_get_type ())
#define FRIDA_PROCESS_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_PROCESS_LIST, FridaProcessList))
#define FRIDA_IS_PROCESS_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_PROCESS_LIST))

#define FRIDA_TYPE_PROCESS (frida_process_get_type ())
#define FRIDA_PROCESS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_PROCESS, FridaProcess))
#define FRIDA_IS_PROCESS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_PROCESS))

#define FRIDA_TYPE_SPAWN_OPTIONS (frida_spawn_options_get_type ())
#define FRIDA_SPAWN_OPTIONS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_SPAWN_OPTIONS, FridaSpawnOptions))
#define FRIDA_IS_SPAWN_OPTIONS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_SPAWN_OPTIONS))

#define FRIDA_TYPE_SPAWN_LIST (frida_spawn_list_get_type ())
#define FRIDA_SPAWN_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_SPAWN_LIST, FridaSpawnList))
#define FRIDA_IS_SPAWN_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_SPAWN_LIST))

#define FRIDA_TYPE_SPAWN (frida_spawn_get_type ())
#define FRIDA_SPAWN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_SPAWN, FridaSpawn))
#define FRIDA_IS_SPAWN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_SPAWN))

#define FRIDA_TYPE_CHILD_LIST (frida_child_list_get_type ())
#define FRIDA_CHILD_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_CHILD_LIST, FridaChildList))
#define FRIDA_IS_CHILD_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_CHILD_LIST))

#define FRIDA_TYPE_CHILD (frida_child_get_type ())
#define FRIDA_CHILD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_CHILD, FridaChild))
#define FRIDA_IS_CHILD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_CHILD))

#define FRIDA_TYPE_ICON (frida_icon_get_type ())
#define FRIDA_ICON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_ICON, FridaIcon))
#define FRIDA_IS_ICON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_ICON))

#define FRIDA_TYPE_SESSION (frida_session_get_type ())
#define FRIDA_SESSION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_SESSION, FridaSession))
#define FRIDA_IS_SESSION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_SESSION))

#define FRIDA_TYPE_SCRIPT (frida_script_get_type ())
#define FRIDA_SCRIPT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_SCRIPT, FridaScript))
#define FRIDA_IS_SCRIPT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_SCRIPT))

#define FRIDA_TYPE_INJECTOR (frida_injector_get_type ())
#define FRIDA_INJECTOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_INJECTOR, FridaInjector))
#define FRIDA_IS_INJECTOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_INJECTOR))

#define FRIDA_TYPE_FILE_MONITOR (frida_file_monitor_get_type ())
#define FRIDA_FILE_MONITOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FRIDA_TYPE_FILE_MONITOR, FridaFileMonitor))
#define FRIDA_IS_FILE_MONITOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FRIDA_TYPE_FILE_MONITOR))

#define FRIDA_ERROR (frida_error_quark ())

G_END_DECLS

#endif

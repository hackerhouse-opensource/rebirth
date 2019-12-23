[CCode (cheader_filename = "frida-core.h", cprefix = "Frida", lower_case_cprefix = "frida_")]
namespace Frida {
	public static void init ();
	public static void shutdown ();
	public static void deinit ();
	public static unowned GLib.MainContext get_main_context ();

	public enum DeviceType {
		LOCAL,
		REMOTE,
		USB
	}

	public enum ChildOrigin {
		FORK,
		EXEC,
		SPAWN
	}

	public enum SessionDetachReason {
		APPLICATION_REQUESTED,
		PROCESS_REPLACED,
		PROCESS_TERMINATED,
		SERVER_TERMINATED,
		DEVICE_LOST
	}

	public enum Stdio {
		INHERIT,
		PIPE
	}

	public enum UnloadPolicy {
		IMMEDIATE,
		RESIDENT,
		DEFERRED
	}

	public class DeviceManager : GLib.Object {
		public DeviceManager ();

		public async void close ();
		public void close_sync ();
		public async Frida.Device get_device_by_id (string id, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Device get_device_by_id_sync (string id, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Device get_device_by_type (Frida.DeviceType type, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Device get_device_by_type_sync (Frida.DeviceType type, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Device get_device (Frida.DeviceManager.Predicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Device get_device_sync (Frida.DeviceManager.Predicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Device? find_device_by_id (string id, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Device? find_device_by_id_sync (string id, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Device? find_device_by_type (Frida.DeviceType type, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Device? find_device_by_type_sync (Frida.DeviceType type, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Device? find_device (Frida.DeviceManager.Predicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Device? find_device_sync (Frida.DeviceManager.Predicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.DeviceList enumerate_devices () throws Frida.Error;
		public Frida.DeviceList enumerate_devices_sync () throws Frida.Error;
		public async Frida.Device add_remote_device (string host) throws Frida.Error;
		public Frida.Device add_remote_device_sync (string host) throws Frida.Error;
		public async void remove_remote_device (string host) throws Frida.Error;
		public void remove_remote_device_sync (string host) throws Frida.Error;
		public delegate bool Predicate (Frida.Device device);

		public signal void added (Frida.Device device);
		public signal void changed ();
		public signal void removed (Frida.Device device);
	}

	public class DeviceList : GLib.Object {
		public int size ();
		public new Frida.Device @get (int index);
	}

	public class Device : GLib.Object {
		public string id { get; construct; }
		public string name { get; construct; }
		public Frida.Icon? icon { get; construct; }
		public Frida.DeviceType dtype { get; construct; }
		public Frida.DeviceManager manager { get; construct; }

		public bool is_lost ();
		public async Frida.Application? get_frontmost_application () throws Frida.Error;
		public Frida.Application? get_frontmost_application_sync () throws Frida.Error;
		public async Frida.ApplicationList enumerate_applications () throws Frida.Error;
		public Frida.ApplicationList enumerate_applications_sync () throws Frida.Error;
		public async Frida.Process get_process_by_pid (uint pid) throws Frida.Error;
		public Frida.Process get_process_by_pid_sync (uint pid) throws Frida.Error;
		public async Frida.Process get_process_by_name (string name, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Process get_process_by_name_sync (string name, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Process get_process (Frida.Device.ProcessPredicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Process get_process_sync (Frida.Device.ProcessPredicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Process? find_process_by_pid (uint pid) throws Frida.Error;
		public Frida.Process? find_process_by_pid_sync (uint pid) throws Frida.Error;
		public async Frida.Process? find_process_by_name (string name, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Process? find_process_by_name_sync (string name, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.Process? find_process (Frida.Device.ProcessPredicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public Frida.Process? find_process_sync (Frida.Device.ProcessPredicate predicate, int timeout = 0, GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async Frida.ProcessList enumerate_processes () throws Frida.Error;
		public Frida.ProcessList enumerate_processes_sync () throws Frida.Error;
		public async void enable_spawn_gating () throws Frida.Error;
		public void enable_spawn_gating_sync () throws Frida.Error;
		public async void disable_spawn_gating () throws Frida.Error;
		public void disable_spawn_gating_sync () throws Frida.Error;
		public async Frida.SpawnList enumerate_pending_spawn () throws Frida.Error;
		public Frida.SpawnList enumerate_pending_spawn_sync () throws Frida.Error;
		public async Frida.ChildList enumerate_pending_children () throws Frida.Error;
		public Frida.ChildList enumerate_pending_children_sync () throws Frida.Error;
		public async uint spawn (string program, Frida.SpawnOptions? options = null) throws Frida.Error;
		public uint spawn_sync (string program, Frida.SpawnOptions? options = null) throws Frida.Error;
		public async void input (uint pid, GLib.Bytes data) throws Frida.Error;
		public void input_sync (uint pid, GLib.Bytes data) throws Frida.Error;
		public async void resume (uint pid) throws Frida.Error;
		public void resume_sync (uint pid) throws Frida.Error;
		public async void kill (uint pid) throws Frida.Error;
		public void kill_sync (uint pid) throws Frida.Error;
		public async Frida.Session attach (uint pid) throws Frida.Error;
		public Frida.Session attach_sync (uint pid) throws Frida.Error;
		public async uint inject_library_file (uint pid, string path, string entrypoint, string data) throws Frida.Error;
		public uint inject_library_file_sync (uint pid, string path, string entrypoint, string data) throws Frida.Error;
		public async uint inject_library_blob (uint pid, GLib.Bytes blob, string entrypoint, string data) throws Frida.Error;
		public uint inject_library_blob_sync (uint pid, GLib.Bytes blob, string entrypoint, string data) throws Frida.Error;
		public delegate bool ProcessPredicate (Frida.Process process);

		public signal void child_added (Frida.Child child);
		public signal void child_removed (Frida.Child child);
		public signal void lost ();
		public signal void output (uint pid, int fd, GLib.Bytes data);
		public signal void spawn_added (Frida.Spawn spawn);
		public signal void spawn_removed (Frida.Spawn spawn);
		public signal void uninjected (uint id);
	}

	public class ApplicationList : GLib.Object {
		public int size ();
		public new Frida.Application @get (int index);
	}

	public class Application : GLib.Object {
		public string identifier { get; construct; }
		public string name { get; construct; }
		public uint pid { get; construct; }
		public Frida.Icon? small_icon { get; construct; }
		public Frida.Icon? large_icon { get; construct; }
	}

	public class ProcessList : GLib.Object {
		public int size ();
		public new Frida.Process @get (int index);
	}

	public class Process : GLib.Object {
		public uint pid { get; construct; }
		public string name { get; construct; }
		public Frida.Icon? small_icon { get; construct; }
		public Frida.Icon? large_icon { get; construct; }
	}

	public class SpawnOptions : GLib.Object {
		public string[]? argv { get; set; }
		public string[]? envp { get; set; }
		public string[]? env { get; set; }
		public string? cwd { get; set; }
		public Frida.Stdio stdio { get; set; }
		public GLib.VariantDict aux { get; }

		public SpawnOptions ();
	}

	public class SpawnList : GLib.Object {
		public int size ();
		public new Frida.Spawn @get (int index);
	}

	public class Spawn : GLib.Object {
		public uint pid { get; construct; }
		public string? identifier { get; construct; }
	}

	public class ChildList : GLib.Object {
		public int size ();
		public new Frida.Child @get (int index);
	}

	public class Child : GLib.Object {
		public uint pid { get; construct; }
		public uint parent_pid { get; construct; }
		public Frida.ChildOrigin origin { get; construct; }
		public string? identifier { get; construct; }
		public string? path { get; construct; }
		public string[]? argv { get; construct; }
		public string[]? envp { get; construct; }
	}

	public class Icon : GLib.Object {
		public int width { get; construct; }
		public int height { get; construct; }
		public int rowstride { get; construct; }
		public GLib.Bytes pixels { get; construct; }
	}

	public class Session : GLib.Object {
		public uint pid { get; construct; }
		public Frida.Device device { get; construct; }

		public bool is_detached ();
		public async void detach ();
		public void detach_sync ();
		public async void enable_child_gating () throws Frida.Error;
		public void enable_child_gating_sync () throws Frida.Error;
		public async void disable_child_gating () throws Frida.Error;
		public void disable_child_gating_sync () throws Frida.Error;
		public async Frida.Script create_script (string? name, string source) throws Frida.Error;
		public Frida.Script create_script_sync (string? name, string source) throws Frida.Error;
		public async Frida.Script create_script_from_bytes (GLib.Bytes bytes) throws Frida.Error;
		public Frida.Script create_script_from_bytes_sync (GLib.Bytes bytes) throws Frida.Error;
		public async GLib.Bytes compile_script (string? name, string source) throws Frida.Error;
		public GLib.Bytes compile_script_sync (string? name, string source) throws Frida.Error;
		public async void enable_debugger (uint16 port = 0) throws Frida.Error;
		public void enable_debugger_sync (uint16 port = 0) throws Frida.Error;
		public async void disable_debugger () throws Frida.Error;
		public void disable_debugger_sync () throws Frida.Error;
		public async void enable_jit () throws Frida.Error;
		public void enable_jit_sync () throws Frida.Error;

		public signal void detached (Frida.SessionDetachReason reason);
	}

	public class Script : GLib.Object {
		public uint id { get; construct; }

		public bool is_destroyed ();
		public async void load () throws Frida.Error;
		public void load_sync () throws Frida.Error;
		public async void unload () throws Frida.Error;
		public void unload_sync () throws Frida.Error;
		public async void post (string message, GLib.Bytes? data = null) throws Frida.Error;
		public void post_sync (string message, GLib.Bytes? data = null) throws Frida.Error;

		public signal void destroyed ();
		public signal void message (string message, GLib.Bytes? data);
	}

	public interface Injector : GLib.Object {
		public static Frida.Injector @new ();

		public static Frida.Injector new_inprocess ();
		public abstract async void close ();
		public void close_sync ();
		public abstract async uint inject_library_file (uint pid, string path, string entrypoint, string data) throws Frida.Error;
		public uint inject_library_file_sync (uint pid, string path, string entrypoint, string data) throws Frida.Error;
		public abstract async uint inject_library_blob (uint pid, GLib.Bytes blob, string entrypoint, string data) throws Frida.Error;
		public uint inject_library_blob_sync (uint pid, GLib.Bytes blob, string entrypoint, string data) throws Frida.Error;
		public abstract async uint demonitor_and_clone_state (uint id) throws Frida.Error;
		public uint demonitor_and_clone_state_sync (uint id) throws Frida.Error;
		public abstract async void recreate_thread (uint pid, uint id) throws Frida.Error;
		public void recreate_thread_sync (uint pid, uint id) throws Frida.Error;

		public signal void uninjected (uint id);
	}

	public class FileMonitor : GLib.Object {
		public string path { get; construct; }

		public FileMonitor (string path);

		public async void enable (GLib.Cancellable? cancellable = null) throws Frida.Error;
		public void enable_sync (GLib.Cancellable? cancellable = null) throws Frida.Error;
		public async void disable () throws Frida.Error;
		public void disable_sync () throws Frida.Error;

		public signal void change (string file_path, string? other_file_path, GLib.FileMonitorEvent event);
	}
}

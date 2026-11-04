#include <NodeWorkbench/NodeWorkbench.h>
#include <Node/Script/Script.h>

#ifdef ERROR
#undef ERROR
#endif

namespace Upp {
#ifdef UPP_HEAP
extern bool NoMemoryLeaksCheck;
#endif
}

using namespace Upp;

// --dump-graph <path>  — headless: open a graph file, print stats, exit 0 on success
static int DumpGraph(const String& path) {
	if (!FileExists(path)) {
		Cout() << "ERROR: file not found: " << path << "\n";
		return 1;
	}

	Node::Graph g;
	Vector<Node::ValidationMessage> msgs;
	bool ok = Node::LoadEonFile(g, path, msgs);

	// Print any load messages
	for (auto& m : msgs)
		Cout() << (m.severity == Node::ValidationMessage::ERROR ? "ERROR" :
		           m.severity == Node::ValidationMessage::WARNING ? "WARNING" : "INFO")
		       << ": " << m.message << "\n";

	const Node::GraphDoc& doc = g.GetDoc();
	int n_nodes = doc.nodes.GetCount();
	int n_edges = doc.edges.GetCount();

	Cout() << "File    : " << path << "\n";
	Cout() << "Nodes   : " << n_nodes << "\n";
	Cout() << "Edges   : " << n_edges << "\n";

	if (n_nodes > 0) {
		Cout() << "\nNode list:\n";
		for (const Node::NodeDoc& nd : doc.nodes) {
			Cout() << "  [" << nd.id << "]"
			       << "  type=" << nd.node_type_id
			       << "  pins=" << nd.pins.GetCount()
			       << "  slots=" << nd.slots.GetCount()
			       << "\n";
		}
	}

	if (n_edges > 0) {
		Cout() << "\nConnection list:\n";
		for (const Node::EdgeDoc& ed : doc.edges) {
			Cout() << "  " << ed.source_node << "." << ed.source_pin
			       << " -> " << ed.target_node << "." << ed.target_pin
			       << "\n";
		}
	}

	Cout() << "\nResult  : " << (ok ? "OK" : "LOAD FAILED") << "\n";
	return ok && n_nodes > 0 ? 0 : 2;
}

static int RunSelfTest() {
	String test_subpath = "share/eon/tests/00a_audio_gen.eon";
	Vector<String> candidates = {
		test_subpath,
		"../" + test_subpath,
		"../../" + test_subpath,
		NormalizePath(AppendFileName(GetFileFolder(GetExeFilePath()), "../share/eon/tests/00a_audio_gen.eon")),
		NormalizePath(AppendFileName(GetFileFolder(GetExeFilePath()), "../../share/eon/tests/00a_audio_gen.eon")),
		NormalizePath(AppendFileName(GetFileFolder(GetExeFilePath()), "../../../share/eon/tests/00a_audio_gen.eon")),
		"/home/sblo/Dev/Eon/share/eon/tests/00a_audio_gen.eon"
	};
	String found_path;
	for (const String& c : candidates) {
		if (FileExists(c)) {
			found_path = c;
			break;
		}
	}
	if (found_path.IsEmpty()) {
		Cout() << "ERROR: Cannot find sample graph 00a_audio_gen.eon\n";
		return 1;
	}
	Cout() << "Running NodeWorkbenchApp self-test using: " << found_path << "\n";
	int res = DumpGraph(found_path);
	if (res != 0) {
		Cout() << "ERROR: DumpGraph returned code " << res << "\n";
		return res;
	}
	Cout() << "SUCCESS: NodeWorkbenchApp self-test passed.\n";
	return 0;
}

GUI_APP_MAIN {
	const Vector<String>& args = CommandLine();
	for (int i = 0; i < args.GetCount(); i++) {
		if (args[i] == "--test") {
#ifdef UPP_HEAP
			NoMemoryLeaksCheck = true;
#endif
			SetExitCode(RunSelfTest());
			return;
		}
		if (args[i] == "--dump-graph" && i + 1 < args.GetCount()) {
#ifdef UPP_HEAP
			NoMemoryLeaksCheck = true;
#endif
			SetExitCode(DumpGraph(args[i + 1]));
			return;
		}
	}

	NodeWorkbenchWindow win;
	if (!args.IsEmpty()) {
		String path = args[0];
		if (FileExists(path))
			win.OpenPath(path);
	}
	win.Run();
}

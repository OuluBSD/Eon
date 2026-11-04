#include <Core/Core.h>
#include <Eon/Core/Core.h>

using namespace Upp;

class DemoSinkAtom : public AtomBase {
public:
	CLASSTYPE(DemoSinkAtom)
	int received_count = 0;
	DemoSinkAtom(VfsValue& v) : AtomBase(v) {}

	AtomTypeCls GetType() const override { return AtomTypeCls(); }
	void CopyTo(AtomBase* atom) const override {}
	bool InitializeAtom(const WorldState& ws) override { return true; }
	void UninitializeAtom() override {}
	void VisitSource(Vis& vis) override {}
	void VisitSink(Vis& vis) override {}
	void ClearSinkSource() override {}
	ISourcePtr GetSource() override { return nullptr; }
	ISinkPtr GetSink() override { return nullptr; }
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override { return false; }

	bool Recv(int sink_ch, const Packet& in) override {
		received_count++;
		return true;
	}
};

class DemoSourceAtom : public AtomBase {
public:
	CLASSTYPE(DemoSourceAtom)
	DemoSourceAtom(VfsValue& v) : AtomBase(v) {}

	AtomTypeCls GetType() const override { return AtomTypeCls(); }
	void CopyTo(AtomBase* atom) const override {}
	bool InitializeAtom(const WorldState& ws) override { return true; }
	void UninitializeAtom() override {}
	void VisitSource(Vis& vis) override {}
	void VisitSink(Vis& vis) override {}
	void ClearSinkSource() override {}
	ISourcePtr GetSource() override { return nullptr; }
	ISinkPtr GetSink() override { return nullptr; }
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override { return true; }
};

int main(int argc, const char *argv[]) {
	StdLogSetup(LOG_COUT | LOG_FILE);
	SetExitCode(0);

	bool test_mode = false;
	int steps = 10;

	for (int i = 1; i < argc; i++) {
		String arg = argv[i];
		if (arg == "--test")
			test_mode = true;
		else if (arg.StartsWith("--steps="))
			steps = StrInt(arg.Mid(8));
	}
	if (steps <= 0)
		steps = 10;

	Cout() << "=== Eon Headless Packet Router Demo ===\n";
	Cout() << "Running " << steps << " packet routing steps...\n";

	VfsValue src_node;
	src_node.id = "demo_source_atom";
	DemoSourceAtom src_atom(src_node);

	VfsValue sink_node;
	sink_node.id = "demo_sink_atom";
	DemoSinkAtom sink_atom(sink_node);

	PacketRouter router;

	ValDevTuple vd;
	vd.Add(ValDevCls(AUDIO, CENTER), false);

	PacketRouter::PortHandle src_handle = router.RegisterPort(
		&src_atom,
		RouterPortDesc::Direction::Source,
		0,
		vd
	);

	PacketRouter::PortHandle sink_handle = router.RegisterPort(
		&sink_atom,
		RouterPortDesc::Direction::Sink,
		0,
		vd
	);

	if (!src_handle.IsValid() || !sink_handle.IsValid()) {
		Cerr() << "ERROR: Failed to register router ports!\n";
		return 1;
	}

	router.Connect(src_handle, sink_handle);

	if (router.GetPortCount() != 2) {
		Cerr() << "ERROR: Expected 2 ports in router, got " << router.GetPortCount() << "\n";
		return 1;
	}

	if (router.GetConnectionCount() != 1) {
		Cerr() << "ERROR: Expected 1 connection in router, got " << router.GetConnectionCount() << "\n";
		return 1;
	}

	Cout() << router.DumpTopology();
	Cout() << router.DumpConnectionTable();

	for (int i = 0; i < steps; i++) {
		Packet pkt = CreatePacket(0);
		bool ok = router.RoutePacket(src_handle, pkt);
		if (!ok) {
			Cerr() << "ERROR: Failed to route packet at step " << (i + 1) << "\n";
			return 1;
		}
	}

	int routed = router.GetTotalPacketsRouted();
	int failures = router.GetTotalDeliveryFailures();

	Cout() << "Steps completed: " << steps << "\n";
	Cout() << "Packets routed: " << routed << "\n";
	Cout() << "Packets received by sink: " << sink_atom.received_count << "\n";
	Cout() << "Failures: " << failures << "\n";

	if (routed != steps) {
		Cerr() << "ERROR: Expected " << steps << " packets routed, got " << routed << "\n";
		return 1;
	}

	if (sink_atom.received_count != steps) {
		Cerr() << "ERROR: Expected " << steps << " packets received by sink, got " << sink_atom.received_count << "\n";
		return 1;
	}

	if (failures != 0) {
		Cerr() << "ERROR: Expected 0 failures, got " << failures << "\n";
		return 1;
	}

	Cout() << "SUCCESS: Eon PacketRouter demo passed.\n";
	return 0;
}

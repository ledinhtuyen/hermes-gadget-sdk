#include "check.hpp"
#include "speaker_queue.hpp"

TEST("whole_sample_bytes: a nearly full buffer takes whole samples only") {
  CHECK_EQ(hg::whole_sample_bytes(1280, 511), 510u);  // #73: 511 bytes of room used to take 511
  CHECK_EQ(hg::whole_sample_bytes(1280, 1), 0u);
  CHECK_EQ(hg::whole_sample_bytes(1280, 0), 0u);
}

TEST("whole_sample_bytes: a write that fits is queued whole") {
  CHECK_EQ(hg::whole_sample_bytes(1280, 1281), 1280u);
  CHECK_EQ(hg::whole_sample_bytes(1280, 49151), 1280u);
}

TEST("speaker waits for a startup buffer before playing a live stream") {
  CHECK(!hg::speaker_should_start(4096, 6400, true));
  CHECK(hg::speaker_should_start(6400, 6400, true));
  CHECK(hg::speaker_should_start(100, 6400, false));  // drain short final replies
}

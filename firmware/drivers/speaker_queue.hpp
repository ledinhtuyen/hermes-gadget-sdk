// How much of a PCM16 write fits in the speaker's stream buffer. A FreeRTOS
// stream buffer keeps one byte free, so its room is odd whenever it holds whole
// samples. Queueing all of that room would split a sample, shift every later
// sample by a byte, and play the rest of the reply as noise.
#pragma once
#include <algorithm>
#include <cstddef>

namespace hg {
inline size_t whole_sample_bytes(size_t want, size_t room) {
  return std::min(want, room) & ~static_cast<size_t>(1);
}

inline bool speaker_should_start(size_t buffered_bytes, size_t prebuffer_bytes, bool stream_open) {
  // Live playback waits for a jitter cushion; end-of-stream releases any short tail.
  return !stream_open || buffered_bytes >= prebuffer_bytes;
}
}  // namespace hg

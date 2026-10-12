from types import SimpleNamespace

from gateway.platforms.base import AudioFormat
from hermes_gadget_plugin.adapter import GadgetAdapter


def test_gadget_can_disable_streaming_tts_for_smooth_whole_file_playback():
    adapter = object.__new__(GadgetAdapter)
    adapter._streaming_tts = False
    adapter._session = lambda _chat_id: SimpleNamespace(paired=True, has_speaker=True)
    fmt = AudioFormat(sample_rate=24000, channels=1, sample_width=2)

    assert adapter.supports_streaming_tts("device", fmt) is False

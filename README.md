The IBXM extension adds decoding support for `.mod` (ProTracker), `.xm` (FastTracker 2), and `.s3m` (Scream Tracker 3) files.
The `it2play` extension adds decoding support for `.it` (Impulse Tracker) and `.s3m` files. Since both libraries support S3M,
whichever one you list first in your list of decoders (see usage section) should take priority.

# Compiling
You have to provide your own copy of Miniaudio, and add the folder containing `miniaudio.h` to your include path.

### `miniaudio_ibxm.c`
- Compile `miniaudio_ibxm.c`, `ibxm_reader.c`, `lib/micromod/ibxm-ac/ibxm.c`, and your own copy of `miniaudio.c`
  - Requires `lib/micromod/ibxm-ac/` as an include path

### `miniaudio_it2play.c`
- Compile these files and link with the math library (`-lm`):
  - `miniaudio_it2play.c`
  - `lib/it2_core.c`
  - `lib/it2_wav.c`
  - `lib/it2_hq.c`

# Usage
You have to explicitly tell Miniaudio to use the custom decoders:
```c
  #include <miniaudio_ibxm.h>
  #include <miniaudio_it2play.h>

  /* ...snip... */
  
  ma_decoding_backend_vtable* customDecoders[] = {
      ma_decoding_backend_ibxm,
      ma_decoding_backend_it2,
  };

  ma_decoder_config cfg = ma_decoder_config_init(ma_format_s16, 2, 48000);
  cfg.ppCustomBackendVTables = customDecoders;
  cfg.customBackendCount = sizeof(customDecoders) / sizeof(*customDecoders);
  cfg.pCustomBackendUserData = NULL;

  ma_decoder decoder = {};
  ma_result ma_res = ma_decoder_init_file("foregone.it", &cfg, &decoder);
  if (ma_res != MA_SUCCESS) {
      printf("Failed to setup audio decoder!\n");
      return false;
  }
```
After this you can use the decoder interface as normal (or use the decoder as a data source with the `ma_data_source_*` API).

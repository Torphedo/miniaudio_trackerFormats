This repository adds decoding support in [Miniaudio](https://github.com/mackron/miniaudio) for the following music formats:
- `.mod` (ProTracker)
- `.xm` (FastTracker 2)
- `.s3m` (Scream Tracker 3)
- `.it` (Impulse Tracker)

The IBXM extension adds `.mod`, `.xm`, and `.s3m` support. The `it2play` extension adds `.it` and `.s3m` support. Since both support S3M,
whichever one you list first in your list of decoders (see usage section) should take priority.

# Compiling
You have to provide your own copy of Miniaudio, and add the folder containing `miniaudio.h` to your include path.

<details>
  <summary>CMake instructions</summary>
  
  Assuming you already have a `miniaudio` target, add something like this to your CMake file. The `CMakeLists.txt`
  in this repo provides the `ibxm` and `IT2` targets.
  ```cmake
    # Link this for Miniaudio with tracker module support
    add_subdirectory(lib/ma_trackerFormats)
    add_library(ma_trackerFormats STATIC
        lib/ma_trackerFormats/ibxm_reader.c
        lib/ma_trackerFormats/miniaudio_ibxm.c
        lib/ma_trackerFormats/miniaudio_it2play.c
    )
    target_link_libraries(ma_trackerFormats PUBLIC miniaudio ibxm IT2)
    target_include_directories(miniaudio PUBLIC lib/ma_trackerFormats lib/ma_trackerFormats/lib/it2play)
  ```
</details>

<details>
  <summary>Non-CMake instructions</summary>

### `miniaudio_ibxm.c`
- Compile `miniaudio_ibxm.c`, `ibxm_reader.c`, `lib/micromod/ibxm-ac/ibxm.c`, and your own copy of `miniaudio.c`
  - Requires `lib/micromod/ibxm-ac/` as an include path

### `miniaudio_it2play.c`
- Compile these files and link with the math library (`-lm`):
  - `miniaudio_it2play.c`
  - `lib/it2_core.c`
  - `lib/it2_wav.c`
  - `lib/it2_hq.c`

</details>

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

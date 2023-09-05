# Focus Stacking Mecha

My 3D printing models are adjusted for:

* **Genesis Base GMR-150** - my macro rail,
* **Micro N20 Gear Motor Slow Speed** - I use 100RPM version in my project,
* **12x28x8 mm bearing** - for support the gears.

If you use different hardware you must adjust the STL files.

## Parts

There are four separated parts to print on 3D printer:

* **mount** - mounting motor to macro rail. Suggest to cut to two parts for easy insert motor. See `./3mf_pursa_slicer_mk3s/v1_mount.3mf`,
* **gear_small** - small gear mounted on motor. Suggest to cut to two parts for easy install gears support. See `./3mf_pursa_slicer_mk3s/v1_gear_small.3mf`,
* **gear_big** - big gear mounted on macro rail screw. Suggest to cut to two parts for easy install gears support. See `./3mf_pursa_slicer_mk3s/v1_gear_big.3mf`,
* **gears_support** - support for two gears. Suggest to cut to three parts of pause printing for insert bearing. I use second method, see: `./3mf_pursa_slicer_mk3s/v1_gears_support.3mf`.

All parts I printent on PET-G.

## Known disadventages

* **gear_small** - should hawe longer shaft because the cap is difficult to put on.
* **gears_support** - bearing overlap, so are shifted. Should use smaller bearings or bigger gears.

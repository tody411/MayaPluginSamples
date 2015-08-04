
NoiseCmd
====

Simple noise command (command plug-in).

## Result

This command can add noise to the selected mesh.

| ![Original] (results/original.png) | ![Original] (results/original.png) |
|-------------------------|-----------------|
| Original mesh   |   Noise mesh with $\sigma=0.5$  |

## Usage

1. Select the target mesh.
2. Run the following command.

###MEL:
``` bash
NoiseCmd <sigma>;
```

###Python:
``` bash
cmds.NoiseCmd(<sigma>)
```

|Parameter|Description |
|----------|------------|
|sigma     |Noise parameter |

## Examples

###MEL:
``` bash
polyTorus -sx 40 -sy 40 -r 5.0 -sr 2.0;
NoiseCmd 0.5;
```

###Python:
``` python
cmds.polyTorus(sx=40, sy=40, r=5.0, sr=2.0)
cmds.NoiseCmd(0.5)
```

## License

The MIT License 2015 (c) tody